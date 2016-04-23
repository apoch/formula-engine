//
// FormulaEngine Project
// By Mike Lewis - 2015
//
// Declarations for game "unit" objects
//

#pragma once


// Forward declarations
class Scriptable;
class ScriptWorld;


//
// Helper structure for representing coordinates
//
struct Coords {
	ValueT x;
	ValueT y;
};


//
// A basic game unit, meant to represent some kind of autonomous character
//
// Units occupy a single grid cell on a map. They can move freely based on
// rules established in the script side. Units bind to exaclty one entity,
// as chosen by the script engine.
//
class Unit {
public:			// Construction
	Unit (unsigned x, unsigned y, unsigned maxX, unsigned maxY, Scriptable * boundScriptable, ScriptWorld * world);

public:			// Simulation advancement
	void AdvanceTick ();

public:			// Coordinates
	const Coords & GetCoordinates () const			{ return m_location; }
	void GetCoordinatesForScript (ValueT * x, ValueT * y) const {
		*x = m_location.x;
		*y = m_location.y;
	}
	
	void MoveDirection (ValueT xDir, ValueT yDir);
	void Teleport (ValueT x, ValueT y);

public:			// Additional stuff
	bool IsBlue () const							{ return m_blue > 0.0; }
	void SetBlueColor (ValueT blue);

private:		// Internal helpers
	void SetLocationClamped (ValueT x, ValueT y);

private:		// Internal state
	Coords m_location;
	Coords m_desired;
	Coords m_bounds;
	ValueT m_blue = -1.0;

	Scriptable * m_scriptable;
	ScriptWorld * m_world;

	unsigned m_arrivalToken;
};

