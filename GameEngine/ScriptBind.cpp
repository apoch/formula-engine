#include "Pch.h"

#include "../FormulaEngine/EngineBind.h"
#include "../FormulaEngine/TokenPool.h"

#include "ScriptBind.h"

#include "Unit.h"
#include "Map.h"


namespace Game {


Binder::Binder(TokenPool * pool, Map * map)
	: m_tokens(pool),
	  m_map(map)
{
	m_unitBindTable.BindTokenToFunction(pool->AddToken("Teleport"), &Unit::Teleport);
}



IEngineBinding * Binder::CreateBinding(unsigned token) {
	if(!m_tokens)
		return nullptr;

	if(m_tokens->GetStringFromToken(token) == "Unit") {
		Unit * unit = new Unit(0, 0);
		m_map->AddUnit(unit);
		return new Binding<Unit>(unit, &m_unitBindTable);
	}

	return nullptr;
}


} // Game namespace

