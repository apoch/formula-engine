//
// FormulaEngine Project
// By Mike Lewis - 2015
//
// Grid-based map wrapper implementation
//


#include "Pch.h"

#include "Map.h"
#include "Unit.h"


//
// Construct and initialize a map wrapper
//
Map::Map (unsigned width, unsigned height)
	: m_maxX(width),
	  m_maxY(height)
{
}

//
// Destruct and clean up a map wrapper
//
// Owned units are destroyed as part of this process
//
Map::~Map () {
	for (auto & unit : m_ownedUnits)
		delete unit;
}


//
// Add a unit to the map; the unit becomes owned
// by the map wrapper after this call and will be
// destructed automatically.
//
void Map::AddUnit (Unit * unit) {
	m_ownedUnits.push_back(unit);
}


//
// Advance the world simulation by one tick
//
// Forwards the notification to all owned units.
//
void Map::AdvanceTick () {
	for (auto & unit : m_ownedUnits)
		unit->AdvanceTick();
}



