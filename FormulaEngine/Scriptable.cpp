#include "Pch.h"

#include "Formula.h"
#include "Actions.h"
#include "PropertyBag.h"
#include "EventHandler.h"
#include "Scriptable.h"



Scriptable::Scriptable(Scriptable && other)
	: m_scopes(std::move(other.m_scopes)),
	  m_listMemberships(std::move(other.m_listMemberships)),
	  m_eventHandlers(std::move(other.m_eventHandlers))
{ }

Scriptable::~Scriptable() {
	for(auto & membership : m_listMemberships)
		membership.owner->ListRemoveEntry(membership.token, *this);
}


Scriptable * Scriptable::Instantiate() const {
	Scriptable * clone = new Scriptable;
	clone->m_eventHandlers = m_eventHandlers;
	clone->m_scopes.InstantiateFrom(m_scopes);

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


