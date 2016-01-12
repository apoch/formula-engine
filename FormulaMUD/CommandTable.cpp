#include "Pch.h"


#include "CommandTable.h"



namespace Game {


CommandTable::CommandTable(const char * jsonFileName, TokenPool * tokens) {
	picojson::value outvalue;

	{
		std::ifstream stream(jsonFileName, std::ios::in);
		picojson::parse(outvalue, stream);
	}

	if(!outvalue.is<picojson::object>())
		return;

	const auto & obj = outvalue.get<picojson::object>();

	auto cmditer = obj.find("commands");
	if (cmditer == obj.end())
		return;

	const auto & cmds = cmditer->second.get<picojson::array>();
	for (const auto & cmd : cmds) {
		if (!cmd.is<picojson::object>())
			continue;

		const auto & command = cmd.get<picojson::object>();
		CommandData data;

		auto textiter = command.find("command");
		if (textiter == command.end())
			continue;

		auto eventiter = command.find("event");
		if (eventiter == command.end())
			continue;

		std::string helpText = "No help is available for this command.";
		auto helpiter = command.find("helpText");
		if (helpiter != command.end())
			helpText = helpiter->second.get<std::string>();

		data.eventId = tokens->AddToken(eventiter->second.get<std::string>());
		data.numParams = 0;
		data.helpText = helpText;

		m_map[textiter->second.get<std::string>()] = data;
	}
}

bool CommandTable::DispatchCommandToWorld(const std::string & command, ScriptWorld * world, Scriptable * user) {
	auto iter = m_map.find(command);
	if (iter == m_map.end())
		return false;

	// TODO - params

	world->QueueEvent(user, iter->second.eventId, nullptr);

	return true;
}

void CommandTable::DisplayHelp (const std::string & command) {
	auto iter = m_map.find(command);
	if (iter == m_map.end()) {
		if (command.empty()) {
			std::cout << "Available commands:\n";

			for (auto & pair : m_map) {
				std::cout << pair.first << "\n";
			}

			std::cout << "\nType 'help command' to get help with a specific command.\n";
			std::cout << "Type 'quit' or 'exit' at any time to leave." << std::endl;
		}
		else {
			std::cout << "Unknown command '" << command << "'. Type 'help' for a list of commands." << std::endl;
		}

		return;
	}

	std::cout << "Help for '" << iter->first << "':\n" << iter->second.helpText << std::endl;
}



}