#include "Pch.h"

#include "Unit.h"


#include "../FormulaEngine/Formula.h"
#include "../FormulaEngine/TokenPool.h"
#include "../FormulaEngine/Actions.h"
#include "../FormulaEngine/PropertyBag.h"
#include "../FormulaEngine/EventHandler.h"
#include "../FormulaEngine/Scriptable.h"
#include "../FormulaEngine/ScriptWorld.h"


void Unit::AdvanceTick() {
	if(m_location.x != m_desired.x || m_location.y != m_desired.y) {
		m_location = m_desired;
		m_world->QueueEvent(m_scriptable, m_world->GetTokenPool().AddToken("OnArrive"), nullptr);
	}
}


void Unit::MoveDirection(double xDir, double yDir) {
	SetLocationClamped(m_location.x + xDir, m_location.y + yDir);
}


void Unit::Teleport(double x, double y) {
	SetLocationClamped(x, y);
}

void Unit::SetBlueColor(double blue) {
	m_blue = blue;
}

void Unit::SetLocationClamped(double x, double y) {
	if(x < 0.0)
		x = m_bounds.x;
	else if(x >= m_bounds.x)
		x = 0.0;

	if(y < 0.0)
		y = m_bounds.y;
	else if(y >= m_bounds.y)
		y = 0.0;

	m_desired.x = x;
	m_desired.y = y;
}

