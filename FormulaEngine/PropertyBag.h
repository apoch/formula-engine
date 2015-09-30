#pragma once


struct Result;
class Scriptable;


struct IPropertyBag : public IFormulaContext {
	virtual void Set(unsigned token, double value) = 0;
};


class SimplePropertyBag : public IPropertyBag {
public:			// IPropertyBag interface
	void Set(unsigned token, double value) override;

public:			// IFormulaContext interface
	Result ResolveNumber(const IFormulaContext & context, unsigned scope, unsigned token) const override;
	ListResult ResolveList(const IFormulaContext & context, unsigned scope, unsigned token) const override;

private:		// Internal state
	std::map<unsigned, double> m_bag;
};



class FormulaPropertyBag : public IPropertyBag {
public:			// Configuration interface
	void Set(unsigned token, const Formula & formula);
	void Set(unsigned token, Formula && formula);

public:			// IPropertyBag interface
	void Set(unsigned token, double value) override;

public:			// IFormulaContext interface
	Result ResolveNumber(const IFormulaContext & context, unsigned scope, unsigned token) const override;
	ListResult ResolveList(const IFormulaContext & context, unsigned scope, unsigned token) const override;

public:			// Utility routines
	void Flatten(SimplePropertyBag * bag, const ScopedPropertyBag * scopes) const;

private:		// Internal state
	std::map<unsigned, Formula> m_bag;
};



class ScopeResolver {
public:			// Configuration interface
	void AddScope(unsigned token, const IFormulaContext & context);
	const IFormulaContext * GetScope(unsigned token) const;

	void MoveFixup(const IFormulaContext * oldptr, const IFormulaContext * newptr);

private:		// Internal state
	std::map<unsigned, const IFormulaContext *> m_bag;
};


class ScopedPropertyBag : public IFormulaContext, public IActionPerformer {
public:			// Construction and destruction
	ScopedPropertyBag();
	ScopedPropertyBag(ScopedPropertyBag && other);
	~ScopedPropertyBag();

private:		// Non-copyable
	ScopedPropertyBag(const ScopedPropertyBag & other) = delete;
	ScopedPropertyBag & operator = (const ScopedPropertyBag & other) = delete;

public:			// Configuration interface
	ScopeResolver & GetScopes()						{ return m_resolver; }
	FormulaPropertyBag & GetProperties()			{ return m_thisBag; }

public:			// Archetype support
	void InstantiateFrom(const ScopedPropertyBag & other);
	
public:			// IActionPerformer interface
	void SetProperty(unsigned token, double value) override;
	void SetFormula(unsigned token, const Formula & formula) override;

	void ListAddEntry(unsigned listToken, const Scriptable & entry) override;
	void ListRemoveEntry(unsigned listToken, const Scriptable & entry) override;

	const IFormulaContext & GetProperties() const override		{ return m_thisBag; }

public:			// IFormulaContext interface
	Result ResolveNumber(const IFormulaContext & context, unsigned scope, unsigned token) const override;
	ListResult ResolveList(const IFormulaContext & context, unsigned scope, unsigned token) const override;
	
private:		// Internal state
	std::map<unsigned, std::vector<const Scriptable *>> m_lists;
	FormulaPropertyBag m_thisBag;
	ScopeResolver m_resolver;
};


