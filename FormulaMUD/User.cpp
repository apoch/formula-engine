#include "Pch.h"

#include "User.h"
#include "WorldState.h"
#include "CommandTable.h"
#include "Room.h"
#include "Console.h"


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

	std::cout << m_room->GetDescription() << "\n" << std::endl;
}


void User::SendMessage (unsigned tokenId) {
	const char * line = m_textBag->GetLine(tokenId);
	if (!line)
		return;

	if (std::strchr(line, '%') == nullptr) {
		std::cout << line << std::endl;
	}
	else {
		std::string formatter(line);
		size_t phindex = formatter.find('%', 0);
		size_t outindex = 0;
		
		while (phindex != std::string::npos) {
			if (phindex > 0)
				std::cout << formatter.substr(outindex, phindex - outindex);

			outindex = phindex;

			size_t phendindex = phindex + 1;
			while (phendindex < formatter.length() && std::isalnum(formatter[phendindex]))
				++phendindex;

			unsigned placeholderToken = m_world->GetTokenPool().AddToken(formatter.substr(phindex + 1, phendindex - phindex - 1));
			Result res = m_scriptable->GetScopes().GetProperties().ResolveNumber(m_scriptable->GetScopes(), 0, placeholderToken);
			if (res.code != RESULT_CODE_OK)
				res.value = 0.0;

			std::cout << res.value;

			outindex = phendindex;

			phindex = formatter.find('%', phindex + 1);
		}

		if (outindex < formatter.length())
			std::cout << formatter.substr(outindex);
		
		std::cout << std::endl;
	}
}

	
void User::PollInput (double) {
	
	std::string buffer;
	if (!Console::ReadLine(&buffer))
		return;

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

