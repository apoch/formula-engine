#include "Pch.h"

#include "Parser.h"
#include "Formula.h"
#include "TokenPool.h"
#include "Functions.h"


static bool IsOperator(char c) {
	switch(c) {
	case '+':		return true;
	case '-':		return true;
	case '*':		return true;
	case '/':		return true;
	}

	return false;
}

static unsigned GetPrecedence(char c) {
	switch(c) {
	case '+':		return 1;
	case '-':		return 1;
	case '*':		return 2;
	case '/':		return 2;
	}

	return 0;
}

static Formula::Operator GetOperatorFromToken(char optoken) {
	switch(optoken) {
	case '+':		return Formula::OPERATOR_ADD;
	case '-':		return Formula::OPERATOR_SUBTRACT;
	case '*':		return Formula::OPERATOR_MULTIPLY;
	case '/':		return Formula::OPERATOR_DIVIDE;
	}

	return Formula::OPERATOR_ERROR;
}


Formula FormulaParser::Parse(const std::string & formula, TokenPool * tokenPool) {
	m_tokenStack.clear();

	Formula ret;

	auto iter = formula.begin();
	while(iter != formula.end()) {
		if(!ParseToken(&ret, &iter, formula.end(), tokenPool)) {
			return Formula();
		}
	}

	while(!m_tokenStack.empty()) {
		if(m_tokenStack.back().op == '(' || m_tokenStack.back().op == ')') {
			return Formula();
		}

		if(m_tokenStack.back().op)
			ret.Push(GetOperatorFromToken(m_tokenStack.back().op));
		else
			ret.Push(*m_tokenStack.back().eval);

		m_tokenStack.pop_back();
	}

	return ret;
}


bool FormulaParser::ParseToken(Formula * formula, std::string::const_iterator * iter, const std::string::const_iterator & enditer, TokenPool * tokenPool) {
	while(*iter != enditer && std::isblank(**iter))
		++(*iter);

	if(*iter == enditer)
		return true;

	if(std::isdigit(**iter) || (**iter == '.')) {
		auto startpos = *iter;

		while(*iter != enditer && (std::isdigit(**iter) || (**iter == '.'))) {
			++(*iter);
		}

		std::string str(startpos, *iter);
		std::istringstream convert(str);
		ValueT value = 0.0;
		if(!(convert >> value))
			return false;

		formula->Push(value);
	}
	else if(**iter == ',') {
		++(*iter);

		while(!m_tokenStack.empty() && m_tokenStack.back().op != '(') {
			if(m_tokenStack.back().op)
				formula->Push(GetOperatorFromToken(m_tokenStack.back().op));
			else
				formula->Push(*m_tokenStack.back().eval);
			m_tokenStack.pop_back();
		}

		if(m_tokenStack.empty())
			return false;
	}
	else if(**iter == '(') {
		Token t;
		t.op = '(';
		m_tokenStack.emplace_back(t);
		++(*iter);
	}
	else if(**iter == ')') {
		++(*iter);

		while(!m_tokenStack.empty() && m_tokenStack.back().op != '(') {
			if(m_tokenStack.back().op)
				formula->Push(GetOperatorFromToken(m_tokenStack.back().op));
			else
				formula->Push(*m_tokenStack.back().eval);
			m_tokenStack.pop_back();
		}

		if(m_tokenStack.empty())
			return false;

		m_tokenStack.pop_back();

		if(!m_tokenStack.empty() && m_tokenStack.back().op == 0) {
			formula->Push(*m_tokenStack.back().eval);
			m_tokenStack.pop_back();
		}
	}
	else if(IsOperator(**iter)) {
		while(!m_tokenStack.empty() && IsOperator(m_tokenStack.back().op)) {
			if(GetPrecedence(**iter) <= GetPrecedence(m_tokenStack.back().op)) {
				formula->Push(GetOperatorFromToken(m_tokenStack.back().op));
				m_tokenStack.pop_back();
			}
			else
				break;
		}

		Token t;
		t.op = **iter;
		m_tokenStack.emplace_back(t);

		++(*iter);
	}
	else {
		auto startpos = *iter;

		while(*iter != enditer) {
			if(std::isblank(**iter))
				break;

			if(std::isdigit(**iter) || (**iter == '.'))
				break;

			if(IsOperator(**iter))
				break;

			if(**iter == '(' || **iter == ')')
				break;

			if(**iter == ',')
				break;

			++(*iter);
		}

		std::string rawToken(startpos, *iter);
		FTerminalEvaluator eval = GetFunctionEvaluatorByName(rawToken.c_str());
		if(eval) {
			Token t;
			t.op = 0;
			t.eval = eval;
			m_tokenStack.emplace_back(t);
		}
		else {
			std::string::size_type pos = rawToken.find(':');
			if(pos != std::string::npos) {
				std::string scopeName = rawToken.substr(0, pos);
				std::string scopedToken = rawToken.substr(pos + 1);

				unsigned scope = tokenPool->AddToken(scopeName);
				unsigned token = tokenPool->AddToken(scopedToken);
				formula->Push(scope, token);
			}
			else {
				unsigned token = tokenPool->AddToken(rawToken);
				formula->Push(0, token);
			}
		}
	}

	return true;
}


