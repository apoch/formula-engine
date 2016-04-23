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
unsigned TokenPool::AddToken (const char token[]) {
	auto iter = m_fastLookup.find(token);
	if (iter != m_fastLookup.end())
		return iter->second;

	m_pool.emplace_back(token);

	unsigned id = static_cast<unsigned>(m_pool.size());
	m_fastLookup.emplace(token, id);

	return id;
}


unsigned TokenPool::AddToken (const std::string & token) {
	auto iter = m_fastLookup.find(token);
	if (iter != m_fastLookup.end())
		return iter->second;

	m_pool.emplace_back(token);

	unsigned id = static_cast<unsigned>(m_pool.size());
	m_fastLookup.emplace(token, id);

	return id;
}


unsigned TokenPool::FindToken (const std::string & token) {
	auto iter = m_fastLookup.find(token);
	if (iter != m_fastLookup.end())
		return iter->second;

	return 0;
}


//
// Given a token, look up the original string for it
//
const std::string & TokenPool::GetStringFromToken (unsigned token) const {
	assert(token != 0);
	
	unsigned index = token - 1;
	assert(index < m_pool.size());

	return m_pool[index];
}

