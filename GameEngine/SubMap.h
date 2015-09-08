#pragma once


class SubMap : public Map, public Unit {
public:			// Construction
	SubMap(unsigned width, unsigned height, unsigned x, unsigned y)
		: Map(width, height),
		  Unit(x, y)
	{ }

public:			// Unit interaction interface
	using Map::AddUnit;

public:			// Coordinates
	using Unit::GetCoordinates;
};


