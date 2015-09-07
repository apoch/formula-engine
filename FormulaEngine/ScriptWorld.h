#pragma once


class ScriptWorld {
public:			// Destruction
	~ScriptWorld();

public:			// Setup interface
	void AddScriptable(const std::string & name, Scriptable && scriptable);
	void AddArchetype(const std::string & name, Scriptable && archetype);

	Scriptable * GetArchetype(unsigned token);
	Scriptable * GetScriptable(unsigned token);

	TokenPool & GetTokenPool()			{ return m_tokens; }

	Scriptable * InstantiateArchetype(unsigned token);

public:			// Event pump interface
	void QueueEvent(unsigned targetToken, const std::string & eventName);
	void QueueEvent(Scriptable * scriptable, unsigned eventToken);

	void QueueBroadcastEvent(const std::string & eventName);

	bool DispatchEvents();

public:			// Debugging interface
	void DumpOverview() const;

private:		// Internal helpers
	void DispatchEvent(Scriptable * target, unsigned eventToken);

private:		// Internal structures
	struct Event {
		unsigned nameToken;
		Scriptable * directTarget;

		unsigned targetToken;
	};

private:		// Internal state
	TokenPool m_tokens;
	std::map<unsigned, Scriptable> m_scriptables;
	std::map<unsigned, Scriptable> m_archetypes;

	std::vector<Event> m_eventQueue;
	std::vector<Scriptable *> m_instances;
};


