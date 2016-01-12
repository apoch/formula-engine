#pragma once


namespace Game {


class CommandTable;


struct WorldState {
	bool alive = true;
	CommandTable * commands = nullptr;
};


}

