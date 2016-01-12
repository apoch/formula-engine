#include "Pch.h"


#include "User.h"
#include "WorldState.h"
#include "CommandTable.h"


namespace Game {



User::User (ScriptWorld * world, Scriptable * boundScriptable, WorldState * worldState)
	: m_world(world),
	  m_scriptable(boundScriptable),
	  m_worldState(worldState)
{
	m_textBag = world->GetMagicBag(world->GetTokenPool().AddToken("TEXT"));
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

	if (m_worldState->commands->DispatchCommandToWorld(command, m_world, m_scriptable))
		return;

	std::cout << "What?" << std::endl;
}




}

