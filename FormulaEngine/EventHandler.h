#pragma once


class ScriptWorld;


class EventHandlerSet {
public:			// Reference counting
	void IncRef ();
	void DecRef ();

public:			// Configuration interface
	void AddHandler (unsigned eventToken, ActionSet && actions);

public:			// Dispatch interface
	void TriggerHandlers (ScriptWorld * world, unsigned eventToken, Scriptable * target, const IPropertyBag * paramBag) const;

private:		// Internal state
	std::multimap<unsigned, ActionSet> m_eventHandlers;
	std::atomic<unsigned> m_refCount = 1;
};


