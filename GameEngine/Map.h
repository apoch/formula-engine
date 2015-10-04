#pragma once


class Unit;


class Map {
public:			// Construction and destruction
	Map(unsigned width, unsigned height);
	virtual ~Map();

public:			// Unit interaction interface
	void AddUnit(Unit * unit);
	std::vector<const Unit *> GetUnitsByPosition(unsigned x, unsigned y) const;

private:		// Internal state
	std::vector<Unit *> m_ownedUnits;
};


