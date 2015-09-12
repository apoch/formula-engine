//
// FormulaEngine Project
// By Mike Lewis - 2015
//
// Simulation drivers/high level implementation
//
// This module contains the logic needed to drive the
// remaining library/engine code through complete life
// cycles of a simulation.
//


#include "Pch.h"

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


namespace Simulation {


//
// Set up the engine preconditions and drive a complete
// simulation of the "Kingdom War" example. See comments
// in KingdomWar.JSON in the Data directory for details.
//
void RunKingdomWar() {
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


} // Simulation namespace


