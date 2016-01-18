//
// FormulaEngine Project
// By Mike Lewis - 2015
//
// Simulation wrapper API header
//
// This header provides entry points into the various
// bits of simulation/game logic that are exposed to
// the outside world. As might be expected, the surface
// of the API is minimal, since the vast majority of
// the simulation logic is self-contained.
//

#pragma once


namespace Simulation {


// Run a complete simulation of the "Kingdom War" example
void RunKingdomWar ();


// Run a simulation of the "Flocking" example
void RunFlocking ();


}

