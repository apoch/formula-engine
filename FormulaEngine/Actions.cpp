#include "Pch.h"

#include "Formula.h"
#include "TokenPool.h"
#include "Actions.h"
#include "PropertyBag.h"
#include "EventHandler.h"
#include "Scriptable.h"
#include "ScriptWorld.h"
#include "EngineBind.h"



ActionSet::ActionSet(ActionSet && other) {
	m_actions = std::move(other.m_actions);
	m_ownedBags = std::move(other.m_ownedBags);
}

ActionSet::ActionSet(const ActionSet & other)
	: m_actions(other.m_actions)
{
	for(auto & action : m_actions) {
		if(action.bag) {
			action.bag = new FormulaPropertyBag(*action.bag);
			m_ownedBags.push_back(action.bag);
		}
	}
}

ActionSet::~ActionSet() {
	for(auto & bag : m_ownedBags)
		delete bag;
}


void ActionSet::AddActionEventRepeat(unsigned eventToken, Formula && counter, FormulaPropertyBag * bag) {
	ActionRecord rec;
	rec.action = ACTION_CODE_EVENT_REPEAT;
	rec.targetToken = eventToken;
	rec.payload = std::move(counter);
	rec.bag = bag;

	if(bag)
		m_ownedBags.push_back(bag);

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

void ActionSet::AddActionListSpawnEntry(unsigned listToken, unsigned archetypeToken, FormulaPropertyBag * bag) {
	ActionRecord rec;
	rec.action = ACTION_CODE_LIST_SPAWN;
	rec.targetToken = listToken;
	rec.archetypeToken = archetypeToken;
	rec.bag = bag;

	if(bag)
		m_ownedBags.push_back(bag);

	m_actions.emplace_back(rec);
}

ResultCode ActionSet::Execute(ScriptWorld * world, Scriptable * target, unsigned contextScope, const IPropertyBag * optionalContext) const {
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
				SimplePropertyBag * bagptr = nullptr;
				if(action.bag) {
					bagptr = new SimplePropertyBag;
					action.bag->Flatten(bagptr, &scopes);
				}

				Scriptable * instance = world->InstantiateArchetype(action.archetypeToken, bagptr);
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
					SimplePropertyBag * bagptr = nullptr;
					if(action.bag) {
						bagptr = new SimplePropertyBag;
						action.bag->Flatten(bagptr, &scopes);
					}

					world->QueueEvent(target, action.targetToken, bagptr);
				}
			}
			break;

		default:
			return RESULT_CODE_SYNTAX_ERROR;
		}
	}

	return RESULT_CODE_OK;
}


