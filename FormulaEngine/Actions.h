#pragma once

struct IPropertyBag;
struct IFormulaContext;
class ScopedPropertyBag;
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
public:			// Setup interface
	void AddActionSetProperty(unsigned targetToken, Formula && payload);
	void AddActionSetFormula(unsigned targetToken, Formula && payload);

	void AddActionListAddEntry(unsigned listToken, const Scriptable & entry);
	void AddActionListSpawnEntry(unsigned listToken, unsigned archetypeToken);

	void AddActionEventRepeat(unsigned eventToken, Formula && counter);

public:			// Execution interface
	ResultCode Execute(ScriptWorld * world, Scriptable * target, unsigned contextScope, IPropertyBag * optionalContext) const;

private:		// Internal helper structures
	enum ActionCode {
		ACTION_CODE_SET_PROPERTY,
		ACTION_CODE_SET_FORMULA,
		ACTION_CODE_LIST_ADD,
		ACTION_CODE_LIST_SPAWN,
		ACTION_CODE_EVENT_REPEAT,
	};

	struct ActionRecord {
		ActionCode action;
		unsigned   targetToken;
		unsigned   archetypeToken;

		Formula    payload;
		const Scriptable * entry;
	};

private:		// Internal state
	std::vector<ActionRecord> m_actions;
};

