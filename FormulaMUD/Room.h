#pragma once


class ScriptWorld;
class Scriptable;


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

	void SetDescription (const std::string & description);

	const std::string & GetDescription () const {
		return m_description;
	}

	unsigned GetNameToken () const {
		return m_roomToken;
	}

private:		// Internal state
	ScriptWorld * m_world = nullptr;
	Scriptable * m_scriptable = nullptr;
	WorldState * m_worldState = nullptr;

	std::map<unsigned, Room *> m_connections;
	std::string m_description;

	unsigned m_roomToken = 0;
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

