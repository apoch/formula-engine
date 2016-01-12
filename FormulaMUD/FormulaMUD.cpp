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


namespace Game {

	class CommandTable {
	public:			// Construction
		CommandTable (const char * jsonFileName, TokenPool * tokens);

	public:			// Command dispatching
		bool DispatchCommandToWorld (const std::string & command, ScriptWorld * world, Scriptable * user);

	public:			// Additional functionality
		void DisplayHelp (const std::string & command);

	public:			// Internal state
		struct CommandData {
			unsigned    eventId;
			std::string helpText;
			unsigned    numParams;
		};

		std::map<std::string, CommandData> m_map;
	};


	struct WorldState {
		bool alive = true;
		CommandTable * commands = nullptr;
	};



	class User {
	public:			// TODO - icky
		ScriptWorld * world;
		Scriptable * scriptable;
		WorldState * worldState;
		TextPropertyBag * textBag;

	public:
		void SendMessage(unsigned message) {
			std::cout << textBag->GetLine(message) << std::endl;
		}

		void PollInput(double ignored);
	};


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
		Binder(TokenPool * pool, WorldState * worldstate);

	public:
		IEngineBinding * CreateBinding(Scriptable * scriptable, ScriptWorld * world, unsigned token) override;

	private:		// Internal state
		TokenPool * m_tokens;
		WorldState * m_worldState;

		BindingTable<User> m_userBindTable;
	};



	Binder::Binder(TokenPool * pool, WorldState * worldState)
		: m_tokens(pool),
		  m_worldState(worldState)
	{
		m_userBindTable.BindTokenToFunction(pool->AddToken("SendMessage"), &User::SendMessage);
		m_userBindTable.BindTokenToFunction(pool->AddToken("PollInput"), &User::PollInput);
	}



	IEngineBinding * Binder::CreateBinding(Scriptable * scriptable, ScriptWorld * world, unsigned token) {
		if (!m_tokens)
			return nullptr;

		if (m_tokens->GetStringFromToken(token) == "User") {
			User * user = new User();
			user->world = world;
			user->scriptable = scriptable;
			user->worldState = m_worldState;
			user->textBag = world->GetMagicBag(world->GetTokenPool().AddToken("TEXT"));
			return new Binding<User>(user, &m_userBindTable);
		}

		return nullptr;
	}



	CommandTable::CommandTable(const char * jsonFileName, TokenPool * tokens) {
		picojson::value outvalue;

		{
			std::ifstream stream(jsonFileName, std::ios::in);
			picojson::parse(outvalue, stream);
		}

		if(!outvalue.is<picojson::object>())
			return;

		const auto & obj = outvalue.get<picojson::object>();

		auto cmditer = obj.find("commands");
		if (cmditer == obj.end())
			return;

		const auto & cmds = cmditer->second.get<picojson::array>();
		for (const auto & cmd : cmds) {
			if (!cmd.is<picojson::object>())
				continue;

			const auto & command = cmd.get<picojson::object>();
			CommandData data;

			auto textiter = command.find("command");
			if (textiter == command.end())
				continue;

			auto eventiter = command.find("event");
			if (eventiter == command.end())
				continue;

			std::string helpText = "No help is available for this command.";
			auto helpiter = command.find("helpText");
			if (helpiter != command.end())
				helpText = helpiter->second.get<std::string>();

			data.eventId = tokens->AddToken(eventiter->second.get<std::string>());
			data.numParams = 0;
			data.helpText = helpText;

			m_map[textiter->second.get<std::string>()] = data;
		}
	}

	bool CommandTable::DispatchCommandToWorld(const std::string & command, ScriptWorld * world, Scriptable * user) {
		auto iter = m_map.find(command);
		if (iter == m_map.end())
			return false;

		// TODO - params

		world->QueueEvent(user, iter->second.eventId, nullptr);

		return true;
	}

	void CommandTable::DisplayHelp (const std::string & command) {
		auto iter = m_map.find(command);
		if (iter == m_map.end()) {
			if (command.empty()) {
				std::cout << "Available commands:\n";

				for (auto & pair : m_map) {
					std::cout << pair.first << "\n";
				}

				std::cout << "\nType 'help command' to get help with a specific command.\n";
				std::cout << "Type 'quit' or 'exit' at any time to leave." << std::endl;
			}
			else {
				std::cout << "Unknown command '" << command << "'. Type 'help' for a list of commands." << std::endl;
			}

			return;
		}

		std::cout << "Help for '" << iter->first << "':\n" << iter->second.helpText << std::endl;
	}

	
	void User::PollInput (double) {
		std::string buffer;

		std::getline(std::cin, buffer);

		std::stringstream parser;
		parser << buffer;

		std::string command;
		parser >> command;

		if (command == "q" || command == "quit" || command == "exit") {
			worldState->alive = false;
			return;
		}

		if (command == "help") {
			std::string param;
			parser >> param;

			worldState->commands->DisplayHelp(param);

			return;
		}

		// TODO - parse params into property bag

		if (worldState->commands->DispatchCommandToWorld(command, world, scriptable))
			return;

		std::cout << "What?" << std::endl;
	}
}





int main() {
	TokenPool tokens;

	Game::CommandTable commands("Data\\CommandList.json", &tokens);
	Game::WorldState state;

	state.commands = &commands;

	Game::Binder binder(&tokens, &state);

	ScriptWorld world(&tokens, &binder);

	DeserializerFactory factory;

	factory.LoadFileIntoScriptWorld("Data\\FormulaMUD.json", &world);

	world.QueueBroadcastEvent("OnUserConnect");
	while (world.DispatchEvents());


	while (state.alive) {
		world.QueueBroadcastEvent("Poll");
		while (world.DispatchEvents());
	}
		

    return 0;
}

