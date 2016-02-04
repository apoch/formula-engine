#include "Pch.h"


#include "User.h"
#include "WorldState.h"
#include "CommandTable.h"
#include "Room.h"


namespace Game {



User::User (ScriptWorld * world, Scriptable * boundScriptable, WorldState * worldState)
	: m_world(world),
	  m_scriptable(boundScriptable),
	  m_worldState(worldState),
	  m_room(nullptr)
{
	// TODO - improve this
	m_textBag = world->GetMagicBag(world->GetTokenPool().AddToken("TEXT"));
}


void User::GetCurrentRoomNameToken (unsigned * outToken) const {
	if (m_room)
		*outToken = m_room->GetNameToken();
	else
		*outToken = 0;
}


void User::EnterConnectedRoom (unsigned directionIdToken) {
	if (!m_room)
		return;

	Room * target = m_room->FindConnection(directionIdToken);
	if (!target) {
		m_world->QueueEvent(m_scriptable, m_world->GetTokenPool().AddToken("EnterConnectedRoomFailed"), nullptr);
		return;
	}

	m_room = target;
	UpdateRoom();
}


void User::EnterRoom (unsigned roomIdToken) {
	m_room = m_worldState->roomNetwork->FindRoom(roomIdToken);
	UpdateRoom();
}

void User::SendRoomDescription (double) {
	assert(m_room != nullptr);

	std::cout << m_room->GetDescription() << std::endl;
}


void User::SendMessage (unsigned tokenId) {
	std::cout << m_textBag->GetLine(tokenId) << std::endl;
}

	
void User::PollInput (double) {
	std::string buffer;

	std::getline(std::cin, buffer);

	std::stringstream parser;
	parser << buffer;

	std::string command;
	parser >> command;

	if (command == "q" || command == "quit" || command == "exit") {
		m_worldState->alive = false;
		return;
	}

	if (command == "help") {
		std::string param;
		parser >> param;

		m_worldState->commands->DisplayHelp(param);

		return;
	}

	if (m_worldState->commands->DispatchCommandToWorld(command, parser, m_world, m_scriptable))
		return;

	std::cout << "What?" << std::endl;
}


void User::UpdateRoom () {
	auto * scopes = new ScopedPropertyBag();
	scopes->SetNamedBinding(m_world->GetTokenPool().AddToken("User"), m_scriptable);

	m_world->QueueEvent(m_room->GetScriptable(), m_world->GetTokenPool().AddToken("OnUserEnter"), scopes);
}



}

