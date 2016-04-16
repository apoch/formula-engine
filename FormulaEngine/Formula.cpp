#include "Pch.h"

#include "Formula.h"



unsigned Formula::s_evaluationCounter = 0;



Formula::Formula ()
	: m_termCount(0)
{
}


Result Formula::Evaluate (const IFormulaContext * context) const {
	Result ret;

	++s_evaluationCounter;

	ret.code = RESULT_CODE_OK;
	if (!m_termCount) {
		ret.value = 0.0;
		return ret;
	}

	unsigned index = m_termCount - 1;
	ret = EvaluateSubexpression(context, &index);

	if (index > 0) {
		ret.code = RESULT_CODE_SYNTAX_ERROR;
		ret.value = 0.0;
	}

	return ret;
}


Result Formula::EvaluateFunction (const IFormulaContext * context, unsigned * pindex) const {
	return m_termBuffer[*pindex].payload.evaluator->Evaluate(context, *this, pindex);
}

Result Formula::EvaluateSubexpression (const IFormulaContext * context, unsigned * pindex) const {
	if (m_termBuffer[*pindex].type == Term::TERM_TYPE_EVALUATOR)
		return EvaluateFunction(context, pindex);

	if ((*pindex == 0) || (m_termBuffer[*pindex].type != Term::TERM_TYPE_OPERATOR))
		return EvaluateTerminal(context, *pindex);

	Operator op = m_termBuffer[*pindex].payload.op;

	--(*pindex);
	Result right = EvaluateSubexpression(context, pindex);
	if (right.code != RESULT_CODE_OK)
		return right;

	--(*pindex);
	Result left = EvaluateSubexpression(context, pindex);
	if (left.code != RESULT_CODE_OK)
		return left;

	if (left.type != right.type) {
		if (left.type == RESULT_TYPE_SCALAR && right.type == RESULT_TYPE_VECTOR2) {
			if (op == OPERATOR_MULTIPLY) {
				Result ret;
				ret.type = RESULT_TYPE_VECTOR2;
				ret.code = RESULT_CODE_OK;
				ret.value = left.value * right.value;
				ret.value2 = left.value * right.value2;
				return ret;
			}
		}
		else if (left.type == RESULT_TYPE_VECTOR2 && right.type == RESULT_TYPE_SCALAR) {
			if (op == OPERATOR_MULTIPLY) {
				Result ret;
				ret.type = RESULT_TYPE_VECTOR2;
				ret.code = RESULT_CODE_OK;
				ret.value = left.value * right.value;
				ret.value2 = left.value2 * right.value;
				return ret;
			}
			else if (op == OPERATOR_DIVIDE) {
				Result ret;
				ret.type = RESULT_TYPE_VECTOR2;
				ret.code = RESULT_CODE_OK;
				ret.value = left.value / right.value;
				ret.value2 = left.value2 / right.value;
				return ret;
			}
		}

		Result err;
		err.code = RESULT_CODE_TYPE_ERROR;
		return err;
	}

	Result ret;
	ret.code = RESULT_CODE_OK;
	ret.type = left.type;

	switch (op) {
	case OPERATOR_ADD:			ret.value = left.value + right.value;		break;
	case OPERATOR_SUBTRACT:		ret.value = left.value - right.value;		break;
	case OPERATOR_MULTIPLY:		ret.value = left.value * right.value;		break;
	case OPERATOR_DIVIDE:		ret.value = left.value / right.value;		break;
	default:
		ret.code = RESULT_CODE_SYNTAX_ERROR;
		ret.value = 0.0;
		return ret;
	}

	if (left.type == RESULT_TYPE_VECTOR2) {
		switch (op) {
		case OPERATOR_ADD:			ret.value2 = left.value2 + right.value2;		break;
		case OPERATOR_SUBTRACT:		ret.value2 = left.value2 - right.value2;		break;

		case OPERATOR_MULTIPLY:
		case OPERATOR_DIVIDE:
			ret.code = RESULT_CODE_TYPE_ERROR;
			break;
		}
	}

	return ret;
}

Result Formula::EvaluateTerminal (const IFormulaContext * context, unsigned index) const {
	Result ret;

	if (m_termBuffer[index].type == Term::TERM_TYPE_TOKEN) {
		auto newContext = context->ResolveContext(m_termBuffer[index].payload.scopedToken.scope);
		if (!newContext)
			newContext = context;

		ret = newContext->ResolveNumber(*newContext, 0, m_termBuffer[index].payload.scopedToken.token);
		return ret;
	}

	if (m_termBuffer[index].type != Term::TERM_TYPE_LITERAL) {
		ret.code = RESULT_CODE_SYNTAX_ERROR;
		ret.value = 0.0;
		return ret;
	}

	ret.type = RESULT_TYPE_SCALAR;
	ret.code = RESULT_CODE_OK;
	ret.value = m_termBuffer[index].payload.literalValue;
	return ret;
}

bool Formula::EvaluateScopedToken (unsigned index, unsigned * outScope, unsigned * outToken) const {
	if (m_termBuffer[index].type != Term::TERM_TYPE_TOKEN)
		return false;

	if (outScope)
		*outScope = m_termBuffer[index].payload.scopedToken.scope;

	if (outToken)
		*outToken = m_termBuffer[index].payload.scopedToken.token;

	return true;
}


void Formula::Push (double literalValue) {
	m_termBuffer[m_termCount].type = Term::TERM_TYPE_LITERAL;
	m_termBuffer[m_termCount].payload.literalValue = literalValue;

	++m_termCount;		//  TODO - ensure that the Push() overloads don't overflow the buffer
}

void Formula::Push (const ITerminalEvaluator & evaluator) {
	m_termBuffer[m_termCount].type = Term::TERM_TYPE_EVALUATOR;
	m_termBuffer[m_termCount].payload.evaluator = const_cast<ITerminalEvaluator *>(&evaluator);

	++m_termCount;
}

void Formula::Push (Operator op) {
	m_termBuffer[m_termCount].type = Term::TERM_TYPE_OPERATOR;
	m_termBuffer[m_termCount].payload.op = op;

	++m_termCount;
}

void Formula::Push (unsigned scope, unsigned token) {
	m_termBuffer[m_termCount].type = Term::TERM_TYPE_TOKEN;
	m_termBuffer[m_termCount].payload.scopedToken.scope = scope;
	m_termBuffer[m_termCount].payload.scopedToken.token = token;

	++m_termCount;
}



unsigned Formula::GetEvaluationCounter () {
	return s_evaluationCounter;
}


