#include "Pch.h"

#include "Functions.h"
#include "Formula.h"

#include <ctime>



Result FunctionBetween (const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) {
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

	ret.payload.num.value = (v1.payload.num.value < t.payload.num.value && t.payload.num.value < v2.payload.num.value) ? ValueT(1.0) : ValueT(0.0);
	ret.code = RESULT_CODE_OK;
	return ret;
}


Result FunctionDistance (const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) {
	Result ret;
	ret.type = RESULT_TYPE_SCALAR;

	--(*pindex);
	Result v2 = termSource.EvaluateSubexpression(context, pindex);
	if (v2.code != RESULT_CODE_OK)
		return v2;

	--(*pindex);
	Result v1 = termSource.EvaluateSubexpression(context, pindex);
	if (v1.code != RESULT_CODE_OK)
		return v1;

	ValueT x1 = v1.payload.num.value;
	ValueT y1 = v1.payload.num.value2;

	ValueT x2 = v2.payload.num.value;
	ValueT y2 = v2.payload.num.value2;

	ValueT dx = x2 - x1;
	ValueT dy = y2 - y1;

	ret.payload.num.value = sqrt((dx * dx) + (dy * dy));
	ret.code = RESULT_CODE_OK;
	return ret;
}

Result FunctionEqual (const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) {
	Result ret;
	ret.type = RESULT_TYPE_SCALAR;
	ret.code = RESULT_CODE_OK;
	ret.payload.num.value = 0.0f;

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
			if (v1.payload.num.value == v2.payload.num.value)
				ret.payload.num.value = 1.0f;
			break;

		case RESULT_TYPE_TOKEN:
			if (v1.payload.txt.token == v2.payload.txt.token)
				ret.payload.num.value = 1.0f;
			break;

		case RESULT_TYPE_VECTOR2:
			if (v1.payload.num.value == v2.payload.num.value && v1.payload.num.value2 == v2.payload.num.value2)
				ret.payload.num.value = 1.0f;
			break;

		default:
			assert(false);
		}
	}

	return ret;
}



Result FunctionFuzzyMatch (const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) {
	Result ret;
	ret.type = RESULT_TYPE_SCALAR;
	ret.code = RESULT_CODE_OK;
	ret.payload.num.value = 0.0f;

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
			if (context->ResolveToken(v1.payload.txt.scope, v1.payload.txt.token, &token1) && context->ResolveToken(v2.payload.txt.scope, v2.payload.txt.token, &token2)) {
				if (token2.length() > 0 && token1.find(token2) != std::string::npos)
					ret.payload.num.value = 1.0f;

				// TODO - richer fuzzy text matching?
			}
		}
	}

	return ret;
}


Result FunctionLess (const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) {
	Result ret;
	ret.type = RESULT_TYPE_SCALAR;
	ret.code = RESULT_CODE_OK;
	ret.payload.num.value = 0.0f;

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
			if (v1.payload.num.value < v2.payload.num.value)
				ret.payload.num.value = 1.0f;
			break;

		default:
			assert(false);
		}
	}

	return ret;
}


Result FunctionLimit (const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) {
	--(*pindex);
	Result lim = termSource.EvaluateSubexpression(context, pindex);
	if(lim.code != RESULT_CODE_OK)
		return lim;

	--(*pindex);
	Result v = termSource.EvaluateSubexpression(context, pindex);
	if(v.code != RESULT_CODE_OK)
		return v;

	// TODO - type checking in all functions

	ValueT x = v.payload.num.value;
	ValueT y = v.payload.num.value2;

	ValueT mag = sqrt((x * x) + (y * y));
	if(mag <= lim.payload.num.value)
		return v;

	ValueT scale = lim.payload.num.value / mag;
	x *= scale;
	y *= scale;

	Result ret;
	ret.code = RESULT_CODE_OK;
	ret.type = RESULT_TYPE_VECTOR2;
	ret.payload.num.value = x;
	ret.payload.num.value2 = y;

	return ret;
}


