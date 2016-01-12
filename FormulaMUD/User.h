#pragma once


class ScriptWorld;
class Scriptable;
class TextPropertyBag;


namespace Game {


struct WorldState;


class User {
public:			// Construction
	User (ScriptWorld * world, Scriptable * boundScriptable, WorldState * worldState);

public:			// IO interface
	void SendMessage(unsigned message);
	void PollInput(double ignored);

private:		// Internal state
	ScriptWorld * m_world;
	Scriptable * m_scriptable;
	WorldState * m_worldState;
	TextPropertyBag * m_textBag;
};


}

