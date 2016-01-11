// FormulaMUD.cpp : Defines the entry point for the console application.
//

#include "Pch.h"

#include "FormulaEngine/Formula.h"
#include "FormulaEngine/Actions.h"
#include "FormulaEngine/Parser.h"
#include "FormulaEngine/PropertyBag.h"
#include "FormulaEngine/TokenPool.h"
#include "FormulaEngine/EventHandler.h"
#include "FormulaEngine/Scriptable.h"
#include "FormulaEngine/ScriptWorld.h"
#include "FormulaEngine/DeserializerFactory.h"
#include "FormulaEngine/EngineBind.h"



class User {
public:
	ScriptWorld * world;

public:
	void SendMessage(unsigned message) {
		std::cout << world->GetMagicBag(3)->GetLine(message) << std::endl;
	}
};



namespace Game {


	template <typename BoundT>
	class BindingTable {
	public:
		typedef void (BoundT::*GoalStateFunctionDouble)(double);
		typedef void (BoundT::*GoalStateFunctionVector)(double, double);
		typedef void (BoundT::*GoalStateFunctionToken)(unsigned);

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

		void BindTokenToProperty(unsigned token, PropertyFunctionVector func) {
			m_propertyVectorMap[token] = func;
		}

		void Dispatch(unsigned token, BoundT * boundObject, unsigned tokenValue) {
			if (m_tokenMap.find(token) == m_tokenMap.end())
				return;

			GoalStateFunctionToken func = m_tokenMap[token];
			((boundObject)->*func)(tokenValue);
		}

		void Dispatch(unsigned token, BoundT * boundObject, double value) {
			if (m_doubleMap.find(token) == m_doubleMap.end())
				return;

			GoalStateFunctionDouble func = m_doubleMap[token];
			((boundObject)->*func)(value);
		}

		void Dispatch(unsigned token, BoundT * boundObject, double valuex, double valuey) {
			if (m_vectorMap.find(token) == m_vectorMap.end())
				return;

			GoalStateFunctionVector func = m_vectorMap[token];
			((boundObject)->*func)(valuex, valuey);
		}


		bool HasProperty(unsigned token) const {
			return m_propertyVectorMap.find(token) != m_propertyVectorMap.end();
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

		unsigned GetPropertyBinding(unsigned token, double * out1, double * out2) const override {
			return m_table->DispatchProperty(token, m_bound, out1, out2);
		}

	private:
		BoundT * m_bound;
		BindingTable<BoundT> * m_table;
	};


	class Binder : public IEngineBinder {
	public:			// Construction
		explicit Binder(TokenPool * pool);

	public:
		IEngineBinding * CreateBinding(Scriptable * scriptable, ScriptWorld * world, unsigned token) override;

	private:		// Internal state
		TokenPool * m_tokens;

		BindingTable<User> m_userBindTable;
	};



	Binder::Binder(TokenPool * pool)
		: m_tokens(pool)
	{
		m_userBindTable.BindTokenToFunction(pool->AddToken("SendMessage"), &User::SendMessage);
	}



	IEngineBinding * Binder::CreateBinding(Scriptable * scriptable, ScriptWorld * world, unsigned token) {
		if (!m_tokens)
			return nullptr;

		if (m_tokens->GetStringFromToken(token) == "User") {
			User * user = new User();
			user->world = world;
			return new Binding<User>(user, &m_userBindTable);
		}

		return nullptr;
	}


}





int main() {

	TokenPool tokens;

	Game::Binder binder(&tokens);

	ScriptWorld world(&tokens, &binder);

	DeserializerFactory factory;

	factory.LoadFileIntoScriptWorld("Data\\FormulaMUD.json", &world);

	world.QueueBroadcastEvent("OnUserConnect");

	while (world.DispatchEvents());

	//world.DumpOverview();

    return 0;
}

