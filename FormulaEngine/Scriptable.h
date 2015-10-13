#pragma once


struct IActionPerformer;
struct IEngineBinder;
struct IEngineBinding;


class Scriptable {
public:			// Construction and destruction
	Scriptable() { }
	Scriptable(Scriptable && other);
	~Scriptable();

private:		// Non-copyable
	Scriptable(const Scriptable & other) = delete;
	Scriptable & operator = (const Scriptable & other) = delete;

public:			// Component accessors
	const ScopedPropertyBag & GetScopes() const		{ return m_scopes; }
	ScopedPropertyBag & GetScopes()					{ return m_scopes; }

	EventHandlerSet * GetEvents()					{ if(!m_eventHandlers) { m_eventHandlers = new EventHandlerSet; } return m_eventHandlers; }

public:			// Archetype support
	void AddBinding(unsigned bindingToken);
	IEngineBinding * GetBinding(unsigned bindingToken);
	const IEngineBinding * GetBinding(unsigned bindingToken) const;
	Result ResolveBinding(const IFormulaContext & context, unsigned scope, unsigned token) const;

	void BindAll(IEngineBinder * binder, ScriptWorld * world);

	Scriptable * Instantiate() const;

public:			// Membership notification interface
	void OnListMembershipAdded(unsigned listToken, IActionPerformer * owner) const;
	void OnListMembershipRemoved(unsigned listToken, IActionPerformer * owner) const;

private:		// Internal helper structures
	struct Membership {
		IActionPerformer * owner;
		unsigned token;
	};

private:		// Internal state
	ScopedPropertyBag m_scopes;
	EventHandlerSet * m_eventHandlers = nullptr;

	std::map<unsigned, IEngineBinding *> m_bindings;

	mutable std::vector<Membership> m_listMemberships;
};


