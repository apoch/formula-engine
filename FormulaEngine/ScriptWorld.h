#pragma once


class ScriptWorld {
public:			// Setup interface
	void AddScriptable(const std::string & name, Scriptable && scriptable);
	void AddArchetype(const std::string & name, Scriptable && archetype);

	Scriptable * GetArchetype(unsigned token);
	Scriptable * GetScriptable(unsigned token);

	TokenPool & GetTokenPool()			{ return m_tokens; }

public:			// Event pump interface
	void QueueEvent(unsigned targetToken, const std::string & eventName);
	void QueueBroadcastEvent(const std::string & eventName);

	void DispatchEvents();

private:		// Internal helpers
	void DispatchEvent(Scriptable * target, unsigned eventToken);

private:		// Internal structures
	struct Event {
		unsigned nameToken;
		unsigned targetToken;
	};

private:		// Internal state
	TokenPool m_tokens;
	std::map<unsigned, Scriptable> m_scriptables;
	std::map<unsigned, Scriptable> m_archetypes;

	std::vector<Event> m_eventQueue;
};


