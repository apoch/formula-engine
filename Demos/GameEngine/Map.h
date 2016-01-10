#pragma once


class Unit;


class Map {
public:			// Construction and destruction
	Map(unsigned width, unsigned height);
	virtual ~Map();


public:
	void AdvanceTick();

public:			// Unit interaction interface
	void AddUnit(Unit * unit);

	unsigned GetMaxX() const {
		return m_maxX;
	}

	unsigned GetMaxY() const {
		return m_maxY;
	}

	template <typename FilterT>
	void GetUnitsByPosition(unsigned x, unsigned y, const FilterT & filter, std::vector<const Unit *> * out) const {
		out->clear();
		for(auto & unit : m_ownedUnits) {
			auto & pos = unit->GetCoordinates();
			if(unsigned(pos.x) == x && unsigned(pos.y) == y && filter(unit))
				out->push_back(unit);
		}
	}

private:		// Internal state
	std::vector<Unit *> m_ownedUnits;
	unsigned m_maxX;
	unsigned m_maxY;
};


