#include "stdafx.h"
#include "DeserializerFactory.h"
#include "Formula.h"
#include "Actions.h"
#include "PropertyBag.h"
#include "Scriptable.h"
#include "TokenPool.h"
#include "ScriptWorld.h"
#include "Parser.h"



typedef void (ScriptWorld::*RegistrationFunc)(const std::string &, Scriptable &&);
typedef Scriptable * (ScriptWorld::*LookupFunc)(unsigned);



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

					instance->GetScopes().ListAddEntry(token, *otherInstance);
				}
			}
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
	}
}


