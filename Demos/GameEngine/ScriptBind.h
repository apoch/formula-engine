#pragma once


class Map;
class TokenPool;
class Unit;


namespace Game {


template <typename BoundT>
class BindingTable {
public:
	typedef void (BoundT::*GoalStateFunctionDouble)(double);
	typedef void (BoundT::*GoalStateFunctionVector)(double, double);

	typedef void (BoundT::*PropertyFunctionVector)(double *, double *) const;

public:
	void BindTokenToFunction(unsigned token, GoalStateFunctionDouble func) {
		m_doubleMap[token] = func;
	}

	void BindTokenToFunction(unsigned token, GoalStateFunctionVector func) {
		m_vectorMap[token] = func;
	}

	void BindTokenToProperty(unsigned token, PropertyFunctionVector func) {
		m_propertyVectorMap[token] = func;
	}

	void Dispatch(unsigned token, BoundT * boundObject, double value) {
		if(m_doubleMap.find(token) == m_doubleMap.end())
			return;

		GoalStateFunctionDouble func = m_doubleMap[token];
		((boundObject)->*func)(value);
	}

	void Dispatch(unsigned token, BoundT * boundObject, double valuex, double valuey) {
		if(m_vectorMap.find(token) == m_vectorMap.end())
			return;

		GoalStateFunctionVector func = m_vectorMap[token];
		((boundObject)->*func)(valuex, valuey);
	}


	bool HasProperty(unsigned token) const {
		return m_propertyVectorMap.find(token) != m_propertyVectorMap.end();
	}

	unsigned DispatchProperty(unsigned token, BoundT * boundObject, double * outX, double * outY) {
		if(m_propertyVectorMap.find(token) == m_propertyVectorMap.end())
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


template <typename BoundT>
class Binding : public IEngineBinding {
public:
	Binding(BoundT * toBind, BindingTable<BoundT> * bindingTable)
		: m_bound(toBind),
		  m_table(bindingTable)
	{ }

public:
	void SetGoalState(unsigned token, unsigned tokenValue) override {
		assert(false);		// Not implemented
	}


	void SetGoalState(unsigned token, double state) override {
		m_table->Dispatch(token, m_bound, state);
	}

	void SetGoalState(unsigned token, double statex, double statey) override {
		m_table->Dispatch(token, m_bound, statex, statey);
	}

	bool HasPropertyBinding(unsigned token) const override {
		return m_table->HasProperty(token);
	}

	unsigned GetPropertyBinding(unsigned token, double * out1, double * out2) const override {
		return m_table->DispatchProperty(token, m_bound, out1, out2);
	}

private:
	BoundT * m_bound;
	BindingTable<BoundT> * m_table;
};


class Binder : public IEngineBinder {
public:			// Construction
	explicit Binder(TokenPool * pool, Map * map);

public:
	IEngineBinding * CreateBinding(Scriptable * scriptable, ScriptWorld * world, unsigned token) override;

private:		// Internal state
	Map * m_map;
	TokenPool * m_tokens;

	BindingTable<Unit> m_unitBindTable;
};




}

