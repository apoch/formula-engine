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
	assert(m_eventHandlers.find(eventToken) == m_eventHandlers.end());

	m_eventHandlers.emplace(eventToken, std::move(actions));
}

void EventHandlerSet::TriggerHandlers (ScriptWorld * world, unsigned eventToken, Scriptable * target, const IFormulaPropertyBag * paramBag) const {
	auto iter = m_eventHandlers.find(eventToken);
	if (iter != m_eventHandlers.end()) {
		unsigned magic = world->GetMagicTokenForEvent();
		iter->second.Execute(world, target, magic, paramBag);
	}
}


void EventHandlerSet::IncRef() {
	++m_refCount;
}

void EventHandlerSet::DecRef() {
	if (--m_refCount == 0)
		delete this;
}

