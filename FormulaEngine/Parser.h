#pragma once


class Formula;
class TokenPool;
struct ITerminalEvaluator;


class FormulaParser {
public:			// Parsing interface
	Formula Parse (const std::string & formula, TokenPool * tokenPool);

private:		// Internal helpers
	bool ParseToken (Formula * formula, std::string::const_iterator * iter, const std::string::const_iterator & enditer, TokenPool * tokenPool);

private:		// Internal helper structures
	struct Token {
		char op;
		const ITerminalEvaluator * eval;
	};

private:		// Internal state
	std::vector<Token> m_tokenStack;
};


