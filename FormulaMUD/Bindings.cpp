#include "Pch.h"

#include "Bindings.h"

#include "User.h"
#include "WorldState.h"



namespace Game {

Binder::Binder(TokenPool * pool, WorldState * worldState)
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



IEngineBinding * Binder::CreateBinding(Scriptable * scriptable, ScriptWorld * world, unsigned token) {
	if (!m_tokens)
		return nullptr;

	if (m_tokens->GetStringFromToken(token) == "User") {
		User * user = new User(world, scriptable, m_worldState);
		return new Binding<User>(user, &m_userBindTable);
	}

	return nullptr;
}

}
