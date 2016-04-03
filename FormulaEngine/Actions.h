//
// FormulaEngine Project
// By Mike Lewis - 2016
//
// Declarations for script action classes
//
// Script actions are the fundamental tools for making changes
// to the running state of the simulation world. They are most
// often executed in sequences or "sets" in order to support a
// composable language of sorts.
//
// In general, script actions ought to be generic and reusable
// rather than custom-tailored to a particular simulation need
// or feature. This serves dual purposes. First, it prevents a
// needless proliferation of script actions that are difficult
// to distinguish and easy to misapply. Second, it reduces the
// need for programming maintenance, since a richer simulation
// does not require direct updates to the action vocabulary as
// often.
//

#pragma once


// Forward declarations
struct IFormulaPropertyBag;
struct IFormulaContext;
class ActionSet;
class ScopedPropertyBag;
class FormulaPropertyBag;
class Formula;
class Scriptable;
class ScriptWorld;


//
// Base interface for all actions supported by the engine
//
// This design allows us to store flat arrays of actions in a
// uniform way, and also allows single actions to encompass a
// series of "nested" actions (see ActionSet below). Overall,
// the execution overhead is measurable but not terrible.
//
// In principle any form of interpreter/VM-style architecture
// could work fine in place of this style; the specifics will
// vary based on game implementation anyways and don't really
// matter too much in the abstract.
//
// In short, if you have an execution engine style that might
// be preferable, try it out; this was purely a path of least
// resistance sort of design decision.
//
struct IAction {
	virtual ~IAction () { }
	virtual ResultCode Execute (ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const = 0;
};


//
// Aggregation of multiple actions into a single sequence
//
// Each action in the container is executed in turn, given the
// context, parameters, etc. provided by the caller. Acts as a
// building block for creating complex flow-control logic like
// conditionals and loops.
//
class ActionSet {
public:			// Construction and destruction
	ActionSet ();
	ActionSet (ActionSet && other);
	~ActionSet ();

public:			// Non-copyable
	ActionSet (const ActionSet & other) = delete;
	ActionSet & operator= (const ActionSet & other) = delete;

public:			// Setup interface
	void AddAction (IAction * action);

public:			// Execution interface
	ResultCode Execute (ScriptWorld * world, Scriptable * target, unsigned contextScope, const IFormulaPropertyBag * optionalContext) const;
	ResultCode Execute (ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const;

private:		// Internal state
	std::vector<IAction *> m_actions;
	ScopedPropertyBag * m_scopeCache;		// TODO - revisit this; optimize?
};



class ActionEventTrigger : public IAction {
public:
	ActionEventTrigger(unsigned eventToken, unsigned targetToken, FormulaPropertyBag * parambagptr, Formula && delayFormula);
	~ActionEventTrigger();

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

	ResultCode Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const override;

private:
	unsigned m_eventToken;
	Formula m_repeatFormula;
	FormulaPropertyBag * m_paramBag;
};


class ActionSetProperty : public IAction {
public:
	ActionSetProperty (unsigned targetToken, Formula && payload, unsigned scopeToken);

	ResultCode Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const override;

private:
	unsigned m_targetToken;
	unsigned m_scopeToken;
	Formula m_payload;
};

class ActionListAddEntry : public IAction {
public:
	ActionListAddEntry(Formula && objectToken, unsigned listToken, unsigned targetToken);

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

	ResultCode Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const override;

private:
	unsigned m_listToken;
	unsigned m_archetypeToken;
	FormulaPropertyBag * m_paramBag;
};

class ActionSetGoalState : public IAction {
public:
	ActionSetGoalState(unsigned scopeToken, unsigned targetToken, Formula && formula);

	ResultCode Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const override;

private:
	unsigned m_scopeToken;
	unsigned m_targetToken;
	Formula m_formula;
};


class ActionConditionalBlock : public IAction {
public:
	ActionConditionalBlock(Formula && condition, ActionSet && actions, ActionSet && elseActions);

	ResultCode Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const override;

private:
	Formula m_condition;
	ActionSet m_actions;
	ActionSet m_else;
};


class ActionListForEach : public IAction {
public:
	ActionListForEach(Formula && scriptableToken, unsigned listToken, ActionSet && loopActions);

	ResultCode Execute(ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const override;

private:
	Formula m_scriptableToken;
	unsigned m_listToken;
	ActionSet m_loopActions;
};


class ActionListTransfer : public IAction {
public:
	ActionListTransfer (Formula && condition, Formula && originToken, unsigned originListToken, Formula && targetToken, unsigned targetListToken);

	ResultCode Execute (ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const override;

private:
	Formula m_condition;
	Formula m_originToken;
	Formula m_targetToken;
	unsigned m_originListToken;
	unsigned m_targetListToken;
};


class ActionListRemove : public IAction {
public:
	ActionListRemove (Formula && condition, Formula && originToken, unsigned originListToken);

	ResultCode Execute (ScriptWorld * world, Scriptable * target, const ScopedPropertyBag & scopes) const override;

private:
	Formula m_condition;
	Formula m_originToken;
	unsigned m_originListToken;
};


