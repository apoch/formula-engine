//
// FormulaEngine Project
// By Mike Lewis - 2015
//
// Implementation of game "unit" objects
//

#include "Pch.h"

#include "Unit.h"


#include "FormulaEngine/Interfaces.h"
#include "FormulaEngine/Formula.h"
#include "FormulaEngine/TokenPool.h"
#include "FormulaEngine/Actions.h"
#include "FormulaEngine/PropertyBag.h"
#include "FormulaEngine/EventHandler.h"
#include "FormulaEngine/Scriptable.h"
#include "FormulaEngine/ScriptWorld.h"


//
// Construct and initialize a unit object
//
Unit::Unit (unsigned x, unsigned y, unsigned maxX, unsigned maxY, Scriptable * boundScriptable, ScriptWorld * world) {
	m_location.x = ValueT(x);
	m_location.y = ValueT(y);

	m_bounds.x = ValueT(maxX);
	m_bounds.y = ValueT(maxY);

	m_desired = m_location;

	m_scriptable = boundScriptable;
	m_world = world;

	m_arrivalToken = m_world->GetTokenPool().AddToken("OnArrive");
}


//
// Advance the world simulation by one tick
//
// Units generate an arrival event for scripts to handle when they
// reach the grid cell they have designated as their desired location.
//
// In this implementation, units also arrive at their desired cell
// in the next tick after declaring their intent.
//
void Unit::AdvanceTick () {
	if (m_location.x != m_desired.x || m_location.y != m_desired.y) {
		m_location = m_desired;
		m_world->QueueEvent(m_scriptable, m_arrivalToken, nullptr);
	}
}

//
// Set the desired location to a grid cell in the given direction
//
void Unit::MoveDirection (ValueT xDir, ValueT yDir) {
	SetLocationClamped(m_location.x + xDir, m_location.y + yDir);
}

//
// Set the desired location to the given grid cell
//
void Unit::Teleport (ValueT x, ValueT y) {
	SetLocationClamped(x, y);
}

//
// Stash a color value (used for tagging units in some demos)
//
void Unit::SetBlueColor (ValueT blue) {
	m_blue = blue;
}

//
// Register desire to move to the given grid cell, clamped to map bounds
//
void Unit::SetLocationClamped (ValueT x, ValueT y) {
	if (x < 0.0)
		x = m_bounds.x;
	else if (x >= m_bounds.x)
		x = 0.0;

	if (y < 0.0)
		y = m_bounds.y;
	else if (y >= m_bounds.y)
		y = 0.0;

	m_desired.x = x;
	m_desired.y = y;
}

