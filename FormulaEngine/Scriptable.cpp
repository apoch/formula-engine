#include "stdafx.h"

#include "Formula.h"
#include "Actions.h"
#include "PropertyBag.h"
#include "Scriptable.h"



Scriptable::Scriptable(Scriptable && other)
	: m_scopes(std::move(other.m_scopes)),
	  m_listMemberships(std::move(other.m_listMemberships))
{ }

Scriptable::~Scriptable() {
	for(auto & membership : m_listMemberships)
		membership.owner->ListRemoveEntry(membership.token, *this);
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


