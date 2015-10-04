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

public:
	void BindTokenToFunction(unsigned token, GoalStateFunctionDouble func) {
		m_doubleMap[token] = func;
	}

	void BindTokenToFunction(unsigned token, GoalStateFunctionVector func) {
		m_vectorMap[token] = func;
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

private:		// Internal state
	std::map<unsigned, GoalStateFunctionDouble> m_doubleMap;
	std::map<unsigned, GoalStateFunctionVector> m_vectorMap;
};


template <typename BoundT>
class Binding : public IEngineBinding {
public:
	Binding(BoundT * toBind, BindingTable<BoundT> * bindingTable)
		: m_bound(toBind),
		  m_table(bindingTable)
	{ }

public:
	void SetGoalState(unsigned token, double state) override {
		m_table->Dispatch(token, m_bound, state);
	}

	void SetGoalState(unsigned token, double statex, double statey) override {
		m_table->Dispatch(token, m_bound, statex, statey);
	}

private:
	BoundT * m_bound;
	BindingTable<BoundT> * m_table;
};


class Binder : public IEngineBinder {
public:			// Construction
	explicit Binder(TokenPool * pool, Map * map);

public:
	IEngineBinding * CreateBinding(unsigned token) override;

private:		// Internal state
	Map * m_map;
	TokenPool * m_tokens;

	BindingTable<Unit> m_unitBindTable;
};




}

