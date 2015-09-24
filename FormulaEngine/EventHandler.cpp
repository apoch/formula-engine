#include "Pch.h"

#include "Formula.h"
#include "Actions.h"
#include "TokenPool.h"
#include "PropertyBag.h"
#include "EventHandler.h"
#include "Scriptable.h"
#include "ScriptWorld.h"



void EventHandlerSet::AddHandler(unsigned eventToken, ActionSet && actions) {
	m_eventHandlers.emplace(std::make_pair(eventToken, std::move(actions)));
}

void EventHandlerSet::TriggerHandlers(ScriptWorld * world, unsigned eventToken, Scriptable * target, const IPropertyBag * paramBag) {
	unsigned magic = world->GetTokenPool().AddToken("event");
	auto range = m_eventHandlers.equal_range(eventToken);
	for(auto iter = range.first; iter != range.second; ++iter) {
		iter->second.Execute(world, target, magic, paramBag);
	}
}



