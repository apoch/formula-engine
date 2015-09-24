#pragma once

struct IPropertyBag;
struct IFormulaContext;
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


class ActionSet {
public:			// Construction and destruction
	ActionSet() { }
	ActionSet(ActionSet && other);
	ActionSet(const ActionSet & other);
	~ActionSet();

	ActionSet & operator= (const ActionSet & other) = delete;

public:			// Setup interface
	void AddActionSetProperty(unsigned targetToken, Formula && payload);
	void AddActionSetFormula(unsigned targetToken, Formula && payload);
	void AddActionSetGoalState(unsigned scopeToken, unsigned targetToken, Formula && payload);

	void AddActionListAddEntry(unsigned listToken, const Scriptable & entry);
	void AddActionListSpawnEntry(unsigned listToken, unsigned archetypeToken, FormulaPropertyBag * bag);

	void AddActionEventRepeat(unsigned eventToken, Formula && counter, FormulaPropertyBag * bag);

public:			// Execution interface
	ResultCode Execute(ScriptWorld * world, Scriptable * target, unsigned contextScope, const IPropertyBag * optionalContext) const;

private:		// Internal helper structures
	enum ActionCode {
		ACTION_CODE_SET_PROPERTY,
		ACTION_CODE_SET_FORMULA,
		ACTION_CODE_SET_GOAL_STATE,
		ACTION_CODE_LIST_ADD,
		ACTION_CODE_LIST_SPAWN,
		ACTION_CODE_EVENT_REPEAT,
	};

	struct ActionRecord {
		ActionCode action;
		unsigned   targetScope;
		unsigned   targetToken;
		unsigned   archetypeToken;

		Formula    payload;
		const Scriptable * entry;

		FormulaPropertyBag * bag = nullptr;
	};

private:		// Internal state
	std::vector<ActionRecord> m_actions;
	std::vector<FormulaPropertyBag *> m_ownedBags;
};

