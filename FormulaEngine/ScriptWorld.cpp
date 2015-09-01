#include "stdafx.h"

#include "Formula.h"
#include "Actions.h"
#include "PropertyBag.h"
#include "Scriptable.h"
#include "TokenPool.h"
#include "ScriptWorld.h"


void ScriptWorld::AddScriptable(const std::string & name, Scriptable && scriptable) {
	unsigned token = m_tokens.AddToken(name);
	assert(m_scriptables.find(token) == m_scriptables.end());
		
	m_scriptables.emplace(std::make_pair(token, std::move(scriptable)));
}


Scriptable * ScriptWorld::GetScriptable(unsigned token) {
	auto iter = m_scriptables.find(token);
	if(iter == m_scriptables.end())
		return nullptr;

	return &iter->second;
}

