//
// FormulaEngine Project
// By Mike Lewis - 2016
//
// Declarations for engine-to-script binding mechanisms
//
// This code is designed to allow scripts to communicate with
// "engine-side" code via two primary mechanics: bindings are
// used to read engine-owned data, and process it from inside
// a script; while goal states are used to send requests from
// script back to the engine. The engine will attempt to make
// world changes such that the goal state is achieved. If the
// engine succeeds, it propagates an event to the script side
// so that scripts can respond appropriately. Conversely, any
// failure to reach a goal state generates an event, allowing
// script logic to gracefully recover and move on.
//
// Like many aspects of the FormulaEngine implementation, the
// binding layer here is minimalistic and driven primarily by
// interest in simplicity and pragmatism. Any "real" usage of
// the formula script model is likely to replace this binding
// system with something considerably more robust and easy to
// maintain. For example the binding tables probably ought to
// be populated using a reflection system or some macro-based
// markup, instead of a separate discrete layer of hard-coded
// initialization calls.
//

#pragma once

namespace Game {


// Forward declarations
struct WorldState;
class User;


//
// Simple wrapper for storing binding metadata
//
// This class links script tokens to runtime pointers to member
// functions on the "bound" type. Usage occurs in two phases. A
// configuration pass sets up a mapping from token to function,
// and then runtime requests for the binding/goal-state will be
// routed to that mapped function.
//
template <typename BoundT>
class BindingTable {
public:			// Handy type shortcuts
	typedef void (BoundT::*GoalStateFunctionDouble)(double);
	typedef void (BoundT::*GoalStateFunctionVector)(double, double);
	typedef void (BoundT::*GoalStateFunctionToken)(unsigned);

	typedef void (BoundT::*PropertyFunctionToken)(unsigned *) const;
	typedef void (BoundT::*PropertyFunctionVector)(double *, double *) const;

public:			// Configuration phase
	void BindTokenToFunction (unsigned token, GoalStateFunctionDouble func) {
		m_doubleMap[token] = func;
	}

	void BindTokenToFunction (unsigned token, GoalStateFunctionVector func) {
		m_vectorMap[token] = func;
	}

	void BindTokenToFunction (unsigned token, GoalStateFunctionToken func) {
		m_tokenMap[token] = func;
	}

	void BindTokenToProperty (unsigned token, PropertyFunctionToken func) {
		m_propertyTokenMap[token] = func;
	}

	void BindTokenToProperty (unsigned token, PropertyFunctionVector func) {
		m_propertyVectorMap[token] = func;
	}

public:			// Runtime phase
	void Dispatch (unsigned token, BoundT * boundObject, unsigned tokenValue) {
		assert(m_tokenMap.find(token) != m_tokenMap.end());

		GoalStateFunctionToken func = m_tokenMap[token];
		((boundObject)->*func)(tokenValue);
	}

	void Dispatch (unsigned token, BoundT * boundObject, double value) {
		assert(m_doubleMap.find(token) != m_doubleMap.end());

		GoalStateFunctionDouble func = m_doubleMap[token];
		((boundObject)->*func)(value);
	}

	void Dispatch (unsigned token, BoundT * boundObject, double valuex, double valuey) {
		assert(m_vectorMap.find(token) != m_vectorMap.end());

		GoalStateFunctionVector func = m_vectorMap[token];
		((boundObject)->*func)(valuex, valuey);
	}


	bool HasProperty (unsigned token) const {
		if (m_propertyVectorMap.find(token) != m_propertyVectorMap.end())
			return true;

		if (m_propertyTokenMap.find(token) != m_propertyTokenMap.end())
			return true;

		return false;
	}

	//
	// Retrieve a property's value into the out pointer
	//
	// Special overload for token-typed properties. Returns 0
	// if not found, 1 if found (for arity of 1).
	//
	unsigned DispatchProperty (unsigned token, BoundT * boundObject, unsigned * out) const {
		auto iter = m_propertyTokenMap.find(token);
		if (iter == m_propertyTokenMap.end())
			return 0;

		PropertyFunctionToken func = iter->second;
		((boundObject)->*func)(out);
		return 1;
	}

	//
	// Retrieve a vector-typed property's value
	//
	// Returns the arity of the vector if found, 0 otherwise.
	//
	unsigned DispatchProperty (unsigned token, BoundT * boundObject, double * outX, double * outY) {
		if (m_propertyVectorMap.find(token) == m_propertyVectorMap.end())
			return 0;

		PropertyFunctionVector func = m_propertyVectorMap[token];
		((boundObject)->*func)(outX, outY);
		return 2;
	}

private:		// Internal state
	std::map<unsigned, GoalStateFunctionDouble> m_doubleMap;
	std::map<unsigned, GoalStateFunctionVector> m_vectorMap;
	std::map<unsigned, GoalStateFunctionToken> m_tokenMap;

	std::map<unsigned, PropertyFunctionToken> m_propertyTokenMap;
	std::map<unsigned, PropertyFunctionVector> m_propertyVectorMap;
};


//
// Lightweight wrapper connecting a script object to an engine object
//
// Handles the job of mapping script-style API requests over to native,
// engine-style requests, via a BindingTable<> object. This allows many
// bound objects to share a table while also allowing the table to vary
// between bindings if that is desirable.
//
template <typename BoundT>
class Binding : public IEngineBinding {
public:			// Construction and destruction
	Binding (BoundT * toBind, BindingTable<BoundT> * bindingTable)
		: m_bound(toBind),
		  m_table(bindingTable)
	{ }

	~Binding () {
		delete m_bound;
	}

public:			// Goal state manipulation interface
	void SetGoalState (unsigned token, unsigned tokenValue) override {
		m_table->Dispatch(token, m_bound, tokenValue);
	}

	void SetGoalState (unsigned token, double state) override {
		m_table->Dispatch(token, m_bound, state);
	}

	void SetGoalState (unsigned token, double statex, double statey) override {
		m_table->Dispatch(token, m_bound, statex, statey);
	}

public:			// Property retrieval interface
	bool HasPropertyBinding (unsigned token) const override {
		return m_table->HasProperty(token);
	}

	unsigned GetPropertyBinding (unsigned token, unsigned * out) const override {
		return m_table->DispatchProperty(token, m_bound, out);
	}

	unsigned GetPropertyBinding (unsigned token, double * out1, double * out2) const override {
		return m_table->DispatchProperty(token, m_bound, out1, out2);
	}

private:		// Internal state
	BoundT * m_bound;
	BindingTable<BoundT> * m_table;
};


//
// Factory for generating binding objects
//
// Given a script object, creates an engine object to back it,
// and returns a binding record that connects the two.
//
// Note that this order is arbitrary. It is equally valid (and
// perhaps even more useful) to create a script object to back
// an existing engine-side object instead.
//
class Binder : public IEngineBinder {
public:			// Construction
	Binder (TokenPool * pool, WorldState * worldstate);

public:
	IEngineBinding * CreateBinding (Scriptable * scriptable, ScriptWorld * world, unsigned token) override;

private:		// Internal state
	TokenPool * m_tokens;
	WorldState * m_worldState;

	BindingTable<User> m_userBindTable;
};


}

