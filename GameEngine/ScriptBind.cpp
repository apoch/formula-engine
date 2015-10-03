#include "Pch.h"

#include "../FormulaEngine/EngineBind.h"
#include "../FormulaEngine/TokenPool.h"

#include "ScriptBind.h"

#include "Unit.h"


namespace Game {


Binder::Binder(TokenPool * pool)
	: m_tokens(pool)
{
	m_unitBindTable.BindTokenToFunction(pool->AddToken("RedColor"), &Unit::SetRedColor);
	m_unitBindTable.BindTokenToFunction(pool->AddToken("BlueColor"), &Unit::SetBlueColor);
}



IEngineBinding * Binder::CreateBinding(unsigned token) {
	if(!m_tokens)
		return nullptr;

	if(m_tokens->GetStringFromToken(token) == "Unit")
		return new Binding<Unit>(Unit(0, 0), &m_unitBindTable);

	return nullptr;
}


} // Game namespace

