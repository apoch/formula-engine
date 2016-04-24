#include "Pch.h"

#include "Formula.h"



unsigned Formula::s_evaluationCounter = 0;



Formula::Formula ()
	: m_termCount(0)
{
}

Formula::Formula (Formula && other)
	: m_termCount(other.m_termCount)
{
	for (unsigned i = 0; i < m_termCount; ++i)
		m_termBuffer[i] = other.m_termBuffer[i];
}

Formula::Formula (const Formula & other)
	: m_termCount(other.m_termCount)
{
	for (unsigned i = 0; i < m_termCount; ++i)
		m_termBuffer[i] = other.m_termBuffer[i];
}


Formula & Formula::operator= (Formula && other) {
	m_termCount = other.m_termCount;
	for (unsigned i = 0; i < m_termCount; ++i)
		m_termBuffer[i] = other.m_termBuffer[i];

	return *this;
}

Formula & Formula::operator= (const Formula & other) {
	m_termCount = other.m_termCount;
	for (unsigned i = 0; i < m_termCount; ++i)
		m_termBuffer[i] = other.m_termBuffer[i];

	return *this;
}


Result Formula::Evaluate (const IFormulaContext * context) const {
	Result ret;

	++s_evaluationCounter;

	ret.code = RESULT_CODE_OK;
	if (!m_termCount) {
		ret.payload.num.value = 0.0;
		return ret;
	}

	unsigned index = m_termCount - 1;
	ret = EvaluateSubexpression(context, &index);

	assert(index == 0);

	return ret;
}


Result Formula::EvaluateSubexpression (const IFormulaContext * context, unsigned * pindex) const {
	Result ret;

	const Term & term = m_termBuffer[*pindex];

	switch (term.type) {
		case Term::TERM_TYPE_TOKEN:
			{
				auto newContext = context->ResolveContext(term.payload.scopedToken.scope);
				if (!newContext)
					newContext = context;

				ret = newContext->ResolveNumber(*newContext, 0, term.payload.scopedToken.token);
			}
			break;

		case Term::TERM_TYPE_LITERAL:
			{
				ret.type = RESULT_TYPE_SCALAR;
				ret.code = RESULT_CODE_OK;
				ret.payload.num.value = term.payload.literalValue;	
			}
			break;

		case Term::TERM_TYPE_EVALUATOR:
			ret = term.payload.evaluator(context, *this, pindex);
			break;

		case Term::TERM_TYPE_OPERATOR:
			{
				Operator op = term.payload.op;

				--(*pindex);
				Result right = EvaluateSubexpression(context, pindex);

				--(*pindex);
				Result left = EvaluateSubexpression(context, pindex);

		    	if (left.type != right.type) {
					ret.code = RESULT_CODE_TYPE_ERROR;

					if (left.type == RESULT_TYPE_SCALAR && right.type == RESULT_TYPE_VECTOR2) {
						if (op == OPERATOR_MULTIPLY) {
							ret.type = RESULT_TYPE_VECTOR2;
							ret.code = RESULT_CODE_OK;
							ret.payload.num.value = left.payload.num.value * right.payload.num.value;
							ret.payload.num.value2 = left.payload.num.value * right.payload.num.value2;
						}
					}
					else if (left.type == RESULT_TYPE_VECTOR2 && right.type == RESULT_TYPE_SCALAR) {
						if (op == OPERATOR_MULTIPLY) {
							ret.type = RESULT_TYPE_VECTOR2;
							ret.code = RESULT_CODE_OK;
							ret.payload.num.value = left.payload.num.value * right.payload.num.value;
							ret.payload.num.value2 = left.payload.num.value2 * right.payload.num.value;
						}
						else if (op == OPERATOR_DIVIDE) {
							ret.type = RESULT_TYPE_VECTOR2;
							ret.code = RESULT_CODE_OK;
							ret.payload.num.value = left.payload.num.value / right.payload.num.value;
							ret.payload.num.value2 = left.payload.num.value2 / right.payload.num.value;
						}
					}
				}
				else {
					ret.code = RESULT_CODE_OK;
					ret.type = left.type;

					switch (op) {
					case OPERATOR_ADD:			ret.payload.num.value = left.payload.num.value + right.payload.num.value;		break;
					case OPERATOR_SUBTRACT:		ret.payload.num.value = left.payload.num.value - right.payload.num.value;		break;
					case OPERATOR_MULTIPLY:		ret.payload.num.value = left.payload.num.value * right.payload.num.value;		break;
					case OPERATOR_DIVIDE:		ret.payload.num.value = left.payload.num.value / right.payload.num.value;		break;
					default:
						ret.code = RESULT_CODE_SYNTAX_ERROR;
						ret.payload.num.value = 0.0;
						break;
					}

					if (ret.code == RESULT_CODE_OK && ret.type == RESULT_TYPE_VECTOR2) {
						switch (op) {
						case OPERATOR_ADD:			ret.payload.num.value2 = left.payload.num.value2 + right.payload.num.value2;		break;
						case OPERATOR_SUBTRACT:		ret.payload.num.value2 = left.payload.num.value2 - right.payload.num.value2;		break;

						case OPERATOR_MULTIPLY:
						case OPERATOR_DIVIDE:
							ret.code = RESULT_CODE_TYPE_ERROR;
							break;
						}
					}
				}
			}
			break;
	}

	return ret;
}

bool Formula::EvaluateScopedToken (unsigned index, unsigned * outScope, unsigned * outToken) const {
	const Term & term = m_termBuffer[index];

	if (term.type != Term::TERM_TYPE_TOKEN)
		return false;

	*outScope = term.payload.scopedToken.scope;
	*outToken = term.payload.scopedToken.token;

	return true;
}


void Formula::Push (ValueT literalValue) {
	m_termBuffer[m_termCount].type = Term::TERM_TYPE_LITERAL;
	m_termBuffer[m_termCount].payload.literalValue = literalValue;

	++m_termCount;		//  TODO - ensure that the Push() overloads don't overflow the buffer
}

void Formula::Push (FTerminalEvaluator evaluator) {
	m_termBuffer[m_termCount].type = Term::TERM_TYPE_EVALUATOR;
	m_termBuffer[m_termCount].payload.evaluator = evaluator;

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


