#include "Pch.h"

#include "Interfaces.h"
#include "Formula.h"
#include "Actions.h"
#include "TokenPool.h"
#include "PropertyBag.h"
#include "EventHandler.h"
#include "Scriptable.h"
#include "ScriptWorld.h"



void EventHandlerSet::AddHandler (unsigned eventToken, ActionSet && actions) {
	m_eventHandlers.emplace(std::make_pair(eventToken, std::move(actions)));
}

void EventHandlerSet::TriggerHandlers (ScriptWorld * world, unsigned eventToken, Scriptable * target, const IFormulaPropertyBag * paramBag) const {
	unsigned magic = world->GetTokenPool().AddToken("event");		// TODO - improve
	auto range = m_eventHandlers.equal_range(eventToken);
	for(auto iter = range.first; iter != range.second; ++iter) {
		iter->second.Execute(world, target, magic, paramBag);
	}
}


void EventHandlerSet::IncRef() {
	++m_refCount;
}

void EventHandlerSet::DecRef() {
	if(--m_refCount == 0)
		delete this;
}

