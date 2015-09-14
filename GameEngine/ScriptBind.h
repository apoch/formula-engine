#pragma once


class TokenPool;
class Unit;


namespace Game {


template <typename BoundT>
class BindingTable {
public:
	typedef void (BoundT::*GoalStateFunctionDouble)(double);

public:
	void BindTokenToFunction(unsigned token, GoalStateFunctionDouble func) {
		m_doubleMap[token] = func;
	}

	void Dispatch(unsigned token, BoundT * boundObject, double value) {
		GoalStateFunctionDouble func = m_doubleMap[token];
		((boundObject)->*func)(value);
	}

private:		// Internal state
	std::map<unsigned, GoalStateFunctionDouble> m_doubleMap;
};


template <typename BoundT>
class Binding : public IEngineBinding {
public:
	Binding(BoundT && toEmplace, BindingTable<BoundT> * bindingTable)
		: m_bound(std::move(toEmplace)),
		  m_table(bindingTable)
	{ }

public:
	void SetGoalState(unsigned token, double state) override {
		m_table->Dispatch(token, &m_bound, state);
	}

private:
	BoundT m_bound;
	BindingTable<BoundT> * m_table;
};


class Binder : public IEngineBinder {
public:			// Construction
	explicit Binder(TokenPool * pool);

public:
	IEngineBinding * CreateBinding(unsigned token) override;

private:		// Internal state
	TokenPool * m_tokens;

	BindingTable<Unit> m_unitBindTable;
};




}

