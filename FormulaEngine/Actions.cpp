#include "Pch.h"

#include "Formula.h"
#include "TokenPool.h"
#include "Actions.h"
#include "PropertyBag.h"
#include "EventHandler.h"
#include "Scriptable.h"
#include "ScriptWorld.h"
#include "EngineBind.h"



ActionSet::ActionSet()
	: m_scopeCache(new ScopedPropertyBag)
{
}

ActionSet::ActionSet(ActionSet && other) {
	std::swap(m_actions, other.m_actions);

	m_scopeCache = other.m_scopeCache;
	other.m_scopeCache = nullptr;
}

ActionSet::ActionSet(const ActionSet & other) {
	for(auto & action : other.m_actions) {
		m_actions.push_back(action->Clone());
	}

	m_scopeCache = new ScopedPropertyBag;
}

ActionSet::~ActionSet() {
	for(auto & action : m_actions)
		delete action;

	delete m_scopeCache;
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
	m_scopeCache->Clear();
	m_scopeCache->SetProperties(&target->GetScopes().GetProperties());
	BindingPropertyBag bag(target);
	m_scopeCache->SetBindings(bag);
	if (optionalContext) {
		m_scopeCache->GetScopes().AddScope(contextScope, *optionalContext);
		optionalContext->PopulateNamedBindings(m_scopeCache);
	}

	return Execute(world, target, *m_scopeCache);
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
	WorldPropertyBag bag(world, scopes);

	Result result = m_formula.Evaluate(&bag);
	if (result.code == RESULT_CODE_OK) {
		IEngineBinding * binding = target->GetBinding(m_scopeToken);
		if (!binding)
			binding = scopes.GetNamedBinding(m_scopeToken)->GetBinding(m_scopeToken);

		if (binding) {
			if(result.type == RESULT_TYPE_SCALAR)
				binding->SetGoalState(m_targetToken, result.value);
			else if(result.type == RESULT_TYPE_VECTOR2)
				binding->SetGoalState(m_targetToken, result.value, result.value2);
			else if(result.type == RESULT_TYPE_TOKEN)
				binding->SetGoalState(m_targetToken, result.token);
		}
	}
	
	return result.code;
}




ActionEventTrigger::ActionEventTrigger(unsigned eventToken, unsigned targetToken, FormulaPropertyBag * parambagptr)
	: m_eventToken(eventToken),
 	  m_targetToken(targetToken),
 	  m_paramBag(parambagptr)
{
}

ActionEventTrigger::~ActionEventTrigger() {
	delete m_paramBag;
}

IAction * ActionEventTrigger::Clone() const {
	return new ActionEventTrigger(m_eventToken, m_targetToken, m_paramBag ? new FormulaPropertyBag(*m_paramBag) : nullptr);
}

ResultCode ActionEventTrigger::Execute(ScriptWorld * world, Scriptable *, const ScopedPropertyBag & scopes) const {
	SimplePropertyBag * bagptr = nullptr;
	if(m_paramBag) {
		bagptr = new SimplePropertyBag;
		m_paramBag->Flatten(bagptr, &scopes);
	}

	world->QueueEvent(world->GetScriptable(m_targetToken), m_eventToken, bagptr);
	return RESULT_CODE_OK;
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
	WorldPropertyBag bag(world, scopes);
	Result result = m_repeatFormula.Evaluate(&bag);
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
	WorldPropertyBag bag(world, scopes);

	Result result = m_payload.Evaluate(&bag);
	if(result.code == RESULT_CODE_OK)
		target->GetScopes().SetProperty(m_targetToken, result);

	return result.code;
}


ActionListAddEntry::ActionListAddEntry(unsigned listToken, unsigned targetToken)
	: m_listToken(listToken),
	  m_targetToken(targetToken)
{
}

IAction * ActionListAddEntry::Clone() const {
	return new ActionListAddEntry(m_listToken, m_targetToken);
}

ResultCode ActionListAddEntry::Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const {
	((void)(scopes));

	target->GetScopes().ListAddEntry(m_listToken, *world->GetScriptable(m_targetToken));

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
	WorldPropertyBag bag(world, scopes);
	Result cond = m_condition.Evaluate(&bag);
	if(cond.code != RESULT_CODE_OK)
		return cond.code;

	if(cond.value == 0.0)
		return m_else.Execute(world, target, scopes);

	return m_actions.Execute(world, target, scopes);
}


ActionListForEach::ActionListForEach(unsigned scriptableToken, unsigned listToken, ActionSet && loopActions)
	: m_scriptableToken(scriptableToken),
	  m_listToken(listToken),
	  m_loopActions(loopActions)
{
}

IAction * ActionListForEach::Clone() const {
	ActionSet actionCopy(m_loopActions);
	return new ActionListForEach(m_scriptableToken, m_listToken, std::move(actionCopy));
}

ResultCode ActionListForEach::Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const {
	Scriptable * scriptable = world->GetScriptable(m_scriptableToken);
	if(!scriptable)
		scriptable = target;

	const ActionSet * myActions = &m_loopActions;

	return scriptable->GetScopes().ListEnumerate(m_listToken, [world, target, &scopes, myActions](const Scriptable * member){
		ScopedPropertyBag newScopes;
		newScopes.SetProperties(&target->GetScopes().GetProperties());

		if(target->GetScopes().GetBindings())
			newScopes.SetBindings(*target->GetScopes().GetBindings());

		if(member->GetScopes().GetBindings())
			newScopes.GetScopes().AddScope(world->GetTokenPool().AddToken("other"), *member->GetScopes().GetBindings());

		myActions->Execute(world, target, newScopes);
	});
}


ActionListTransfer::ActionListTransfer (Formula && condition, unsigned originToken, unsigned originListToken, unsigned targetToken, unsigned targetListToken)
	: m_condition(std::move(condition)),
	  m_originToken(originToken),
	  m_originListToken(originListToken),
	  m_targetToken(targetToken),
	  m_targetListToken(targetListToken)
{
}

IAction * ActionListTransfer::Clone () const {
	Formula conditionCopy(m_condition);

	return new ActionListTransfer(std::move(conditionCopy), m_originToken, m_originListToken, m_targetToken, m_targetListToken);
}

ResultCode ActionListTransfer::Execute (ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const {
	Scriptable * originScriptable = world->GetScriptable(m_originToken);
	if (!originScriptable)
		originScriptable = target;

	Scriptable * targetScriptable = world->GetScriptable(m_targetToken);
	if (!targetScriptable)
		targetScriptable = target;

	const Formula * condition = &m_condition;
	unsigned targetListToken = m_targetListToken;

	return originScriptable->GetScopes().ListRemoveIf(m_originListToken, [world, condition, &scopes, targetScriptable, targetListToken](const Scriptable * member) {
		WorldPropertyBag bag(world, scopes);
		Result cond = condition->Evaluate(&bag);
		if (cond.code != RESULT_CODE_OK)
			return false;

		if (cond.value == 0.0)
			return false;

		targetScriptable->GetScopes().ListAddEntry(targetListToken, *member);
		return true;
	});
}



