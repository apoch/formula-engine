#pragma once


class ScriptWorld;
class Scriptable;
class TextPropertyBag;


namespace Game {


struct WorldState;


class Room {
public:			// Construction
	Room () = default;
	Room (unsigned roomToken, ScriptWorld * world, WorldState * worldState);

public:			// Connectivity
	void AddConnection (unsigned directionToken, Room * otherRoom);
	Room * FindConnection (unsigned directionToken);

public:			// Miscellaneous access
	Scriptable * GetScriptable () const {
		return m_scriptable;
	}

private:		// Internal state
	ScriptWorld * m_world = nullptr;
	Scriptable * m_scriptable = nullptr;
	WorldState * m_worldState = nullptr;
	TextPropertyBag * m_textBag = nullptr;

	std::map<unsigned, Room *> m_connections;
};



class RoomNetwork {
public:
	RoomNetwork (const char * jsonFileName, TokenPool * tokens, ScriptWorld * world, WorldState * worldState);

public:
	Room * FindRoom (unsigned roomIdToken);

private:
	std::map<unsigned, Room> m_rooms;
};


}

