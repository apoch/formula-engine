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
int main () {

	// Optional memory leak checking
	//Utilities::LeakCheck();

	//
	// Optionally run the test suite
	//
	Tests::RunAll();


	//
	// Run the simulation
	//
	//Simulation::RunKingdomWar();
	Simulation::RunFlocking(false);



	return 0;
}



