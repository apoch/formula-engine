#pragma once


namespace Game {


class CommandTable;
class RoomNetwork;


struct WorldState {
	bool alive = true;
	CommandTable * commands = nullptr;
	RoomNetwork * roomNetwork = nullptr;
};


}

