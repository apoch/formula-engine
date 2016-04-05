#pragma once

namespace Game {


struct WorldState;
class User;


template <typename BoundT>
class BindingTable {
public:
	typedef void (BoundT::*GoalStateFunctionDouble)(double);
	typedef void (BoundT::*GoalStateFunctionVector)(double, double);
	typedef void (BoundT::*GoalStateFunctionToken)(unsigned);

	typedef void (BoundT::*PropertyFunctionToken)(unsigned *) const;
	typedef void (BoundT::*PropertyFunctionVector)(double *, double *) const;

public:
	void BindTokenToFunction(unsigned token, GoalStateFunctionDouble func) {
		m_doubleMap[token] = func;
	}

	void BindTokenToFunction(unsigned token, GoalStateFunctionVector func) {
		m_vectorMap[token] = func;
	}

	void BindTokenToFunction(unsigned token, GoalStateFunctionToken func) {
		m_tokenMap[token] = func;
	}

	void BindTokenToProperty(unsigned token, PropertyFunctionToken func) {
		m_propertyTokenMap[token] = func;
	}

	void BindTokenToProperty(unsigned token, PropertyFunctionVector func) {
		m_propertyVectorMap[token] = func;
	}

	void Dispatch(unsigned token, BoundT * boundObject, unsigned tokenValue) {
		assert(m_tokenMap.find(token) != m_tokenMap.end());

		GoalStateFunctionToken func = m_tokenMap[token];
		((boundObject)->*func)(tokenValue);
	}

	void Dispatch(unsigned token, BoundT * boundObject, double value) {
		assert(m_doubleMap.find(token) != m_doubleMap.end());

		GoalStateFunctionDouble func = m_doubleMap[token];
		((boundObject)->*func)(value);
	}

	void Dispatch(unsigned token, BoundT * boundObject, double valuex, double valuey) {
		assert(m_vectorMap.find(token) != m_vectorMap.end());

		GoalStateFunctionVector func = m_vectorMap[token];
		((boundObject)->*func)(valuex, valuey);
	}


	bool HasProperty(unsigned token) const {
		if (m_propertyVectorMap.find(token) != m_propertyVectorMap.end())
			return true;

		if (m_propertyTokenMap.find(token) != m_propertyTokenMap.end())
			return true;

		return false;
	}

	unsigned DispatchProperty (unsigned token, BoundT * boundObject, unsigned * out) const {
		auto iter = m_propertyTokenMap.find(token);
		if (iter == m_propertyTokenMap.end())
			return 0;

		PropertyFunctionToken func = iter->second;
		((boundObject)->*func)(out);
		return 1;
	}

	unsigned DispatchProperty(unsigned token, BoundT * boundObject, double * outX, double * outY) {
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


template <typename BoundT>
class Binding : public IEngineBinding {
public:
	Binding(BoundT * toBind, BindingTable<BoundT> * bindingTable)
		: m_bound(toBind),
		m_table(bindingTable)
	{ }

	~Binding () {
		delete m_bound;
	}

public:
	void SetGoalState(unsigned token, unsigned tokenValue) override {
		m_table->Dispatch(token, m_bound, tokenValue);
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

	unsigned GetPropertyBinding (unsigned token, unsigned * out) const override {
		return m_table->DispatchProperty(token, m_bound, out);
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
	Binder(TokenPool * pool, WorldState * worldstate);

public:
	IEngineBinding * CreateBinding(Scriptable * scriptable, ScriptWorld * world, unsigned token) override;

private:		// Internal state
	TokenPool * m_tokens;
	WorldState * m_worldState;

	BindingTable<User> m_userBindTable;
};


}

