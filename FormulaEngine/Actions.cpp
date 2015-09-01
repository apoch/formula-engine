#include "stdafx.h"
#include "Formula.h"
#include "Actions.h"
#include "PropertyBag.h"


void ActionSet::AddActionSetProperty(unsigned targetToken, Formula && payload) {
	ActionRecord rec;
	rec.action = ACTION_CODE_SET_PROPERTY;
	rec.targetToken = targetToken;
	rec.payload = std::move(payload);

	m_actions.emplace_back(rec);
}

void ActionSet::AddActionSetFormula(unsigned targetToken, Formula && payload) {
	ActionRecord rec;
	rec.action = ACTION_CODE_SET_FORMULA;
	rec.targetToken = targetToken;
	rec.payload = std::move(payload);

	m_actions.emplace_back(rec);
}

void ActionSet::AddActionListAddEntry(unsigned listToken, const Scriptable & entry) {
	ActionRecord rec;
	rec.action = ACTION_CODE_LIST_ADD;
	rec.targetToken = listToken;
	rec.entry = &entry;

	m_actions.emplace_back(rec);
}

ResultCode ActionSet::Execute(IActionPerformer * targetBag, unsigned contextScope, IPropertyBag * optionalContext) const {
	ScopedPropertyBag scopes;
	scopes.GetScopes().AddScope(0, targetBag->GetProperties());
	if(optionalContext)
		scopes.GetScopes().AddScope(contextScope, *optionalContext);

	for(auto & action : m_actions) {
		switch(action.action) {
		case ACTION_CODE_SET_PROPERTY:
			{
				Result result = action.payload.Evaluate(&scopes);
				if(result.code == RESULT_CODE_OK)
					targetBag->SetProperty(action.targetToken, result.value);
				else
					return result.code;
			}
			break;

		case ACTION_CODE_SET_FORMULA:
			targetBag->SetFormula(action.targetToken, action.payload);
			break;

		case ACTION_CODE_LIST_ADD:
			targetBag->ListAddEntry(action.targetToken, *action.entry);
			break;

		default:
			return RESULT_CODE_SYNTAX_ERROR;
		}
	}

	return RESULT_CODE_OK;
}


