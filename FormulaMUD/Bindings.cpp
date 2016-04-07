//
// FormulaEngine Project
// By Mike Lewis - 2016
//
// Implementation of engine-to-script binding mechanisms
//

#include "Pch.h"

#include "Bindings.h"

#include "User.h"
#include "WorldState.h"



namespace Game {

//
// Construct and initialize a binding factory
//
// Sets up the binding tables for mapping script token identifiers to
// internal native functions for binding properties and goal states.
//
Binder::Binder (TokenPool * pool, WorldState * worldState)
	: m_tokens(pool),
	  m_worldState(worldState)
{
	m_userBindTable.BindTokenToFunction(pool->AddToken("EnterConnectedRoom"), &User::EnterConnectedRoom);
	m_userBindTable.BindTokenToFunction(pool->AddToken("EnterRoom"), &User::EnterRoom);
	m_userBindTable.BindTokenToFunction(pool->AddToken("SendMessage"), &User::SendMessage);
	m_userBindTable.BindTokenToFunction(pool->AddToken("SendRoomDescription"), &User::SendRoomDescription);
	m_userBindTable.BindTokenToFunction(pool->AddToken("PollInput"), &User::PollInput);

	m_userBindTable.BindTokenToProperty(pool->AddToken("CurrentRoom"), &User::GetCurrentRoomNameToken);
}


//
// Actual factory method for creating binding records
//
// Handles the logic for creating a backing engine-side object as well as
// linking up the binding record to the appropriate binding table obejct.
//
IEngineBinding * Binder::CreateBinding (Scriptable * scriptable, ScriptWorld * world, unsigned token) {
	if (!m_tokens)
		return nullptr;

	if (m_tokens->GetStringFromToken(token) == "User") {
		User * user = new User(world, scriptable, m_worldState);
		return new Binding<User>(user, &m_userBindTable);
	}

	return nullptr;
}

}
