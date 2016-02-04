//
// FormulaEngine Project
// By Mike Lewis - 2015
//
// Mapper for condensing strings to unique unsigned integer IDs
//
// This module implements a simple and minimal version of the token
// pool concept, based on the requirements detailed in TokenPool.h.
//
// Note that we choose to use monotonic increasing IDs based on
// indices into a vector; this is not as efficient as it could be,
// but it's effective and easy to think about. Most of the usage
// of this object is meant to occur at load time and/or duing a
// heavy debugging session, so performance is not yet a concern.
//

#include "Pch.h"

#include "TokenPool.h"


//
// Add a string into the pool and get its token back
//
unsigned TokenPool::AddToken(const char token[]) {
	for(unsigned i = 0; i < m_pool.size(); ++i) {
		if(m_pool[i] == token)
			return i + 1;
	}

	m_pool.emplace_back(token);
	return static_cast<unsigned>(m_pool.size());
}


unsigned TokenPool::AddToken(const std::string & token) {
	for(unsigned i = 0; i < m_pool.size(); ++i) {
		if(m_pool[i] == token)
			return i + 1;
	}

	m_pool.emplace_back(token);
	return static_cast<unsigned>(m_pool.size());
}


unsigned TokenPool::FindToken (const std::string & token) {
	for (unsigned i = 0; i < m_pool.size(); ++i) {
		if (m_pool[i] == token)
			return i + 1;
	}

	return 0;
}


//
// Given a token, look up the original string for it
//
const std::string & TokenPool::GetStringFromToken(unsigned token) const {
	assert(token != 0);
	
	unsigned index = token - 1;
	assert(index < m_pool.size());

	return m_pool[index];
}

