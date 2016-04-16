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

#include "FormulaEngine/Interfaces.h"
#include "FormulaEngine/Formula.h"
#include "FormulaEngine/Actions.h"
#include "FormulaEngine/Parser.h"
#include "FormulaEngine/TokenPool.h"
#include "FormulaEngine/PropertyBag.h"
#include "FormulaEngine/EventHandler.h"
#include "FormulaEngine/Scriptable.h"
#include "FormulaEngine/ScriptWorld.h"
#include "FormulaEngine/DeserializerFactory.h"
#include "FormulaEngine/EngineBind.h"

#include "GameEngine/Map.h"
#include "GameEngine/Unit.h"
#include "GameEngine/ScriptBind.h"


namespace Simulation {


//
// Set up the engine preconditions and drive a complete
// simulation of the "Kingdom War" example.
//
void RunKingdomWar () {
	const unsigned worldWidth = 20;
	const unsigned worldHeight = 20;

	Map worldMap(worldWidth, worldHeight);

	TokenPool pool;
	Game::Binder binder(&pool, &worldMap);

	ScriptWorld world(&pool, &binder);
	DeserializerFactory::LoadFileIntoScriptWorld("Data\\KingdomWar.json", &world);

	world.QueueBroadcastEvent("OnCreate");

	for (unsigned i = 0; i < 10; ++i) {
		while (world.DispatchEvents());

		world.DumpOverview();

		std::vector<const Unit *> buffer;
		buffer.reserve(25000);

		for (unsigned y = 0; y < worldHeight; ++y) {
			for (unsigned x = 0; x < worldWidth; ++x) {
				worldMap.GetUnitsByPosition(x, y, [](const Unit * unit) { return !unit->IsBlue(); }, &buffer);
				bool red = buffer.size() > 0;

				worldMap.GetUnitsByPosition(x, y, [](const Unit * unit) { return unit->IsBlue(); }, &buffer);
				bool blue = buffer.size() > 0;

				if (red && blue)
					std::cout << "X";
				else if (red)
					std::cout << "r";
				else if (blue)
					std::cout << "B";
				else
					std::cout << "-";
			}

			std::cout << "\n";
		}

		worldMap.AdvanceTick();
	}
}


//
// Run the Flocking demo
//
void RunFlocking (bool allowConsoleOutput) {
	// TODO - use the world params in the JSON instead of hard coding them here
	const unsigned worldWidth = 60;
	const unsigned worldHeight = 20;

	Map worldMap(worldWidth, worldHeight);

	TokenPool pool;
	Game::Binder binder(&pool, &worldMap);

	ScriptWorld world(&pool, &binder);
	DeserializerFactory::LoadFileIntoScriptWorld("Data\\Flocking.json", &world);

	world.QueueBroadcastEvent("OnCreate");

	unsigned limit = allowConsoleOutput ? 10000 : 300000;
	std::vector<const Unit *> buffer;
	buffer.reserve(500);

	for (unsigned i = 0; i < limit; ++i) {
		while (world.DispatchEvents());

		buffer.clear();

		if (allowConsoleOutput) {
			for (unsigned y = 0; y < worldHeight; ++y) {
				for (unsigned x = 0; x < worldWidth; ++x) {
					worldMap.GetUnitsByPosition(x, y, [](const Unit *) { return true; }, &buffer);

					if (buffer.size() >= 10)
						std::cout << "O";
					else if (buffer.size() >= 3)
						std::cout << "o";
					else if (buffer.size() > 0)
						std::cout << ".";
					else
						std::cout << " ";
				}

				if (allowConsoleOutput)
					std::cout << "\n";
			}
		}

		worldMap.AdvanceTick();

		if (allowConsoleOutput)
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}

	if (!allowConsoleOutput)
		std::cout << "Evaluation count: " << Formula::GetEvaluationCounter() << std::endl;
}


} // Simulation namespace


