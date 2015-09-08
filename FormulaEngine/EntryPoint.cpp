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

#include "../GameEngine/Map.h"
#include "../GameEngine/Unit.h"
#include "../GameEngine/SubMap.h"


static void SimulationRunKingdomWar() {
	const unsigned worldWidth = 20;
	const unsigned worldHeight = 20;

	const unsigned cellWidth = 20;
	const unsigned cellHeight = 20;

	Map worldMap(worldWidth, worldHeight);
	for(unsigned x = 0; x < worldWidth; ++x) {
		for(unsigned y = 0; y < worldHeight; ++y) {
			SubMap * cell = new SubMap(cellWidth, cellHeight, x, y);
			worldMap.AddUnit(cell);
		}
	}

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

