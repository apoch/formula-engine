#pragma once


class ScriptWorld;


class DeserializerFactory {
public:
	void LoadFileIntoScriptWorld(const char filename[], ScriptWorld * world);
};

