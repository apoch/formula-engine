#include "Pch.h"

#include "Interfaces.h"
#include "DeserializerFactory.h"
#include "Formula.h"
#include "Actions.h"
#include "TokenPool.h"
#include "PropertyBag.h"
#include "EventHandler.h"
#include "Scriptable.h"
#include "ScriptWorld.h"
#include "Parser.h"



typedef void (ScriptWorld::*RegistrationFunc)(const std::string &, Scriptable &&);
typedef Scriptable * (ScriptWorld::*LookupFunc)(unsigned);


static void LoadArrayOfBindings(const picojson::value & bindarray, ScriptWorld * world, Scriptable * scriptable) {
	auto & bindings = bindarray.get<picojson::array>();
	for(auto & binding : bindings) {
		if(!binding.is<std::string>())
			continue;

		const std::string & bindingstr = binding.get<std::string>();
		unsigned bindingtoken = world->GetTokenPool().AddToken(bindingstr);

		scriptable->AddBinding(bindingtoken);
	}
}

static void LoadArrayOfText(const picojson::value & textarray, ScriptWorld * world, TextPropertyBag * textBag) {
	auto & texts = textarray.get<picojson::object>();
	for(auto & text : texts) {
		if(!text.second.is<std::string>())
			continue;

		auto & payload = text.second.get<std::string>();
		textBag->AddLine(world->GetTokenPool().AddToken(text.first), payload.c_str());
	}
}

