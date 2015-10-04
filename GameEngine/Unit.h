#pragma once


struct Coords {
	unsigned x;
	unsigned y;
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
	Unit(unsigned x, unsigned y) {
		m_location.x = x;
		m_location.y = y;
	}

	virtual ~Unit() { }

public:			// Coordinates
	const Coords & GetCoordinates() const			{ return m_location; }
	
	bool MoveDirection(Direction dir);
	void Teleport(double x, double y);

public:			// Additional stuff
	bool IsBlue() const								{ return m_blue > 0.0; }
	void SetBlueColor(double blue);

private:		// Internal state
	Coords m_location;
	double m_blue = -1.0;
};

