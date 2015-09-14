#include "Pch.h"

#include "Formula.h"
#include "TokenPool.h"
#include "Actions.h"
#include "PropertyBag.h"
#include "EventHandler.h"
#include "Scriptable.h"
#include "ScriptWorld.h"
#include "EngineBind.h"


void ActionSet::AddActionEventRepeat(unsigned eventToken, Formula && counter) {
	ActionRecord rec;
	rec.action = ACTION_CODE_EVENT_REPEAT;
	rec.targetToken = eventToken;
	rec.payload = std::move(counter);

	m_actions.emplace_back(rec);
}

void ActionSet::AddActionSetGoalState(unsigned scopeToken, unsigned targetToken, Formula && payload) {
	ActionRecord rec;
	rec.action = ACTION_CODE_SET_GOAL_STATE;
	rec.targetScope = scopeToken;
	rec.targetToken = targetToken;
	rec.payload = std::move(payload);

	m_actions.emplace_back(rec);
}

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

void ActionSet::AddActionListSpawnEntry(unsigned listToken, unsigned archetypeToken) {
	ActionRecord rec;
	rec.action = ACTION_CODE_LIST_SPAWN;
	rec.targetToken = listToken;
	rec.archetypeToken = archetypeToken;

	m_actions.emplace_back(rec);
}

ResultCode ActionSet::Execute(ScriptWorld * world, Scriptable * target, unsigned contextScope, IPropertyBag * optionalContext) const {
	ScopedPropertyBag scopes;
	scopes.GetScopes().AddScope(0, target->GetScopes().GetProperties());
	if(optionalContext)
		scopes.GetScopes().AddScope(contextScope, *optionalContext);

	for(auto & action : m_actions) {
		switch(action.action) {
		case ACTION_CODE_SET_PROPERTY:
			{
				Result result = action.payload.Evaluate(&scopes);
				if(result.code == RESULT_CODE_OK)
					target->GetScopes().SetProperty(action.targetToken, result.value);
				else
					return result.code;
			}
			break;

		case ACTION_CODE_SET_FORMULA:
			target->GetScopes().SetFormula(action.targetToken, action.payload);
			break;

		case ACTION_CODE_SET_GOAL_STATE:
			{
				Result result = action.payload.Evaluate(&scopes);
				if(result.code == RESULT_CODE_OK) {
					IEngineBinding * binding = target->GetBinding(action.targetScope);
					if(binding)
						binding->SetGoalState(action.targetToken, result.value);
				}
				else
					return result.code;
			}
			break;

		case ACTION_CODE_LIST_ADD:
			target->GetScopes().ListAddEntry(action.targetToken, *action.entry);
			break;

		case ACTION_CODE_LIST_SPAWN:
			{
				Scriptable * instance = world->InstantiateArchetype(action.archetypeToken);
				if(instance) {
					target->GetScopes().ListAddEntry(action.targetToken, *instance);
				}
			}
			break;

		case ACTION_CODE_EVENT_REPEAT:
			{
				Result result = action.payload.Evaluate(&scopes);
				if(result.code != RESULT_CODE_OK)
					return result.code;

				unsigned counter = unsigned(result.value);
				for(unsigned i = 0; i < counter; ++i) {
					world->QueueEvent(target, action.targetToken);
				}
			}
			break;

		default:
			return RESULT_CODE_SYNTAX_ERROR;
		}
	}

	return RESULT_CODE_OK;
}