static void LoadArrayOfActions(const char name[], const picojson::object & obj, ActionSet * actions, ScriptWorld * world, FormulaParser * parser) {
	auto actioniter = obj.find(name);
	if(actioniter == obj.end() || !actioniter->second.is<picojson::array>())
		return;

	for(auto & actionentry : actioniter->second.get<picojson::array>()) {
		if(!actionentry.is<picojson::object>())
			continue;

		auto & action = actionentry.get<picojson::object>();
		auto actionkeyiter = action.find("action");
		if(actionkeyiter == action.end() || !actionkeyiter->second.is<std::string>())
			continue;

		const std::string & actionkey = actionkeyiter->second.get<std::string>();
		if (actionkey == "AddToList") {
			auto targetiter = action.find("target");
			if (targetiter == action.end() || !targetiter->second.is<std::string>())
				continue;

			auto listiter = action.find("list");
			if (listiter == action.end() || !listiter->second.is<std::string>())
				continue;

			Formula objtoken;
			auto objiter = action.find("object");
			if (objiter != action.end() && objiter->second.is<std::string>())
				objtoken = parser->Parse(objiter->second.get<std::string>(), &world->GetTokenPool());

			unsigned targetToken = world->GetTokenPool().AddToken(targetiter->second.get<std::string>());
			unsigned listToken = world->GetTokenPool().AddToken(listiter->second.get<std::string>());

			actions->AddAction(new ActionListAddEntry(std::move(objtoken), listToken, targetToken));
		}
		else if(actionkey == "CreateListMember") {
			auto listiter = action.find("list");
			if(listiter == action.end() || !listiter->second.is<std::string>())
				continue;

			auto archetypeiter = action.find("archetype");
			if(archetypeiter == action.end() || !archetypeiter->second.is<std::string>())
				continue;

			FormulaPropertyBag * parambagptr = nullptr;
			auto paramsiter = action.find("params");
			if(paramsiter != action.end() && paramsiter->second.is<picojson::object>()) {
				parambagptr = new FormulaPropertyBag;

				auto params = paramsiter->second.get<picojson::object>();
				for(auto & param : params) {
					parambagptr->Set(world->GetTokenPool().AddToken(param.first), parser->Parse(param.second.get<std::string>(), &world->GetTokenPool()));
				}
			}

			unsigned listToken = world->GetTokenPool().AddToken(listiter->second.get<std::string>());
			unsigned archetypeToken = world->GetTokenPool().AddToken(archetypeiter->second.get<std::string>());

			actions->AddAction(new ActionListSpawnEntry(listToken, archetypeToken, parambagptr));
		}
		else if(actionkey == "if") {
			auto conditer = action.find("condition");
			if(conditer == action.end() || !conditer->second.is<std::string>())
				continue;

			Formula condition = parser->Parse(conditer->second.get<std::string>(), &world->GetTokenPool());

			ActionSet nestedActions, elseActions;
			LoadArrayOfActions("actions", action, &nestedActions, world, parser);
			LoadArrayOfActions("else", action, &elseActions, world, parser);

			actions->AddAction(new ActionConditionalBlock(std::move(condition), std::move(nestedActions), std::move(elseActions)));
		}
		else if(actionkey == "SetGoalState") {
			auto binditer = action.find("binding");
			if(binditer == action.end() || !binditer->second.is<std::string>())
				continue;

			auto propiter = action.find("property");
			if(propiter == action.end() || !propiter->second.is<std::string>())
				continue;

			auto valiter = action.find("value");
			if(valiter == action.end() || !valiter->second.is<std::string>())
				continue;

			unsigned scopeToken = world->GetTokenPool().AddToken(binditer->second.get<std::string>());
			unsigned targetToken = world->GetTokenPool().AddToken(propiter->second.get<std::string>());
			auto & payload = valiter->second.get<std::string>();

			actions->AddAction(new ActionSetGoalState(scopeToken, targetToken, parser->Parse(payload, &world->GetTokenPool())));
		}
		else if(actionkey == "SetProperty") {
			auto propiter = action.find("property");
			if(propiter == action.end() || !propiter->second.is<std::string>())
				continue;

			auto valiter = action.find("value");
			if(valiter == action.end() || !valiter->second.is<std::string>())
				continue;

			unsigned targetToken = world->GetTokenPool().AddToken(propiter->second.get<std::string>());
			auto & payload = valiter->second.get<std::string>();

			unsigned scopeToken = 0;

			auto scopeiter = action.find("target");
			if (scopeiter != action.end() && scopeiter->second.is<std::string>())
				scopeToken = world->GetTokenPool().AddToken(scopeiter->second.get<std::string>());

			actions->AddAction(new ActionSetProperty(targetToken, parser->Parse(payload, &world->GetTokenPool()), scopeToken));
		}
		else if(actionkey == "TriggerEvent") {
			auto eventiter = action.find("event");
			if(eventiter == action.end() || !eventiter->second.is<std::string>())
				continue;

			unsigned targetToken = 0;
			auto targetiter = action.find("target");
			if (targetiter != action.end() && targetiter->second.is<std::string>())
			{
				auto & target = targetiter->second.get<std::string>();
				targetToken = world->GetTokenPool().AddToken(target);
			}

			unsigned eventToken = world->GetTokenPool().AddToken(eventiter->second.get<std::string>());

			FormulaPropertyBag * parambagptr = nullptr;
			auto paramsiter = action.find("params");
			if(paramsiter != action.end() && paramsiter->second.is<picojson::object>()) {
				parambagptr = new FormulaPropertyBag;

				auto params = paramsiter->second.get<picojson::object>();
				for(auto & param : params) {
					parambagptr->Set(world->GetTokenPool().AddToken(param.first), parser->Parse(param.second.get<std::string>(), &world->GetTokenPool()));
				}
			}

			Formula delayFormula;
			auto delayiter = action.find("delay");
			if (delayiter != action.end() && delayiter->second.is<std::string>()) {
				auto delay = delayiter->second.get<std::string>();
				delayFormula = parser->Parse(delay, &world->GetTokenPool());
			}
			else {
				delayFormula.Push(0.0);
			}

			actions->AddAction(new ActionEventTrigger(eventToken, targetToken, parambagptr, std::move(delayFormula)));
		}
		else if(actionkey == "RepeatEvent") {
			auto eventiter = action.find("event");
			if(eventiter == action.end() || !eventiter->second.is<std::string>())
				continue;

			auto payloaditer = action.find("count");
			if(payloaditer == action.end() || !payloaditer->second.is<std::string>())
				continue;

			unsigned eventToken = world->GetTokenPool().AddToken(eventiter->second.get<std::string>());
			auto & payload = payloaditer->second.get<std::string>();

			FormulaPropertyBag * parambagptr = nullptr;
			auto paramsiter = action.find("params");
			if(paramsiter != action.end() && paramsiter->second.is<picojson::object>()) {
				parambagptr = new FormulaPropertyBag;

				auto params = paramsiter->second.get<picojson::object>();
				for(auto & param : params) {
					parambagptr->Set(world->GetTokenPool().AddToken(param.first), parser->Parse(param.second.get<std::string>(), &world->GetTokenPool()));
				}
			}

			actions->AddAction(new ActionEventRepeat(eventToken, parser->Parse(payload, &world->GetTokenPool()), parambagptr));
		}
		else if(actionkey == "foreach") {
			auto listiter = action.find("list");
			if(listiter == action.end() || !listiter->second.is<std::string>())
				continue;

			Formula scriptableToken;
			auto scriptableiter = action.find("scriptable");
			if(scriptableiter != action.end() && scriptableiter->second.is<std::string>())
				scriptableToken = parser->Parse(scriptableiter->second.get<std::string>(), &world->GetTokenPool());

			ActionSet loopactions;
			LoadArrayOfActions("actions", action, &loopactions, world, parser);

			unsigned listToken = world->GetTokenPool().AddToken(listiter->second.get<std::string>());
			actions->AddAction(new ActionListForEach(std::move(scriptableToken), listToken, std::move(loopactions)));
		}
		else if (actionkey == "ListTransfer") {
			auto listiter = action.find("list");
			if(listiter == action.end() || !listiter->second.is<std::string>())
				continue;

			auto targetlistiter = action.find("targetList");
			if(targetlistiter == action.end() || !targetlistiter->second.is<std::string>())
				continue;

			auto conditer = action.find("condition");
			if(conditer == action.end() || !conditer->second.is<std::string>())
				continue;

			Formula originToken;
			Formula targetToken;

			auto originiter = action.find("scriptable");
			if(originiter != action.end() && originiter->second.is<std::string>())
				originToken = parser->Parse(originiter->second.get<std::string>(), &world->GetTokenPool());

			auto targetIter = action.find("target");
			if(targetIter != action.end() && targetIter->second.is<std::string>())
				targetToken = parser->Parse(targetIter->second.get<std::string>(), &world->GetTokenPool());


			unsigned listToken = world->GetTokenPool().AddToken(listiter->second.get<std::string>());
			unsigned targetListToken = world->GetTokenPool().AddToken(targetlistiter->second.get<std::string>());

			Formula condition = parser->Parse(conditer->second.get<std::string>(), &world->GetTokenPool());

			actions->AddAction(new ActionListTransfer(std::move(condition), std::move(originToken), listToken, std::move(targetToken), targetListToken));
		}
		else if (actionkey == "ListRemove") {
			auto listiter = action.find("list");
			if (listiter == action.end() || !listiter->second.is<std::string>())
				continue;

			auto conditer = action.find("condition");
			if (conditer == action.end() || !conditer->second.is<std::string>())
				continue;

			Formula originToken;

			auto originiter = action.find("scriptable");
			if (originiter != action.end() && originiter->second.is<std::string>())
				originToken = parser->Parse(originiter->second.get<std::string>(), &world->GetTokenPool());

			unsigned listToken = world->GetTokenPool().AddToken(listiter->second.get<std::string>());

			Formula condition = parser->Parse(conditer->second.get<std::string>(), &world->GetTokenPool());

			actions->AddAction(new ActionListRemove(std::move(condition), std::move(originToken), listToken));
		}
		else {
			assert(false);
		}
	}
}


