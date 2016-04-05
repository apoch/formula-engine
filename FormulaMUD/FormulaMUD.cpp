// FormulaMUD.cpp : Defines the entry point for the console application.
//

#include "Pch.h"

#include "Room.h"
#include "CommandTable.h"
#include "WorldState.h"
#include "Bindings.h"
#include "Console.h"



namespace {

void RunMud () {
	TokenPool tokens;

	Game::CommandTable commands("Data\\CommandList.json", &tokens);
	Game::WorldState state;

	state.commands = &commands;

	Game::Binder binder(&tokens, &state);

	ScriptWorld world(&tokens, &binder);

	DeserializerFactory::LoadFileIntoScriptWorld("Data\\FormulaMUD.json", &world);

	Game::RoomNetwork roomNetwork("Data\\Rooms.json", &tokens, &world, &state);
	state.roomNetwork = &roomNetwork;



	Console::Init();

	world.QueueBroadcastEvent("OnUserConnect");
	while (world.DispatchEvents());


	while (state.alive) {
		while (world.DispatchEvents());

		unsigned sleep = world.PeekTimeUntilNextEvent();
		if (sleep > 250)
			sleep = 250;

		std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
	}
}

}



int main() {

	// Optional memory leak checking
	Utilities::LeakCheck();

	RunMud();

    return 0;
}


