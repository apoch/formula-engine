#include "Pch.h"

#include "Interfaces.h"
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
		action->Execute(world, target, scopes);
	}

	return RESULT_CODE_OK;
}

ResultCode ActionSet::Execute(ScriptWorld * world, Scriptable * target, unsigned contextScope, const IFormulaPropertyBag * optionalContext) const {
	m_scopeCache->Clear();
	m_scopeCache->SetProperties(&target->GetScopes().GetProperties());

	BindingPropertyBag bag(target);
	m_scopeCache->SetBindings(bag);

	if (optionalContext) {
		m_scopeCache->GetScopes().AddScope(contextScope, *optionalContext);
		optionalContext->PopulateNamedBindings(m_scopeCache);
	}

	m_scopeCache->SetWorld(world);

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

ResultCode ActionListSpawnEntry::Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const {
	SimplePropertyBag * bagptr = nullptr;
	if(m_paramBag) {
		bagptr = new SimplePropertyBag;
		m_paramBag->Flatten(bagptr, &scopes);
	}

	Scriptable * instance = world->InstantiateArchetype(m_archetypeToken, bagptr);
	if(instance) {
		target->GetScopes().ListAddEntry(m_listToken, instance);
	}

	return RESULT_CODE_OK;
}


ActionSetGoalState::ActionSetGoalState(unsigned scopeToken, unsigned targetToken, Formula && formula)
	: m_scopeToken(scopeToken),
	  m_targetToken(targetToken),
	  m_formula(formula)
{
}

ResultCode ActionSetGoalState::Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const {
	ref(world);

	Result result = m_formula.Evaluate(&scopes);
	if (result.code == RESULT_CODE_OK) {
		IEngineBinding * binding = target->GetBinding(m_scopeToken);
		if (!binding)
			binding = scopes.GetNamedBinding(m_scopeToken)->GetBinding(m_scopeToken);

		if (binding) {
			if(result.type == RESULT_TYPE_SCALAR)
				binding->SetGoalState(m_targetToken, result.payload.num.value);
			else if(result.type == RESULT_TYPE_VECTOR2)
				binding->SetGoalState(m_targetToken, result.payload.num.value, result.payload.num.value2);
			else if(result.type == RESULT_TYPE_TOKEN)
				binding->SetGoalState(m_targetToken, result.payload.txt.token);
		}
	}
	
	return result.code;
}




ActionEventTrigger::ActionEventTrigger(unsigned eventToken, unsigned targetToken, FormulaPropertyBag * parambagptr, Formula && delayFormula)
	: m_eventToken(eventToken),
 	  m_targetToken(targetToken),
 	  m_paramBag(parambagptr),
	  m_delay(std::move(delayFormula))
{
}

ActionEventTrigger::~ActionEventTrigger() {
	delete m_paramBag;
}

ResultCode ActionEventTrigger::Execute(ScriptWorld * world, Scriptable * scriptable, const ScopedPropertyBag & scopes) const {
	SimplePropertyBag * bagptr = nullptr;
	if(m_paramBag) {
		bagptr = new SimplePropertyBag;
		m_paramBag->Flatten(bagptr, &scopes);
	}

	ValueT delaySeconds = 0.0;
	Result delayResult = m_delay.Evaluate(&scopes);
	if (delayResult.code == RESULT_CODE_OK)
		delaySeconds = delayResult.payload.num.value;

	if (m_targetToken) {
		if (delaySeconds > 0.0)
			world->QueueDelayedEvent(m_targetToken, m_eventToken, bagptr, delaySeconds);
		else
			world->QueueEvent(world->GetScriptable(m_targetToken), m_eventToken, bagptr);
	}
	else {
		if (delaySeconds > 0.0)
			world->QueueDelayedEvent(scriptable, m_eventToken, bagptr, delaySeconds);
		else
			world->QueueEvent(scriptable, m_eventToken, bagptr);
	}

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

ResultCode ActionEventRepeat::Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const {
	Result result = m_repeatFormula.Evaluate(&scopes);
	if(result.code != RESULT_CODE_OK)
		return result.code;

	unsigned counter = unsigned(result.payload.num.value);
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


ActionSetProperty::ActionSetProperty (unsigned targetToken, Formula && payload, unsigned scopeToken)
	: m_targetToken(targetToken),
      m_scopeToken(scopeToken),
	  m_payload(payload)
{
}

ResultCode ActionSetProperty::Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const {
	ref(world);

	Result result = m_payload.Evaluate(&scopes);
	if(result.code == RESULT_CODE_OK) {
		if (m_scopeToken) {
			scopes.GetNamedBinding(m_scopeToken)->GetScopes().Set(m_targetToken, result);
		}
		else {
			target->GetScopes().Set(m_targetToken, result);
		}
	}

	return result.code;
}


ActionListAddEntry::ActionListAddEntry (Formula && objectToken, unsigned listToken, unsigned targetToken)
	: m_listToken(listToken),
	  m_targetToken(targetToken),
	  m_objectToken(objectToken)
{
}

ResultCode ActionListAddEntry::Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const {

	// TODO - respect m_objectToken
	Scriptable * newMember = world->GetScriptable(m_targetToken);
	if (!newMember)
		newMember = scopes.GetNamedBinding(m_targetToken);

	target->GetScopes().ListAddEntry(m_listToken, newMember);

	return RESULT_CODE_OK;
}



ActionConditionalBlock::ActionConditionalBlock(Formula && condition, ActionSet && actions, ActionSet && elseActions)
	: m_actions(std::move(actions)),
	  m_else(std::move(elseActions))
{
	std::swap(m_condition, condition);
}

ResultCode ActionConditionalBlock::Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const {
	Result cond = m_condition.Evaluate(&scopes);
	if(cond.code != RESULT_CODE_OK)
		return cond.code;

	if(cond.payload.num.value == 0.0)
		return m_else.Execute(world, target, scopes);

	return m_actions.Execute(world, target, scopes);
}


ActionListForEach::ActionListForEach(Formula && scriptableToken, unsigned listToken, ActionSet && loopActions)
	: m_scriptableToken(scriptableToken),
	  m_listToken(listToken),
	  m_loopActions(std::move(loopActions))
{
}

ResultCode ActionListForEach::Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const {
	unsigned token = 0;
	Result originRes = m_scriptableToken.Evaluate(&scopes);
	if (originRes.code == RESULT_CODE_OK)
		token = originRes.payload.txt.token;

	Scriptable * scriptable = world->GetScriptable(token);
	if (!scriptable)
		scriptable = target;

	const ActionSet * myActions = &m_loopActions;

	return scriptable->GetScopes().ListEnumerate(m_listToken, [world, target, &scopes, myActions](Scriptable * member) {
		unsigned otherscope = world->GetMagicTokenForOther();

		ScopedPropertyBag newScopes(world);
		newScopes.InstantiateFrom(scopes);
		newScopes.GetScopes().AddScope(otherscope, member->GetScopes());
		newScopes.SetProperties(&target->GetScopes().GetProperties());
		newScopes.SetNamedBinding(otherscope, member);
		if(target->GetScopes().GetBindings())
			newScopes.SetBindings(*target->GetScopes().GetBindings());

		myActions->Execute(world, target, newScopes);
	});
}


ActionListTransfer::ActionListTransfer (Formula && condition, Formula && originToken, unsigned originListToken, Formula && targetToken, unsigned targetListToken)
	: m_condition(std::move(condition)),
	  m_originToken(originToken),
	  m_originListToken(originListToken),
	  m_targetToken(std::move(targetToken)),
	  m_targetListToken(targetListToken)
{
}

ResultCode ActionListTransfer::Execute (ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const {
	unsigned token = 0;
	Result originRes = m_originToken.Evaluate(&scopes);
	if (originRes.code == RESULT_CODE_OK)
		token = originRes.payload.txt.token;

	Scriptable * originScriptable = world->GetScriptable(token);
	if (!originScriptable)
		originScriptable = target;

  unsigned targetToken = 0;
  Result targetRes = m_targetToken.Evaluate(&scopes);
  if (targetRes.code == RESULT_CODE_OK)
    targetToken = targetRes.payload.txt.token;

	Scriptable * targetScriptable = world->GetScriptable(targetToken);
	if (!targetScriptable)
		targetScriptable = target;

	const Formula * condition = &m_condition;
	unsigned targetListToken = m_targetListToken;

	return originScriptable->GetScopes().ListRemoveIf(m_originListToken, [world, condition, &scopes, targetScriptable, targetListToken](Scriptable * member) {
		unsigned otherscope = world->GetMagicTokenForOther();

		ScopedPropertyBag newScopes(world);
		newScopes.InstantiateFrom(scopes);
		newScopes.GetScopes().AddScope(otherscope, member->GetScopes());
		newScopes.SetProperties(&targetScriptable->GetScopes().GetProperties());
		newScopes.SetNamedBinding(otherscope, member);
		if(targetScriptable->GetScopes().GetBindings())
			newScopes.SetBindings(*targetScriptable->GetScopes().GetBindings());

		Result cond = condition->Evaluate(&newScopes);
		if (cond.code != RESULT_CODE_OK)
			return false;

		if (cond.payload.num.value == 0.0)
			return false;

		targetScriptable->GetScopes().ListAddEntry(targetListToken, member);
		return true;
	});
}



ActionListRemove::ActionListRemove (Formula && condition, Formula && originToken, unsigned originListToken)
	: m_condition(std::move(condition)),
	  m_originToken(originToken),
	  m_originListToken(originListToken)
{
}

ResultCode ActionListRemove::Execute (ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const {
	unsigned token = 0;
	Result originRes = m_originToken.Evaluate(&scopes);
	if (originRes.code == RESULT_CODE_OK)
		token = originRes.payload.txt.token;

	Scriptable * originScriptable = world->GetScriptable(token);
	if (!originScriptable)
		originScriptable = target;

	const Formula * condition = &m_condition;

	return originScriptable->GetScopes().ListRemoveIf(m_originListToken, [world, condition, &scopes](Scriptable * member) {
		unsigned otherscope = world->GetMagicTokenForOther();

		ScopedPropertyBag newScopes(world);
		newScopes.InstantiateFrom(scopes);
		newScopes.GetScopes().AddScope(otherscope, member->GetScopes());
		newScopes.SetNamedBinding(otherscope, member);

		Result cond = condition->Evaluate(&newScopes);
		if (cond.code != RESULT_CODE_OK)
			return false;

		if (cond.payload.num.value == 0.0)
			return false;

		return true;
	});
}



