//
// FormulaEngine Project
// By Mike Lewis - 2015
//
// Grid-based map wrapper declaration
//

#pragma once


// Forward declarations
class Unit;


//
// Wrapper class for a grid-style game map
//
// Owns a list of units which are placed on the map;
// can manipulate them directly or by grid position.
//
class Map {
public:			// Construction and destruction
	Map (unsigned width, unsigned height);
	virtual ~Map ();

public:			// Game simulation advancement
	void AdvanceTick ();

public:			// Unit interaction interface
	void AddUnit (Unit * unit);

	unsigned GetMaxX () const {
		return m_maxX;
	}

	unsigned GetMaxY () const {
		return m_maxY;
	}

	//
	// Retrieve an optionally filtered list of units
	// present in a specified grid cell.
	//
	template <typename FilterT>
	void GetUnitsByPosition (unsigned x, unsigned y, const FilterT & filter, std::vector<const Unit *> * out) const {
		out->clear();
		for (auto & unit : m_ownedUnits) {
			auto & pos = unit->GetCoordinates();
			if (unsigned(pos.x) == x && unsigned(pos.y) == y && filter(unit))
				out->push_back(unit);
		}
	}

private:		// Internal state
	std::vector<Unit *> m_ownedUnits;
	unsigned m_maxX;
	unsigned m_maxY;
};


