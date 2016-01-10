#pragma once


class Scriptable;
class ScriptWorld;


struct Coords {
	double x;
	double y;
};

enum Direction {
	DIRECTION_NORTH,
	DIRECTION_SOUTH,
	DIRECTION_EAST,
	DIRECTION_WEST,
	DIRECTIONS
};


class Unit {
public:			// Construction and destruction
	Unit(unsigned x, unsigned y, unsigned maxX, unsigned maxY, Scriptable * boundScriptable, ScriptWorld * world) {
		m_location.x = double(x);
		m_location.y = double(y);

		m_bounds.x = double(maxX);
		m_bounds.y = double(maxY);

		m_desired = m_location;

		m_scriptable = boundScriptable;
		m_world = world;
	}

	virtual ~Unit() { }

public:
	void AdvanceTick();

public:			// Coordinates
	const Coords & GetCoordinates() const			{ return m_location; }
	void GetCoordinatesForScript(double * x, double * y) const {
		*x = m_location.x;
		*y = m_location.y;
	}
	
	void MoveDirection(double xDir, double yDir);
	void Teleport(double x, double y);

public:			// Additional stuff
	bool IsBlue() const								{ return m_blue > 0.0; }
	void SetBlueColor(double blue);

private:
	void SetLocationClamped(double x, double y);

private:		// Internal state
	Coords m_location;
	Coords m_desired;
	Coords m_bounds;
	double m_blue = -1.0;

	Scriptable * m_scriptable;
	ScriptWorld * m_world;
};
