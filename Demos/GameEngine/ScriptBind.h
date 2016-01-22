//
// FormulaEngine Project
// By Mike Lewis - 2015
//
// Script-to-engine bindings declarations
//
// This header declares the binding mechanisms used to
// link code and data in the game engine back to a set
// of properties and goal states in the FormulaEngine.
//

#pragma once


// Forward declarations
class Map;
class TokenPool;
class Unit;


namespace Game {


//
// Binding management for specific game engine types
//
// One binding table should exist per bound type in the game engine.
// The table's entries link goal states and properties from the game
// side back to the FormulaEngine side, and the Dispatch methods let
// script code talk to the bindings.
//
template <typename BoundT>
class BindingTable {
public:			// Type shortcuts
	typedef void (BoundT::*GoalStateFunctionDouble)(double);
	typedef void (BoundT::*GoalStateFunctionVector)(double, double);

	typedef void (BoundT::*PropertyFunctionVector)(double *, double *) const;

public:			// Binding interface
	void BindTokenToFunction (unsigned token, GoalStateFunctionDouble func) {
		m_doubleMap[token] = func;
	}

	void BindTokenToFunction (unsigned token, GoalStateFunctionVector func) {
		m_vectorMap[token] = func;
	}

	void BindTokenToProperty (unsigned token, PropertyFunctionVector func) {
		m_propertyVectorMap[token] = func;
	}

	void Dispatch (unsigned token, BoundT * boundObject, double value) {
		if (m_doubleMap.find(token) == m_doubleMap.end())
			return;

		GoalStateFunctionDouble func = m_doubleMap[token];
		((boundObject)->*func)(value);
	}

	void Dispatch (unsigned token, BoundT * boundObject, double valuex, double valuey) {
		if (m_vectorMap.find(token) == m_vectorMap.end())
			return;

		GoalStateFunctionVector func = m_vectorMap[token];
		((boundObject)->*func)(valuex, valuey);
	}


	bool HasProperty (unsigned token) const {
		return m_propertyVectorMap.find(token) != m_propertyVectorMap.end();
	}

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

	std::map<unsigned, PropertyFunctionVector> m_propertyVectorMap;
};


//
// Binding to a single game engine object
//
// One instance of this should exist per instance of a bindable
// type in the engine. It knows how to route binding requests by
// consulting a BindingTable.
//
template <typename BoundT>
class Binding : public IEngineBinding {
public:			// Construction
	Binding (BoundT * toBind, BindingTable<BoundT> * bindingTable)
		: m_bound(toBind),
		  m_table(bindingTable)
	{ }

public:			// Goal state and property interface
	void SetGoalState (unsigned token, unsigned tokenValue) override {
		ref(token);
		ref(tokenValue);
		assert(false);		// Not implemented
	}

	void SetGoalState (unsigned token, double state) override {
		m_table->Dispatch(token, m_bound, state);
	}

	void SetGoalState (unsigned token, double statex, double statey) override {
		m_table->Dispatch(token, m_bound, statex, statey);
	}

	bool HasPropertyBinding (unsigned token) const override {
		return m_table->HasProperty(token);
	}

	unsigned GetPropertyBinding (unsigned token, unsigned * out) const override {
		ref(token);
		ref(out);
		return 0;			// Not implemented
	}

	unsigned GetPropertyBinding (unsigned token, double * out1, double * out2) const override {
		return m_table->DispatchProperty(token, m_bound, out1, out2);
	}

private:		// Internal state
	BoundT * m_bound;
	BindingTable<BoundT> * m_table;
};


//
// Factory for binding objects
//
// Ask this class for a binding between game and script objects
//
class Binder : public IEngineBinder {
public:			// Construction
	explicit Binder(TokenPool * pool, Map * map);

public:			// Binding interface
	IEngineBinding * CreateBinding(Scriptable * scriptable, ScriptWorld * world, unsigned token) override;

private:		// Internal state
	Map * m_map;
	TokenPool * m_tokens;

	BindingTable<Unit> m_unitBindTable;
};




}

