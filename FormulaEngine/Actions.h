#pragma once

struct IFormulaPropertyBag;
struct IFormulaContext;
class ActionSet;
class ScopedPropertyBag;
class FormulaPropertyBag;
class Formula;
class Scriptable;
class ScriptWorld;


struct IActionPerformer {
	virtual void SetProperty(unsigned targetToken, const Result & value) = 0;
	virtual void SetFormula(unsigned targetToken, const Formula & formula) = 0;

	virtual void ListAddEntry(unsigned listToken, Scriptable * entry) = 0;
	virtual void ListRemoveEntry(unsigned listToken, const Scriptable & entry) = 0;

	virtual const IFormulaContext & GetProperties() const = 0;
};


struct IAction {
	virtual ~IAction() { }
	virtual IAction * Clone() const = 0;
	virtual ResultCode Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const = 0;
};





class ActionSet {
public:			// Construction and destruction
	ActionSet();
	ActionSet(ActionSet && other);
	ActionSet(const ActionSet & other);
	~ActionSet();

	ActionSet & operator= (const ActionSet & other) = delete;

public:			// Setup interface
	void AddAction(IAction * action);

public:			// Execution interface
	ResultCode Execute(ScriptWorld * world, Scriptable * target, unsigned contextScope, const IFormulaPropertyBag * optionalContext) const;
	ResultCode Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const;

private:		// Internal state
	std::vector<IAction *> m_actions;
	ScopedPropertyBag * m_scopeCache;
};



class ActionEventTrigger : public IAction {
public:
	ActionEventTrigger(unsigned eventToken, unsigned targetToken, FormulaPropertyBag * parambagptr, Formula && delayFormula);
	~ActionEventTrigger();

	IAction * Clone() const override;
	ResultCode Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const override;

private:
	unsigned m_eventToken;
	unsigned m_targetToken;
	FormulaPropertyBag * m_paramBag;
	Formula m_delay;
};

class ActionEventRepeat : public IAction {
public:
	ActionEventRepeat(unsigned eventToken, Formula && repeatFormula, FormulaPropertyBag * parambagptr);
	~ActionEventRepeat();

	IAction * Clone() const override;
	ResultCode Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const override;

private:
	unsigned m_eventToken;
	Formula m_repeatFormula;
	FormulaPropertyBag * m_paramBag;
};


class ActionSetProperty : public IAction {
public:
	ActionSetProperty (unsigned targetToken, Formula && payload, unsigned scopeToken);

	IAction * Clone() const override;
	ResultCode Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const override;

private:
	unsigned m_targetToken;
	unsigned m_scopeToken;
	Formula m_payload;
};

class ActionListAddEntry : public IAction {
public:
	ActionListAddEntry(Formula && objectToken, unsigned listToken, unsigned targetToken);

	IAction * Clone() const override;
	ResultCode Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const override;

private:
	Formula  m_objectToken;
	unsigned m_listToken;
	unsigned m_targetToken;
};

class ActionListSpawnEntry : public IAction {
public:
	ActionListSpawnEntry(unsigned listToken, unsigned archetypeToken, FormulaPropertyBag * paramBagPtr);
	~ActionListSpawnEntry();

	IAction * Clone() const override;
	ResultCode Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const override;

private:
	unsigned m_listToken;
	unsigned m_archetypeToken;
	FormulaPropertyBag * m_paramBag;
};

class ActionSetGoalState : public IAction {
public:
	ActionSetGoalState(unsigned scopeToken, unsigned targetToken, Formula && formula);

	IAction * Clone() const override;
	ResultCode Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const override;

private:
	unsigned m_scopeToken;
	unsigned m_targetToken;
	Formula m_formula;
};


class ActionConditionalBlock : public IAction {
public:
	ActionConditionalBlock(Formula && condition, ActionSet && actions, ActionSet && elseActions);

	IAction * Clone() const override;
	ResultCode Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const override;

private:
	Formula m_condition;
	ActionSet m_actions;
	ActionSet m_else;
};


class ActionListForEach : public IAction {
public:
	ActionListForEach(Formula && scriptableToken, unsigned listToken, ActionSet && loopActions);

	IAction * Clone() const override;
	ResultCode Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const override;

private:
	Formula m_scriptableToken;
	unsigned m_listToken;
	ActionSet m_loopActions;
};


class ActionListTransfer : public IAction {
public:
	ActionListTransfer (Formula && condition, Formula && originToken, unsigned originListToken, Formula && targetToken, unsigned targetListToken);

	IAction * Clone () const override;
	ResultCode Execute (ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const override;

private:
	Formula m_condition;
	Formula m_originToken;
	Formula m_targetToken;
  unsigned m_originListToken;
  unsigned m_targetListToken;
};

