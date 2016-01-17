#pragma once


class FormulaParser;
class Scriptable;
class ScriptWorld;


namespace picojson {
	class value;

	typedef std::vector<value> array;
}


namespace DeserializerFactory {
	void LoadFileIntoScriptWorld(const char filename[], ScriptWorld * world);

	void LoadArrayOfEvents(const picojson::value & eventarray, ScriptWorld * world, FormulaParser * parser, Scriptable * scriptable);
	void LoadArrayOfLists (const picojson::array & listarray, ScriptWorld * world, Scriptable * instance);
}

