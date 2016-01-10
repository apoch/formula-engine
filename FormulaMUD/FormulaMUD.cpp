// FormulaMUD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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



int main() {

	TokenPool tokens;
	ScriptWorld world(&tokens, nullptr);

	DeserializerFactory factory;

	factory.LoadFileIntoScriptWorld("Data\\FormulaMUD.json", &world);

	world.QueueBroadcastEvent("OnCreate");

	while (world.DispatchEvents());

	world.DumpOverview();

    return 0;
}

