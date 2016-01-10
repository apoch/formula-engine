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
int _tmain() {

	// Optional memory leak checking
	/*
	{
		int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
		flag |= _CRTDBG_LEAK_CHECK_DF;
		_CrtSetDbgFlag(flag);

		_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
		_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
		_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
		_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
		_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
		_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

		//_CrtSetBreakAlloc(207737);
	}*/

	//
	// Optionally run the test suite
	//
	Tests::RunAll();


	//
	// Run the simulation
	//
	//Simulation::RunKingdomWar();
	Simulation::RunFlocking();



	return 0;
}



