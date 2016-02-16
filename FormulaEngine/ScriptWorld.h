#pragma once

struct IEngineBinder;


class ScriptWorld {
public:			// Construction and destruction
	ScriptWorld(TokenPool * pool, IEngineBinder * binder);
	~ScriptWorld();

public:			// Setup interface
	void AddScriptable(const std::string & name, Scriptable && scriptable);
	void AddArchetype(const std::string & name, Scriptable && archetype);
	void AddMagicBag(unsigned nametoken);

	Scriptable * GetArchetype(unsigned token);
	Scriptable * GetScriptable(unsigned token);
	TextPropertyBag * GetMagicBag(unsigned token);

	TokenPool & GetTokenPool()			{ return *m_tokens; }

	Scriptable * InstantiateArchetype(unsigned token, IPropertyBag * paramBag);
	Scriptable * InstantiateArchetype(unsigned nameOfInstance, unsigned token, IPropertyBag * paramBag);

public:			// Event pump interface
	void QueueEvent(unsigned targetToken, const std::string & eventName);
	void QueueEvent(Scriptable * scriptable, unsigned eventToken, IPropertyBag * paramBag);

	void QueueBroadcastEvent(const std::string & eventName);

	void QueueDelayedEvent (unsigned targetToken, unsigned eventToken, IPropertyBag * paramBag, double delaySeconds);

	bool DispatchEvents();

public:			// Debugging interface
	void DumpOverview() const;

private:		// Internal helpers
	void DispatchEvent(Scriptable * target, unsigned eventToken, const IPropertyBag * paramBag);
	void TransferTimedEvents ();

private:		// Internal structures
	struct Event {
		unsigned nameToken;
		Scriptable * directTarget;

		unsigned targetToken;

		IPropertyBag * parameterBag = nullptr;
		std::chrono::time_point<std::chrono::system_clock> timestamp;
	};

private:		// Internal state
	TokenPool * m_tokens;
	std::map<unsigned, Scriptable> m_scriptables;
	std::map<unsigned, Scriptable> m_archetypes;
	std::map<unsigned, TextPropertyBag> m_magicBags;

	std::vector<Event> m_eventQueue;
	std::vector<Event> m_eventQueueTimed;
	std::vector<Scriptable *> m_instances;

	IEngineBinder * m_binder;
};


