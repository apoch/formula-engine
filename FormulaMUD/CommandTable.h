#pragma once


class ScriptWorld;
class Scriptable;


namespace Game {


class CommandTable {
public:			// Construction
	CommandTable (const char * jsonFileName, TokenPool * tokens);

public:			// Command dispatching
	bool DispatchCommandToWorld (const std::string & command, std::stringstream & parser, ScriptWorld * world, Scriptable * user);

public:			// Additional functionality
	void DisplayHelp (const std::string & command);

public:			// Internal state
	struct CommandData {
		unsigned    eventId;
		std::string helpText;
		std::vector<std::string> params;
	};

	std::map<std::string, CommandData> m_map;
};


}


