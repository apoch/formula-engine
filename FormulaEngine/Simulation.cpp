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
#include "EngineBind.h"

#include "../GameEngine/Map.h"
#include "../GameEngine/Unit.h"
#include "../GameEngine/ScriptBind.h"


namespace Simulation {


//
// Set up the engine preconditions and drive a complete
// simulation of the "Kingdom War" example. See comments
// in KingdomWar.JSON in the Data directory for details.
//
void RunKingdomWar() {
	const unsigned worldWidth = 20;
	const unsigned worldHeight = 20;

	Map worldMap(worldWidth, worldHeight);

	TokenPool pool;
	Game::Binder binder(&pool, &worldMap);

	ScriptWorld world(&pool, &binder);
	DeserializerFactory factory;

	factory.LoadFileIntoScriptWorld("Data\\KingdomWar.json", &world);

	world.QueueBroadcastEvent("OnCreate");

	for(unsigned i = 0; i < 10; ++i) {
		while(world.DispatchEvents());

		world.DumpOverview();

		std::vector<const Unit *> buffer;
		buffer.reserve(25000);

		for(unsigned y = 0; y < worldHeight; ++y) {
			for(unsigned x = 0; x < worldWidth; ++x) {
				worldMap.GetUnitsByPosition(x, y, [](const Unit * unit) { return !unit->IsBlue(); }, &buffer);
				bool red = buffer.size() > 0;

				worldMap.GetUnitsByPosition(x, y, [](const Unit * unit) { return unit->IsBlue(); }, &buffer);
				bool blue = buffer.size() > 0;

				if(red && blue)
					std::cout << "X";
				else if(red)
					std::cout << "r";
				else if(blue)
					std::cout << "B";
				else
					std::cout << "-";
			}

			std::cout << "\n";
		}

		worldMap.AdvanceTick();
	}
}


} // Simulation namespace


