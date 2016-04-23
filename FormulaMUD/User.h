#pragma once


class ScriptWorld;
class Scriptable;
class TextPropertyBag;


namespace Game {


struct WorldState;
class Room;


class User {
public:			// Construction
	User (ScriptWorld * world, Scriptable * boundScriptable, WorldState * worldState);

public:			// IO interface
	void EnterRoom (unsigned roomIdToken);
	void EnterConnectedRoom (unsigned directionIdToken);

	void SendMessage (unsigned message);
	void SendRoomDescription (ValueT ignored);

	void PollInput (ValueT ignored);

public:			// Properties
	void GetCurrentRoomNameToken (unsigned * outToken) const;

private:		// Internal helpers
	void UpdateRoom ();

private:		// Internal state
	ScriptWorld * m_world;
	Scriptable * m_scriptable;
	WorldState * m_worldState;
	TextPropertyBag * m_textBag;

	Room * m_room;
};


}