Result FunctionNormalize (const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) {
	Result ret;
	ret.type = RESULT_TYPE_SCALAR;

	--(*pindex);
	Result v1 = termSource.EvaluateSubexpression(context, pindex);
	if (v1.code != RESULT_CODE_OK)
		return v1;

	ValueT x1 = v1.payload.num.value;
	ValueT y1 = v1.payload.num.value2;

	ValueT mag = sqrt((x1 * x1) + (y1 * y1));
	x1 /= mag;
	y1 /= mag;

	ret.payload.num.value = x1;
	ret.payload.num.value2 = y1;
	ret.type = RESULT_TYPE_VECTOR2;
	ret.code = RESULT_CODE_OK;
	return ret;
}

Result FunctionRandom (const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) {
	static std::default_random_engine s_generator((unsigned)(time(nullptr)));

	Result ret;

	--(*pindex);

	Result param = termSource.EvaluateSubexpression(context, pindex);
	if (param.code != RESULT_CODE_OK)
		return param;

	std::uniform_real_distribution<ValueT> distribution(0.0, param.payload.num.value);
	ret.payload.num.value = distribution(s_generator);
	ret.code = RESULT_CODE_OK;

	return ret;
}



Result FunctionRound (const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) {
	Result ret;

	--(*pindex);

	Result param = termSource.EvaluateSubexpression(context, pindex);
	if (param.code != RESULT_CODE_OK)
		return param;

	ret.code = RESULT_CODE_OK;
	ret.payload.num.value = std::round(param.payload.num.value);

	return ret;
}


Result FunctionSumOfList (const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) {
	Result ret;

	--(*pindex);

	unsigned parameterListScope = 0;
	unsigned parameterListName = 0;
	if (!termSource.EvaluateScopedToken(*pindex, &parameterListScope, &parameterListName)) {
		ret.code = RESULT_CODE_SYNTAX_ERROR;
		ret.payload.num.value = 0.0;
		return ret;
	}

	if (!context) {
		ret.code = RESULT_CODE_MISSING_DEFINITION;
		ret.payload.num.value = 0.0;
		return ret;
	}

	ListResult listresult = context->ResolveList(*context, parameterListScope, parameterListName);
	if (listresult.code != RESULT_CODE_OK) {
		ret.code = listresult.code;
		ret.payload.num.value = 0.0;
		return ret;
	}

	ret.payload.num.value = 0.0;
	for (auto val : listresult.values)
		ret.payload.num.value += val;

	ret.code = RESULT_CODE_OK;
	return ret;
}


Result FunctionVector (const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) {
	// Always retrieve parameter values right to left

	--(*pindex);
	Result yparam = termSource.EvaluateSubexpression(context, pindex);

	--(*pindex);
	Result xparam = termSource.EvaluateSubexpression(context, pindex);

	Result ret;
	ret.code = RESULT_CODE_OK;
	ret.type = RESULT_TYPE_VECTOR2;
	ret.payload.num.value = xparam.payload.num.value;
	ret.payload.num.value2 = yparam.payload.num.value;
	return ret;
}


struct HashFunc {
	int operator() (const char * str) const {
		int seed = 131;
		int hash = 0;

		while (*str) {
			hash = (hash * seed) + (*str);
			++str;
		}

		return (hash & 0x7fffffff);
	}
};

struct EqualityFunc {
	bool operator() (const char * a, const char * b) const {
		return (std::strcmp(a, b) == 0);
	}
};


FTerminalEvaluator GetFunctionEvaluatorByName (const char str[]) {
	static const std::unordered_map<const char *, FTerminalEvaluator, HashFunc, EqualityFunc> evalNames = 
	{
		{ "Between",	&FunctionBetween	},
		{ "Distance",	&FunctionDistance	},
		{ "Equal",		&FunctionEqual		},
		{ "FuzzyMatch", &FunctionFuzzyMatch	},
		{ "Less",		&FunctionLess		},
		{ "Limit",		&FunctionLimit		},
		{ "Normalize",	&FunctionNormalize	},
		{ "Random",		&FunctionRandom		},
		{ "Round",		&FunctionRound		},
		{ "SumOf",		&FunctionSumOfList	},
		{ "Vec",		&FunctionVector		},
	};

	auto iter = evalNames.find(str);
	if (iter != evalNames.end())
		return iter->second;

	return nullptr;
}