static void LoadArrayOfProperties(const picojson::value & proparray, ScriptWorld * world, FormulaParser * parser, Scriptable * scriptable) {
	auto & props = proparray.get<picojson::object>();
	for(auto & prop : props) {
		if(!prop.second.is<std::string>())
			continue;

		const std::string & formulastring = prop.second.get<std::string>();

		Formula formula = parser->Parse(formulastring, &world->GetTokenPool());
		scriptable->GetScopes().SetFormula(world->GetTokenPool().AddToken(prop.first), formula);
	}
}


void DeserializerFactory::LoadArrayOfLists (const picojson::array & listarray, ScriptWorld * world, Scriptable * instance) {
	for(auto & listentry : listarray) {
		auto & listobj = listentry.get<picojson::object>();

		auto listnameiter = listobj.find("name");
		if(listnameiter == listobj.end() || !listnameiter->second.is<std::string>())
			continue;

		auto contentsiter = listobj.find("contents");
		if(contentsiter == listobj.end() || !contentsiter->second.is<picojson::array>())
			continue;

		const std::string & listname = listnameiter->second.get<std::string>();
		unsigned token = world->GetTokenPool().AddToken(listname);

				
		auto & contents = contentsiter->second.get<picojson::array>();
		for(auto & contententry : contents) {
			if(!contententry.is<std::string>())
				continue;

			const std::string & content = contententry.get<std::string>();
			unsigned contenttoken = world->GetTokenPool().AddToken(content);
			Scriptable * otherInstance = world->GetScriptable(contenttoken);

			if(!otherInstance)
				continue;

			instance->GetScopes().ListAddEntry(token, otherInstance);
		}
	}
}


