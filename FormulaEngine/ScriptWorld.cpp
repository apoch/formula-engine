#include "Pch.h"

#include "Formula.h"
#include "Actions.h"
#include "PropertyBag.h"
#include "EventHandler.h"
#include "Scriptable.h"
#include "TokenPool.h"
#include "ScriptWorld.h"



ScriptWorld::ScriptWorld(TokenPool * pool, IEngineBinder * binder)
	: m_binder(binder),
	  m_tokens(pool)
{
	assert(m_tokens != nullptr);
}


ScriptWorld::~ScriptWorld() {
	for(auto & instance : m_instances)
		delete instance;
}



void ScriptWorld::AddArchetype(const std::string & name, Scriptable && archetype) {
	unsigned token = m_tokens->AddToken(name);
	assert(m_archetypes.find(token) == m_archetypes.end());

	m_archetypes.emplace(std::make_pair(token, std::move(archetype)));
}


void ScriptWorld::AddScriptable(const std::string & name, Scriptable && scriptable) {
	unsigned token = m_tokens->AddToken(name);
	assert(m_scriptables.find(token) == m_scriptables.end());
		
	m_scriptables.emplace(std::make_pair(token, std::move(scriptable)));
}



void ScriptWorld::DispatchEvent(Scriptable * target, unsigned eventToken) {
	target->GetEvents().TriggerHandlers(this, eventToken, target);
}


bool ScriptWorld::DispatchEvents() {
	bool dispatched = false;

	while(!m_eventQueue.empty()) {
		dispatched = true;
		std::vector<Event> tempqueue = std::move(m_eventQueue);
		for(Event e : tempqueue) {
			if(e.targetToken) {
				Scriptable * scriptable = GetScriptable(e.targetToken);
				if(scriptable)
					DispatchEvent(scriptable, e.nameToken);
			}
			else if(e.directTarget) {
				DispatchEvent(e.directTarget, e.nameToken);
			}
			else {
				for(auto & pair : m_scriptables) {
					DispatchEvent(&pair.second, e.nameToken);
				}
			}
		}
	}

	return dispatched;
}


void ScriptWorld::DumpOverview() const {
	std::cout << "----- Scripting world " << this << " -----\n";
	std::cout << "Contains " << m_scriptables.size() << " objects and " << m_archetypes.size() << " archetypes\n";
	std::cout << "Instantiated " << m_instances.size() << " objects\n";
	std::cout << "----- End world -----" << std::endl;
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


Scriptable * ScriptWorld::InstantiateArchetype(unsigned token) {
	Scriptable * archetype = GetArchetype(token);
	if(!archetype)
		return nullptr;

	Scriptable * instance = archetype->Instantiate();
	m_instances.push_back(instance);

	instance->BindAll(m_binder);

	QueueEvent(instance, m_tokens->AddToken("OnCreate"));

	return instance;
}


void ScriptWorld::QueueBroadcastEvent(const std::string & eventName) {
	QueueEvent(0, eventName);
}

void ScriptWorld::QueueEvent(unsigned targetToken, const std::string & eventName) {
	Event e;
	e.nameToken = m_tokens->AddToken(eventName);
	e.targetToken = targetToken;
	e.directTarget = nullptr;

	m_eventQueue.push_back(e);
}

void ScriptWorld::QueueEvent(Scriptable * target, unsigned eventToken) {
	Event e;
	e.nameToken = eventToken;
	e.targetToken = 0;
	e.directTarget = target;

	m_eventQueue.push_back(e);
}


