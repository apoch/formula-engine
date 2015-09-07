// FormulaEngine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Tests.h"




#include "Formula.h"
#include "Actions.h"
#include "Parser.h"
#include "PropertyBag.h"
#include "TokenPool.h"
#include "EventHandler.h"
#include "Scriptable.h"
#include "ScriptWorld.h"
#include "DeserializerFactory.h"


static void SimulationRunKingdomWar() {
	ScriptWorld world;
	DeserializerFactory factory;

	factory.LoadFileIntoScriptWorld("Data\\KingdomWar.json", &world);

	world.QueueBroadcastEvent("OnCreate");

	while(world.DispatchEvents());

	world.DumpOverview();
}




int _tmain(int argc, _TCHAR* argv[]) {
	//TestsRunAll();

	SimulationRunKingdomWar();

	return 0;
}

