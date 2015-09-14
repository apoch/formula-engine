//
// FormulaEngine Project
// By Mike Lewis - 2015
//
// Project entry point routine
//


#include "Pch.h"

#include "Tests.h"
#include "Simulation.h"


// This is Microsoft-specific for _TCHAR and _tmain.
// The entry point can be trivially rewritten for other
// compilers/platforms, so I'm not putting much effort
// into abstracting away those dependencies for now.
#include <tchar.h>


//
// Entry point for the program
//
int _tmain(int argc, _TCHAR* argv[]) {
	
	
	//
	// Optionally run the test suite
	//
	//Tests::RunAll();


	//
	// Run the simulation
	//
	Simulation::RunKingdomWar();



	return 0;
}

