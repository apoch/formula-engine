#pragma once

struct IPropertyBag;
struct IFormulaContext;
class ActionSet;
class ScopedPropertyBag;
class FormulaPropertyBag;
class Formula;
class Scriptable;
class ScriptWorld;


struct IActionPerformer {
	virtual void SetProperty(unsigned targetToken, double value) = 0;
	virtual void SetFormula(unsigned targetToken, const Formula & formula) = 0;

	virtual void ListAddEntry(unsigned listToken, const Scriptable & entry) = 0;
	virtual void ListRemoveEntry(unsigned listToken, const Scriptable & entry) = 0;

	virtual const IFormulaContext & GetProperties() const = 0;
};


struct IAction {
	virtual ~IAction() { }
	virtual IAction * Clone() const = 0;
	virtual ResultCode Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const = 0;
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
	ActionSetProperty(unsigned targetToken, Formula && payload);
	IAction * Clone() const override;
	ResultCode Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const override;

private:
	unsigned m_targetToken;
	Formula m_payload;
};

class ActionSetFormula : public IAction {
public:
	ActionSetFormula(unsigned targetToken, Formula && payload);
	IAction * Clone() const override;
	ResultCode Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const override;

private:
	unsigned m_targetToken;
	Formula m_payload;
};

class ActionListAddEntry : public IAction {
public:
	ActionListAddEntry(unsigned listToken, const Scriptable & scriptable);

	IAction * Clone() const override;
	ResultCode Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const override;

private:
	unsigned m_listToken;
	const Scriptable * m_scriptable;
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



class ActionSet {
public:			// Construction and destruction
	ActionSet() { }
	ActionSet(ActionSet && other);
	ActionSet(const ActionSet & other);
	~ActionSet();

	ActionSet & operator= (const ActionSet & other) = delete;

public:			// Setup interface
	void AddAction(IAction * action);

public:			// Execution interface
	ResultCode Execute(ScriptWorld * world, Scriptable * target, unsigned contextScope, const IPropertyBag * optionalContext) const;
	ResultCode Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const;

private:		// Internal state
	std::vector<IAction *> m_actions;
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

