#pragma once


class FormulaParser;
class Scriptable;
class ScriptWorld;


namespace picojson {
	class value;
}


namespace DeserializerFactory {
	void LoadFileIntoScriptWorld(const char filename[], ScriptWorld * world);

	void LoadArrayOfEvents(const picojson::value & eventarray, ScriptWorld * world, FormulaParser * parser, Scriptable * scriptable);
}

