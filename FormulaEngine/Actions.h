#pragma once

struct IPropertyBag;
struct IFormulaContext;
class ScopedPropertyBag;
class Formula;
class Scriptable;


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

public:			// Execution interface
	ResultCode Execute(IActionPerformer * targetBag, unsigned contextScope, IPropertyBag * optionalContext) const;

private:		// Internal helper structures
	enum ActionCode {
		ACTION_CODE_SET_PROPERTY,
		ACTION_CODE_SET_FORMULA,
		ACTION_CODE_LIST_ADD,
	};

	struct ActionRecord {
		ActionCode action;
		unsigned   targetToken;
		Formula    payload;
		const Scriptable * entry;
	};

private:		// Internal state
	std::vector<ActionRecord> m_actions;
};

