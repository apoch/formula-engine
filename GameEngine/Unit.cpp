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
	double xCur = static_cast<double>(m_location.x);
	double yCur = static_cast<double>(m_location.y);

	SetLocationClamped(xCur + xDir, yCur + yDir);
}


void Unit::Teleport(double x, double y) {
	SetLocationClamped(x, y);
	m_location = m_desired;
}

void Unit::SetBlueColor(double blue) {
	m_blue = blue;
}

void Unit::SetLocationClamped(double x, double y) {
	if(x < 0.0)
		x = 0.0;
	else if(x > m_bounds.x)
		x = m_bounds.x;

	if(y < 0.0)
		y = 0.0;
	else if(y > m_bounds.y)
		y = m_bounds.y;

	m_desired.x = static_cast<unsigned>(x);
	m_desired.y = static_cast<unsigned>(y);
}

