#include "Pch.h"

#include "Map.h"
#include "Unit.h"


Map::Map(unsigned width, unsigned height)
	: m_maxX(width),
	  m_maxY(height)
{
}


Map::~Map() {
	for(auto & unit : m_ownedUnits)
		delete unit;
}


void Map::AddUnit(Unit * unit) {
	m_ownedUnits.push_back(unit);
}


void Map::AdvanceTick() {
	for(auto & unit : m_ownedUnits)
		unit->AdvanceTick();
}



