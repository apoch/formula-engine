//
// FormulaEngine Project
// By Mike Lewis - 2015
//
// Script-to-engine bindings implementation
//

#include "Pch.h"

#include "FormulaEngine/EngineBind.h"
#include "FormulaEngine/TokenPool.h"

#include "ScriptBind.h"

#include "Unit.h"
#include "Map.h"


namespace Game {


//
// Construct and initialize a binding factory wrapper
//
// Initializes the binding tables for later use by mapping binding
// tokens to member function pointers on the bound types.
//
Binder::Binder (TokenPool * pool, Map * map)
	: m_tokens(pool),
	  m_map(map)
{
	m_unitBindTable.BindTokenToFunction(pool->AddToken("Teleport"), &Unit::Teleport);
	m_unitBindTable.BindTokenToFunction(pool->AddToken("BlueColor"), &Unit::SetBlueColor);
	m_unitBindTable.BindTokenToFunction(pool->AddToken("MoveDirection"), &Unit::MoveDirection);

	m_unitBindTable.BindTokenToProperty(pool->AddToken("Position"), &Unit::GetCoordinatesForScript);
}


//
// Create a binding between a script object and a game engine object
//
// In this configuration we generate a new game object at the time of the
// binding request to "back" the script object. Other approaches are also
// reasonable, but this is the most natural way in the current design.
//
IEngineBinding * Binder::CreateBinding (Scriptable * scriptable, ScriptWorld * world, unsigned token) {
	if (!m_tokens)
		return nullptr;

	if (m_tokens->GetStringFromToken(token) == "Unit") {
		Unit * unit = new Unit(0, 0, m_map->GetMaxX(), m_map->GetMaxY(), scriptable, world);
		m_map->AddUnit(unit);
		return new Binding<Unit>(unit, &m_unitBindTable);
	}

	return nullptr;
}


} // Game namespace

