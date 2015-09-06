// FormulaEngine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Tests.h"




#include "Formula.h"
#include "Actions.h"
#include "Parser.h"
#include "PropertyBag.h"
#include "TokenPool.h"
#include "Scriptable.h"
#include "ScriptWorld.h"
#include "DeserializerFactory.h"


static void SimulationRunKingdomWar() {
	TokenPool pool;
	FormulaParser parser;

	ScriptWorld world;
	DeserializerFactory factory;

	factory.LoadFileIntoScriptWorld("Data\\KingdomWar.json", &world);

	world.QueueBroadcastEvent("OnCreate");

	world.DispatchEvents();
}




int _tmain(int argc, _TCHAR* argv[]) {
	TestsRunAll();

	SimulationRunKingdomWar();

	return 0;
}

