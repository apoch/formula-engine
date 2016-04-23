#pragma once

struct IEngineBinder;


class ScriptWorld {
public:			// Construction and destruction
	ScriptWorld (TokenPool * pool, IEngineBinder * binder);
	~ScriptWorld ();

public:			// Setup interface
	void AddScriptable(const std::string & name, Scriptable && scriptable);
	void AddArchetype(const std::string & name, Scriptable && archetype);
	void AddMagicBag(unsigned nametoken);

	Scriptable * GetArchetype(unsigned token);
	Scriptable * GetScriptable(unsigned token);
	TextPropertyBag * GetMagicBag(unsigned token);

	TokenPool & GetTokenPool()			{ return *m_tokens; }

	Scriptable * InstantiateArchetype(unsigned token, IFormulaPropertyBag * paramBag);
	Scriptable * InstantiateArchetype(unsigned nameOfInstance, unsigned token, IFormulaPropertyBag * paramBag);

public:			// Event pump interface
	void QueueEvent(unsigned targetToken, const std::string & eventName);
	void QueueEvent(Scriptable * scriptable, unsigned eventToken, IFormulaPropertyBag * paramBag);

	void QueueBroadcastEvent(const std::string & eventName);

	void QueueDelayedEvent (Scriptable * target, unsigned eventToken, IFormulaPropertyBag * paramBag, ValueT delaySeconds);
	void QueueDelayedEvent (unsigned targetToken, unsigned eventToken, IFormulaPropertyBag * paramBag, ValueT delaySeconds);

	bool DispatchEvents();

	unsigned PeekTimeUntilNextEvent () const;

	unsigned GetMagicTokenForEvent () const {
		return m_magicTokenEvent;
	}


public:			// Debugging interface
	void DumpOverview() const;

private:		// Internal helpers
	void DispatchEvent(Scriptable * target, unsigned eventToken, const IFormulaPropertyBag * paramBag);
	void TransferTimedEvents ();

private:		// Internal structures
	struct Event {
		unsigned nameToken;
		Scriptable * directTarget;

		unsigned targetToken;

		IFormulaPropertyBag * parameterBag = nullptr;
		std::chrono::time_point<std::chrono::system_clock> timestamp;
	};

private:		// Internal state
	TokenPool * m_tokens;
	std::map<unsigned, Scriptable> m_scriptables;
	std::map<unsigned, Scriptable> m_archetypes;
	std::vector<std::pair<unsigned, TextPropertyBag>> m_magicBags;

	std::vector<Event> m_eventQueue;
	std::vector<Event> m_eventQueueTimed;
	std::vector<Scriptable *> m_instances;

	IEngineBinder * m_binder;

	unsigned m_magicTokenEvent = 0;
};