static void LoadArrayOfScriptables(const picojson::value & node, ScriptWorld * world, RegistrationFunc func, LookupFunc lookup, FormulaParser * parser) {
	if(!node.is<picojson::array>())
		return;

	auto & scriptables = node.get<picojson::array>();
	for(auto & scriptable : scriptables) {
		if(!scriptable.is<picojson::object>())
			continue;

		auto & obj = scriptable.get<picojson::object>();
		auto nameiter = obj.find("name");
		if(nameiter == obj.end() || !nameiter->second.is<std::string>())
			continue;

		const std::string & name = nameiter->second.get<std::string>();

		Scriptable instance;

		auto propsiter = obj.find("properties");
		if(propsiter != obj.end() && propsiter->second.is<picojson::object>())
			LoadArrayOfProperties(propsiter->second, world, parser, &instance);

		auto eventiter = obj.find("events");
		if(eventiter != obj.end() && eventiter->second.is<picojson::array>())
			DeserializerFactory::LoadArrayOfEvents(eventiter->second, world, parser, &instance);

		auto binditer = obj.find("bindings");
		if(binditer != obj.end() && binditer->second.is<picojson::array>())
			LoadArrayOfBindings(binditer->second, world, &instance);

		(world->*(func))(name, std::move(instance));
	}

	for(auto & scriptable : scriptables) {
		if(!scriptable.is<picojson::object>())
			continue;

		auto & obj = scriptable.get<picojson::object>();
		auto nameiter = obj.find("name");

		if(nameiter == obj.end() || !nameiter->second.is<std::string>())
			continue;

		const std::string & name = nameiter->second.get<std::string>();

		Scriptable * instance = (world->*(lookup))(world->GetTokenPool().AddToken(name));
		if(!instance)
			continue;

		auto listiter = obj.find("lists");
		if(listiter != obj.end() && listiter->second.is<picojson::array>()) {
			auto & listarray = listiter->second.get<picojson::array>();

			DeserializerFactory::LoadArrayOfLists(listarray, world, instance);
		}
	}
}



void DeserializerFactory::LoadFileIntoScriptWorld(const char filename[], ScriptWorld * world) {
	picojson::value outvalue;

	{
		std::ifstream stream(filename, std::ios::in);
		picojson::parse(outvalue, stream);
	}

	if(!outvalue.is<picojson::object>())
		return;

	FormulaParser parser;
	auto & parsedobject = outvalue.get<picojson::object>();
	for(auto & pair : parsedobject) {
		if(pair.first == "scriptables")
			LoadArrayOfScriptables(pair.second, world, &ScriptWorld::AddScriptable, &ScriptWorld::GetScriptable, &parser);
		else if(pair.first == "archetypes")
			LoadArrayOfScriptables(pair.second, world, &ScriptWorld::AddArchetype, &ScriptWorld::GetArchetype, &parser);
		else if(pair.first == "textbags") {
			auto & obj = pair.second.get<picojson::array>();

			for (auto & textiter : obj) {
				unsigned token = world->GetTokenPool().AddToken(textiter.get<picojson::object>().find("name")->second.get<std::string>());
				world->AddMagicBag(token);
				TextPropertyBag * bag = world->GetMagicBag(token);
				LoadArrayOfText(textiter.get<picojson::object>().find("textlines")->second, world, bag);
			}
		}
	}
}


void DeserializerFactory::LoadArrayOfEvents(const picojson::value & eventarray, ScriptWorld * world, FormulaParser * parser, Scriptable * scriptable) {
	auto & events = eventarray.get<picojson::array>();
	for(auto & evententry : events) {
		if(!evententry.is<picojson::object>())
			continue;

		auto & obj = evententry.get<picojson::object>();

		auto nameiter = obj.find("name");
		if(nameiter == obj.end() || !nameiter->second.is<std::string>())
			continue;

		const std::string & name = nameiter->second.get<std::string>();

		ActionSet actions;
		LoadArrayOfActions("actions", obj, &actions, world, parser);

		unsigned eventToken = world->GetTokenPool().AddToken(name);
		scriptable->GetEvents()->AddHandler(eventToken, std::move(actions));
	}
}
