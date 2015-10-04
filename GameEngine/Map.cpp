#include "Pch.h"

#include "Map.h"
#include "Unit.h"


Map::Map(unsigned width, unsigned height) {
	((void)(width));
	((void)(height));
}


Map::~Map() {
	for(auto & unit : m_ownedUnits)
		delete unit;
}


void Map::AddUnit(Unit * unit) {
	m_ownedUnits.push_back(unit);
}


std::vector<const Unit *> Map::GetUnitsByPosition(unsigned x, unsigned y) const {
	std::vector<const Unit *> ret;

	for(auto & unit : m_ownedUnits) {
		if(unit->GetCoordinates().x == x && unit->GetCoordinates().y == y)
			ret.push_back(unit);
	}

	return ret;
}

