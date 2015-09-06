#include "stdafx.h"

#include "Formula.h"
#include "Actions.h"
#include "PropertyBag.h"
#include "Scriptable.h"
#include "TokenPool.h"
#include "ScriptWorld.h"



void ScriptWorld::AddArchetype(const std::string & name, Scriptable && archetype) {
	unsigned token = m_tokens.AddToken(name);
	assert(m_archetypes.find(token) == m_archetypes.end());

	m_archetypes.emplace(std::make_pair(token, std::move(archetype)));
}


void ScriptWorld::AddScriptable(const std::string & name, Scriptable && scriptable) {
	unsigned token = m_tokens.AddToken(name);
	assert(m_scriptables.find(token) == m_scriptables.end());
		
	m_scriptables.emplace(std::make_pair(token, std::move(scriptable)));
}



void ScriptWorld::DispatchEvent(Scriptable * target, unsigned eventToken) {
	// TODO - implement events
}


void ScriptWorld::DispatchEvents() {
	while(!m_eventQueue.empty()) {
		std::vector<Event> tempqueue = std::move(m_eventQueue);
		for(Event e : tempqueue) {
			if(e.targetToken) {
				Scriptable * scriptable = GetScriptable(e.targetToken);
				if(scriptable)
					DispatchEvent(scriptable, e.nameToken);
			}
			else {
				for(auto & pair : m_scriptables) {
					DispatchEvent(&pair.second, e.nameToken);
				}
			}
		}
	}
}


Scriptable * ScriptWorld::GetArchetype(unsigned token) {
	auto iter = m_archetypes.find(token);
	if(iter == m_archetypes.end())
		return nullptr;

	return &iter->second;
}

Scriptable * ScriptWorld::GetScriptable(unsigned token) {
	auto iter = m_scriptables.find(token);
	if(iter == m_scriptables.end())
		return nullptr;

	return &iter->second;
}



void ScriptWorld::QueueBroadcastEvent(const std::string & eventName) {
	QueueEvent(0, eventName);
}

void ScriptWorld::QueueEvent(unsigned targetToken, const std::string & eventName) {
	Event e;
	e.nameToken = m_tokens.AddToken(eventName);
	e.targetToken = targetToken;

	m_eventQueue.push_back(e);
}

