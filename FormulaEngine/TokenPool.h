//
// FormulaEngine Project
// By Mike Lewis - 2015
//
// Mapper for condensing strings to unique unsigned integer IDs
//
// Given an input string, the token pool is designed to return a
// unique but stable ID - that is, if the same string is provided
// to the token pool later on, the same ID should be retured.
//
// Moreover, the token pool must support going from a unique ID
// back to the original string.
//

#pragma once


class TokenPool {
public:
	unsigned AddToken(const std::string & str);
	const std::string & GetStringFromToken(unsigned token) const;

private:
	std::vector<std::string> m_pool;
};


