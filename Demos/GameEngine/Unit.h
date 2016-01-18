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
	double x;
	double y;
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
	Unit (unsigned x, unsigned y, unsigned maxX, unsigned maxY, Scriptable * boundScriptable, ScriptWorld * world) {
		m_location.x = double(x);
		m_location.y = double(y);

		m_bounds.x = double(maxX);
		m_bounds.y = double(maxY);

		m_desired = m_location;

		m_scriptable = boundScriptable;
		m_world = world;
	}

public:			// Simulation advancement
	void AdvanceTick ();

public:			// Coordinates
	const Coords & GetCoordinates () const			{ return m_location; }
	void GetCoordinatesForScript (double * x, double * y) const {
		*x = m_location.x;
		*y = m_location.y;
	}
	
	void MoveDirection (double xDir, double yDir);
	void Teleport (double x, double y);

public:			// Additional stuff
	bool IsBlue () const							{ return m_blue > 0.0; }
	void SetBlueColor (double blue);

private:		// Internal helpers
	void SetLocationClamped (double x, double y);

private:		// Internal state
	Coords m_location;
	Coords m_desired;
	Coords m_bounds;
	double m_blue = -1.0;

	Scriptable * m_scriptable;
	ScriptWorld * m_world;
};

