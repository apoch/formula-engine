#include "Pch.h"

#include "Map.h"
#include "Unit.h"


Map::Map(unsigned width, unsigned height) {

}


Map::~Map() {
	for(auto & unit : m_ownedUnits)
		delete unit;
}


void Map::AddUnit(Unit * unit) {
	m_ownedUnits.push_back(unit);
}


