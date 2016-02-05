#include "Pch.h"

#include "Functions.h"
#include "Formula.h"

#include <ctime>



static class FunctionBetween : public ITerminalEvaluator {
public:			// ITerminalEvaluator interface
	Result Evaluate(const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) const override {
		Result ret;
		ret.type = RESULT_TYPE_SCALAR;

		--(*pindex);
		Result v2 = termSource.EvaluateSubexpression(context, pindex);
		if(v2.code != RESULT_CODE_OK)
			return v2;

		--(*pindex);
		Result v1 = termSource.EvaluateSubexpression(context, pindex);
		if(v1.code != RESULT_CODE_OK)
			return v1;

		--(*pindex);
		Result t = termSource.EvaluateSubexpression(context, pindex);
		if(t.code != RESULT_CODE_OK)
			return t;

		ret.value = (v1.value < t.value && t.value < v2.value) ? 1.0 : 0.0;
		ret.code = RESULT_CODE_OK;
		return ret;
	}
} s_functionBetween;


static class FunctionDistance : public ITerminalEvaluator {
public:			// ITerminalEvaluator interface
	Result Evaluate(const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) const override {
		Result ret;
		ret.type = RESULT_TYPE_SCALAR;

		--(*pindex);
		Result v2 = termSource.EvaluateSubexpression(context, pindex);
		if(v2.code != RESULT_CODE_OK)
			return v2;

		--(*pindex);
		Result v1 = termSource.EvaluateSubexpression(context, pindex);
		if(v1.code != RESULT_CODE_OK)
			return v1;

		double x1 = v1.value;
		double y1 = v1.value2;

		double x2 = v2.value;
		double y2 = v2.value2;

		double dx = x2 - x1;
		double dy = y2 - y1;

		ret.value = sqrt((dx * dx) + (dy * dy));
		ret.code = RESULT_CODE_OK;
		return ret;
	}
} s_functionDistance;


static class FunctionEqual : public ITerminalEvaluator {
public:			// ITerminalEvaluator interface
	Result Evaluate (const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) const override {
		Result ret;
		ret.type = RESULT_TYPE_SCALAR;
		ret.code = RESULT_CODE_OK;
		ret.value = 0.0f;

		--(*pindex);
		Result v2 = termSource.EvaluateSubexpression(context, pindex);
		if (v2.code != RESULT_CODE_OK)
			return v2;

		--(*pindex);
		Result v1 = termSource.EvaluateSubexpression(context, pindex);
		if (v1.code != RESULT_CODE_OK)
			return v1;

		if (v1.type == v2.type) {
			switch (v1.type) {
			case RESULT_TYPE_SCALAR:
				if (v1.value == v2.value)
					ret.value = 1.0f;
				break;

			case RESULT_TYPE_TOKEN:
				if (v1.token == v2.token)
					ret.value = 1.0f;
				break;

			case RESULT_TYPE_VECTOR2:
				if (v1.value == v2.value && v1.value2 == v2.value2)
					ret.value = 1.0f;
				break;

			default:
				assert(false);
			}
		}

		return ret;
	}
} s_functionEqual;



static class FunctionFuzzyMatch : public ITerminalEvaluator {
public:			// ITerminalEvaluator interface
	Result Evaluate (const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) const override {
		Result ret;
		ret.type = RESULT_TYPE_SCALAR;
		ret.code = RESULT_CODE_OK;
		ret.value = 0.0f;

		--(*pindex);
		Result v2 = termSource.EvaluateSubexpression(context, pindex);
		if (v2.code != RESULT_CODE_OK)
			return v2;

		--(*pindex);
		Result v1 = termSource.EvaluateSubexpression(context, pindex);
		if (v1.code != RESULT_CODE_OK)
			return v1;

		if (v1.type == v2.type) {
			if (v1.type == RESULT_TYPE_TOKEN) {
				std::string token1, token2;
				if (context->ResolveToken(v1.scope, v1.token, &token1) && context->ResolveToken(v2.scope, v2.token, &token2)) {
					if (token2.length() > 0 && token1.find(token2) != std::string::npos)
						ret.value = 1.0f;
				}
			}
		}

		return ret;
	}
} s_functionFuzzyMatch;



static class FunctionLimit : public ITerminalEvaluator {
public:			// ITerminalEvaluator interface
	Result Evaluate(const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) const override {
		--(*pindex);
		Result lim = termSource.EvaluateSubexpression(context, pindex);
		if(lim.code != RESULT_CODE_OK)
			return lim;

		--(*pindex);
		Result v = termSource.EvaluateSubexpression(context, pindex);
		if(v.code != RESULT_CODE_OK)
			return v;

		// TODO - type checking in all functions

		double x = v.value;
		double y = v.value2;

		double mag = sqrt((x * x) + (y * y));
		if(mag <= lim.value)
			return v;

		double scale = lim.value / mag;
		x *= scale;
		y *= scale;

		Result ret;
		ret.code = RESULT_CODE_OK;
		ret.type = RESULT_TYPE_VECTOR2;
		ret.value = x;
		ret.value2 = y;

		return ret;
	}
} s_functionLimit;


static class FunctionNormalize : public ITerminalEvaluator {
public:			// ITerminalEvaluator interface
	Result Evaluate(const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) const override {
		Result ret;
		ret.type = RESULT_TYPE_SCALAR;

		--(*pindex);
		Result v1 = termSource.EvaluateSubexpression(context, pindex);
		if(v1.code != RESULT_CODE_OK)
			return v1;

		double x1 = v1.value;
		double y1 = v1.value2;

		double mag = sqrt((x1 * x1) + (y1 * y1));
		x1 /= mag;
		y1 /= mag;

		ret.value = x1;
		ret.value2 = y1;
		ret.type = RESULT_TYPE_VECTOR2;
		ret.code = RESULT_CODE_OK;
		return ret;
	}
} s_functionNormalize;


static class FunctionRandom : public ITerminalEvaluator {
public:
	FunctionRandom()
		: m_generator((unsigned)(time(nullptr)))
	{ }

public:			// ITerminalEvaluator interface
	Result Evaluate(const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) const override {
		Result ret;

		--(*pindex);

		Result param = termSource.EvaluateSubexpression(context, pindex);
		if(param.code != RESULT_CODE_OK)
			return param;

		std::uniform_real_distribution<double> distribution(-1.0, 1.0);
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

		unsigned parameterListScope = 0;
		unsigned parameterListName = 0;
		if (!termSource.EvaluateScopedToken(*pindex, &parameterListScope, &parameterListName)) {
			ret.code = RESULT_CODE_SYNTAX_ERROR;
			ret.value = 0.0;
			return ret;
		}

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
	if(!std::strcmp(str, "Between"))
		return &s_functionBetween;

	if(!std::strcmp(str, "Distance"))
		return &s_functionDistance;

	if (!std::strcmp(str, "Equal"))
		return &s_functionEqual;

	if (!std::strcmp(str, "FuzzyMatch"))
		return &s_functionFuzzyMatch;

	if(!std::strcmp(str, "Limit"))
		return &s_functionLimit;

	if(!std::strcmp(str, "Normalize"))
		return &s_functionNormalize;

	if(!std::strcmp(str, "Random"))
		return &s_functionRandom;

	if(!std::strcmp(str, "SumOf"))
		return &s_functionSumOfList;

	if(!std::strcmp(str, "Vec"))
		return &s_functionVector;

	return nullptr;
}


