#include "Pch.h"

#include "Unit.h"


void Unit::Teleport(double x, double y) {
	m_location.x = static_cast<unsigned>(x);
	m_location.y = static_cast<unsigned>(y);
}

