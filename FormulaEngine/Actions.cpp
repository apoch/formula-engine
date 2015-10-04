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
	std::swap(m_actions, other.m_actions);
}

ActionSet::ActionSet(const ActionSet & other) {
	for(auto & action : other.m_actions) {
		m_actions.push_back(action->Clone());
	}
}

ActionSet::~ActionSet() {
	for(auto & action : m_actions)
		delete action;
}

void ActionSet::AddAction(IAction * action) {
	m_actions.push_back(action);
}

ResultCode ActionSet::Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const {
	for(auto & action : m_actions) {
		ResultCode code = action->Execute(world, target, scopes);
		if(code != RESULT_CODE_OK)
			return code;
	}

	return RESULT_CODE_OK;
}

ResultCode ActionSet::Execute(ScriptWorld * world, Scriptable * target, unsigned contextScope, const IPropertyBag * optionalContext) const {
	ScopedPropertyBag scopes;
	scopes.SetProperties(target->GetScopes().GetProperties());
	if(optionalContext)
		scopes.GetScopes().AddScope(contextScope, *optionalContext);

	return Execute(world, target, scopes);
}



ActionListSpawnEntry::ActionListSpawnEntry(unsigned listToken, unsigned archetypeToken, FormulaPropertyBag * paramBagPtr)
	: m_listToken(listToken),
	  m_archetypeToken(archetypeToken),
	  m_paramBag(paramBagPtr)
{
}

ActionListSpawnEntry::~ActionListSpawnEntry() {
	delete m_paramBag;
}

IAction * ActionListSpawnEntry::Clone() const {
	return new ActionListSpawnEntry(m_listToken, m_archetypeToken, m_paramBag ? new FormulaPropertyBag(*m_paramBag) : nullptr);
}

ResultCode ActionListSpawnEntry::Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const {
	SimplePropertyBag * bagptr = nullptr;
	if(m_paramBag) {
		bagptr = new SimplePropertyBag;
		m_paramBag->Flatten(bagptr, &scopes);
	}

	Scriptable * instance = world->InstantiateArchetype(m_archetypeToken, bagptr);
	if(instance) {
		target->GetScopes().ListAddEntry(m_listToken, *instance);
	}

	return RESULT_CODE_OK;
}


ActionSetGoalState::ActionSetGoalState(unsigned scopeToken, unsigned targetToken, Formula && formula)
	: m_scopeToken(scopeToken),
	  m_targetToken(targetToken),
	  m_formula(formula)
{
}

IAction * ActionSetGoalState::Clone() const {
	Formula copy(m_formula);
	return new ActionSetGoalState(m_scopeToken, m_targetToken, std::move(copy));
}

ResultCode ActionSetGoalState::Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const {
	((void)(world));

	Result result = m_formula.Evaluate(&scopes);
	if(result.code == RESULT_CODE_OK) {
		IEngineBinding * binding = target->GetBinding(m_scopeToken);
		if(binding) {
			if(result.type == RESULT_TYPE_SCALAR)
				binding->SetGoalState(m_targetToken, result.value);
			else if(result.type == RESULT_TYPE_VECTOR2)
				binding->SetGoalState(m_targetToken, result.value, result.value2);
		}
	}
	
	return result.code;
}


ActionEventRepeat::ActionEventRepeat(unsigned eventToken, Formula && repeatFormula, FormulaPropertyBag * parambagptr)
	: m_eventToken(eventToken),
 	  m_repeatFormula(repeatFormula),
 	  m_paramBag(parambagptr)
{
}

ActionEventRepeat::~ActionEventRepeat() {
	delete m_paramBag;
}

IAction * ActionEventRepeat::Clone() const {
	Formula formulacopy(m_repeatFormula);
	return new ActionEventRepeat(m_eventToken, std::move(formulacopy), m_paramBag ? new FormulaPropertyBag(*m_paramBag) : nullptr);
}

ResultCode ActionEventRepeat::Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const {
	Result result = m_repeatFormula.Evaluate(&scopes);
	if(result.code != RESULT_CODE_OK)
		return result.code;

	unsigned counter = unsigned(result.value);
	for(unsigned i = 0; i < counter; ++i) {
		SimplePropertyBag * bagptr = nullptr;
		if(m_paramBag) {
			bagptr = new SimplePropertyBag;
			m_paramBag->Flatten(bagptr, &scopes);
		}

		world->QueueEvent(target, m_eventToken, bagptr);
	}

	return RESULT_CODE_OK;
}


ActionSetProperty::ActionSetProperty(unsigned targetToken, Formula && payload)
	: m_targetToken(targetToken),
	  m_payload(payload)
{
}

IAction * ActionSetProperty::Clone() const {
	Formula copy(m_payload);
	return new ActionSetProperty(m_targetToken, std::move(copy));
}

ResultCode ActionSetProperty::Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const {
	((void)(world));

	Result result = m_payload.Evaluate(&scopes);
	if(result.code == RESULT_CODE_OK)
		target->GetScopes().SetProperty(m_targetToken, result.value);

	return result.code;
}


ActionListAddEntry::ActionListAddEntry(unsigned listToken, const Scriptable & scriptable)
	: m_listToken(listToken),
	  m_scriptable(&scriptable)
{
}

IAction * ActionListAddEntry::Clone() const {
	return new ActionListAddEntry(m_listToken, *m_scriptable);
}

ResultCode ActionListAddEntry::Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const {
	((void)(world));
	((void)(scopes));

	target->GetScopes().ListAddEntry(m_listToken, *m_scriptable);

	return RESULT_CODE_OK;
}



ActionConditionalBlock::ActionConditionalBlock(Formula && condition, ActionSet && actions, ActionSet && elseActions)
	: m_actions(actions),
	  m_else(elseActions)
{
	std::swap(m_condition, condition);
}

IAction * ActionConditionalBlock::Clone() const {
	Formula conditionCopy(m_condition);
	ActionSet actionCopy(m_actions);
	ActionSet elseCopy(m_else);
	return new ActionConditionalBlock(std::move(conditionCopy), std::move(actionCopy), std::move(elseCopy));
}

ResultCode ActionConditionalBlock::Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const {
	Result cond = m_condition.Evaluate(&scopes);
	if(cond.code != RESULT_CODE_OK)
		return cond.code;

	if(cond.value == 0.0)
		return m_else.Execute(world, target, scopes);

	return m_actions.Execute(world, target, scopes);
}

