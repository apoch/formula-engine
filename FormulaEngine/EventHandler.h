#pragma once


class ScriptWorld;


class EventHandlerSet {
public:			// Configuration interface
	void AddHandler(unsigned eventToken, ActionSet && actions);

public:			// Dispatch interface
	void TriggerHandlers(ScriptWorld * world, unsigned eventToken, Scriptable * target);

private:		// Internal state
	std::multimap<unsigned, ActionSet> m_eventHandlers;
};


