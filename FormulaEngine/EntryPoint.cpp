//
// FormulaEngine Project
// By Mike Lewis - 2015
//
// Project entry point routine
//


#include "Pch.h"

#include "Tests.h"
#include "Simulation.h"


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

