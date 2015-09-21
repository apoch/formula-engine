#include "Pch.h"

#include "Functions.h"
#include "Formula.h"




static class FunctionRandom : public ITerminalEvaluator {
public:			// ITerminalEvaluator interface
	Result Evaluate(const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) const override {
		Result ret;

		--(*pindex);

		Result param = termSource.EvaluateSubexpression(context, pindex);
		if(param.code != RESULT_CODE_OK)
			return param;

		std::uniform_real_distribution<double> distribution(0.0, param.value);
		ret.value = distribution(m_generator);
		ret.code = RESULT_CODE_OK;

		return ret;
	}

private:
	mutable std::default_random_engine m_generator;
} s_functionRandom;


static class FunctionSumOfList : public ITerminalEvaluator {
public:			// ITerminalEvaluator interface
	Result Evaluate(const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) const override {
		Result ret;

		--(*pindex);

		const Formula::Term & term = termSource.m_terms[*pindex];
		if(!(term.flags & Formula::Term::FLAG_IS_TOKEN)) {
			ret.code = RESULT_CODE_SYNTAX_ERROR;
			ret.value = 0.0;
			return ret;
		}

		unsigned parameterListScope = term.payload.scopedToken.scope;
		unsigned parameterListName = term.payload.scopedToken.token;

		if(!context) {
			ret.code = RESULT_CODE_MISSING_DEFINITION;
			ret.value = 0.0;
			return ret;
		}

		ListResult listresult = context->ResolveList(*context, parameterListScope, parameterListName);
		if(listresult.code != RESULT_CODE_OK) {
			ret.code = listresult.code;
			ret.value = 0.0;
			return ret;
		}

		ret.value = 0.0;
		for(auto val : listresult.values)
			ret.value += val;

		ret.code = RESULT_CODE_OK;
		return ret;
	}
} s_functionSumOfList;


static class FunctionVector : public ITerminalEvaluator {
public:			// ITerminalEvaluator interface
	Result Evaluate(const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) const override {
		Result ret;

		--(*pindex);

		Result xparam = termSource.EvaluateSubexpression(context, pindex);
		if(xparam.code != RESULT_CODE_OK)
			return xparam;

		--(*pindex);

		Result yparam = termSource.EvaluateSubexpression(context, pindex);
		if(yparam.code != RESULT_CODE_OK)
			return yparam;

		// These are inverted because parameters to the function are
		// obtained in reverse order, due to internal notation.
		ret.code = RESULT_CODE_OK;
		ret.type = RESULT_TYPE_VECTOR2;
		ret.value = yparam.value;
		ret.value2 = xparam.value;
		return ret;
	}
} s_functionVector;



const ITerminalEvaluator * GetFunctionEvaluatorByName(const char str[]) {
	if(!std::strcmp(str, "SumOf"))
		return &s_functionSumOfList;

	if(!std::strcmp(str, "Random"))
		return &s_functionRandom;

	if(!std::strcmp(str, "Vec"))
		return &s_functionVector;

	return nullptr;
}


