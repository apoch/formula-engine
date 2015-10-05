#include "Pch.h"

#include "Formula.h"
#include "Actions.h"
#include "PropertyBag.h"
#include "EventHandler.h"
#include "Scriptable.h"

#include "EngineBind.h"



Scriptable::Scriptable(Scriptable && other)
	: m_scopes(std::move(other.m_scopes)),
	  m_listMemberships(std::move(other.m_listMemberships)),
	  m_bindings(std::move(other.m_bindings))
{
	m_eventHandlers = other.m_eventHandlers;
	other.m_eventHandlers = nullptr;
}

Scriptable::~Scriptable() {
	for(auto & membership : m_listMemberships)
		membership.owner->ListRemoveEntry(membership.token, *this);

	for(auto & pair : m_bindings)
		delete pair.second;

	if(m_eventHandlers)
		m_eventHandlers->DecRef();
}


void Scriptable::AddBinding(unsigned bindingToken) {
	assert(m_bindings.find(bindingToken) == m_bindings.end());

	m_bindings[bindingToken] = nullptr;
}


void Scriptable::BindAll(IEngineBinder * binder, ScriptWorld * world) {
	for(auto & pair : m_bindings) {
		if(pair.second == nullptr) {
			pair.second = binder->CreateBinding(this, world, pair.first);
		}
	}
}

IEngineBinding * Scriptable::GetBinding(unsigned token) {
	auto iter = m_bindings.find(token);
	if(iter == m_bindings.end())
		return nullptr;

	return iter->second;
}


Scriptable * Scriptable::Instantiate() const {
	Scriptable * clone = new Scriptable;
	clone->m_eventHandlers = m_eventHandlers;
	clone->m_scopes.InstantiateFrom(m_scopes);
	clone->m_bindings = m_bindings;

	if(m_eventHandlers)
		m_eventHandlers->IncRef();

	return clone;
}


void Scriptable::OnListMembershipAdded(unsigned listToken, IActionPerformer * owner) const {
	Membership membership;
	membership.owner = owner;
	membership.token = listToken;
	m_listMemberships.push_back(membership);
}

void Scriptable::OnListMembershipRemoved(unsigned listToken, IActionPerformer * owner) const {
	for(auto iter = m_listMemberships.begin(); iter != m_listMemberships.end(); ) {
		if(iter->owner == owner && iter->token == listToken)
			iter = m_listMemberships.erase(iter);
		else
			++iter;
	}
}


