#pragma once


struct Result;
class Scriptable;
class ScopedPropertyBag;


struct IPropertyBag : public IFormulaContext {
	virtual void Set(unsigned token, const Result & value) = 0;

	virtual void PopulateNamedBindings (ScopedPropertyBag *) const { }
};


class SimplePropertyBag : public IPropertyBag {
public:			// IPropertyBag interface
	void Set(unsigned token, const Result & value) override;

public:			// IFormulaContext interface
	Result ResolveNumber(const IFormulaContext & context, unsigned scope, unsigned token) const override;
	ListResult ResolveList(const IFormulaContext & context, unsigned scope, unsigned token) const override;

private:
	void MaintainSorted();

private:		// Internal state
	typedef std::pair<unsigned, double> BagPair;
	std::vector<BagPair> m_bag;
};



class FormulaPropertyBag : public IPropertyBag {
public:			// Configuration interface
	void Clear();

	void Set(unsigned token, const Formula & formula);
	void Set(unsigned token, Formula && formula);

public:			// IPropertyBag interface
	void Set(unsigned token, const Result & value) override;

public:			// IFormulaContext interface
	Result ResolveNumber(const IFormulaContext & context, unsigned scope, unsigned token) const override;
	ListResult ResolveList(const IFormulaContext & context, unsigned scope, unsigned token) const override;

public:			// Utility routines
	void Flatten(SimplePropertyBag * bag, const ScopedPropertyBag * scopes) const;

private:
	void MaintainSorted();

private:		// Internal state
	typedef std::pair<unsigned, Formula> BagPair;
	std::vector<BagPair> m_bag;
};


class BindingPropertyBag : public IFormulaContext {
public:			// Construction
	explicit BindingPropertyBag(const Scriptable * scriptable);

public:			// IFormulaContext interface
	Result ResolveNumber(const IFormulaContext & context, unsigned scope, unsigned token) const override;
	ListResult ResolveList(const IFormulaContext & context, unsigned scope, unsigned token) const override;

private:		// Internal state
	const Scriptable * m_scriptable;
};


class ScopeResolver {
public:			// Configuration interface
	void AddScope(unsigned token, const IFormulaContext & context);
	const IFormulaContext * GetScope(unsigned token) const;

	void Clear();

	template <typename FunctorT>
	void EnumScopes (FunctorT callback) const {
		for (const auto & kvp : m_bag) {
			callback(kvp.second);
		}
	}

private:		// Internal state
	std::map<unsigned, const IFormulaContext *> m_bag;
};


class ScopedPropertyBag : public IPropertyBag, public IActionPerformer {
public:			// Construction and destruction
	ScopedPropertyBag();
	ScopedPropertyBag(ScopedPropertyBag && other);
	~ScopedPropertyBag();

private:		// Non-copyable
	ScopedPropertyBag(const ScopedPropertyBag & other) = delete;
	ScopedPropertyBag & operator = (const ScopedPropertyBag & other) = delete;

public:			// Configuration interface
	void Clear();

	ScopeResolver & GetScopes()						{ return m_resolver; }
	FormulaPropertyBag & GetProperties()			{ return *m_thisBag; }
	BindingPropertyBag * GetBindings() const		{ return m_bindingBag; }

	void SetProperties(FormulaPropertyBag * refbag);
	void SetBindings(const BindingPropertyBag & refBag);

	void SetNamedBinding (unsigned token, Scriptable * binding);
	Scriptable * GetNamedBinding (unsigned token) const;
	void PopulateNamedBindings (ScopedPropertyBag * otherBag) const override;

public:			// Archetype support
	void InstantiateFrom(const ScopedPropertyBag & other);
	
public:			// IActionPerformer interface
	void SetProperty(unsigned token, const Result & value) override;
	void SetFormula(unsigned token, const Formula & formula) override;

	void ListAddEntry(unsigned listToken, const Scriptable & entry) override;
	void ListRemoveEntry(unsigned listToken, const Scriptable & entry) override;

	const IFormulaContext & GetProperties() const override		{ return *m_thisBag; }

public:
	void Set(unsigned token, const Result & value) override;

public:			// ForEach loop support
	template <typename FunctorT>
	ResultCode ListEnumerate (unsigned listToken, const FunctorT & functor) const {
		auto iter = m_lists.find(listToken);
		if (iter == m_lists.end())
			return RESULT_CODE_MISSING_DEFINITION;

		for (auto scriptable : iter->second)
			functor(scriptable);

		return RESULT_CODE_OK;
	}

	template <typename FunctorT>
	ResultCode ListRemoveIf (unsigned listToken, const FunctorT & functor) {
		auto iter = m_lists.find(listToken);
		if (iter == m_lists.end())
			return RESULT_CODE_MISSING_DEFINITION;

		auto killiter = std::remove_if(iter->second.begin(), iter->second.end(), functor);

		// Need to issue "removed from list" notifications to all deleted elements
		for (auto notifyiter = killiter; notifyiter != iter->second.end(); ++notifyiter)
			(*notifyiter)->OnListMembershipRemoved(listToken, this);

		iter->second.erase(killiter, iter->second.end());

		return RESULT_CODE_OK;
	}

public:			// IFormulaContext interface
	Result ResolveNumber(const IFormulaContext & context, unsigned scope, unsigned token) const override;
	ListResult ResolveList(const IFormulaContext & context, unsigned scope, unsigned token) const override;
	bool ResolveToken (unsigned scope, unsigned token, std::string * out) const override;
	
private:		// Internal state
	std::map<unsigned, std::vector<const Scriptable *>> m_lists;
	FormulaPropertyBag * m_thisBag;
	BindingPropertyBag * m_bindingBag;
	FormulaPropertyBag m_builtInBag;
	ScopeResolver m_resolver;

	std::map<unsigned, Scriptable *> m_namedBindings;
};


class WorldPropertyBag : public IFormulaContext {
public:			// Construction
	WorldPropertyBag(ScriptWorld * world, const ScopedPropertyBag & scopes);

public:			// IFormulaContext interface
	Result ResolveNumber(const IFormulaContext & context, unsigned scope, unsigned token) const override;
	ListResult ResolveList(const IFormulaContext & context, unsigned scope, unsigned token) const override;
	bool ResolveToken (unsigned scope, unsigned token, std::string * out) const override;

private:		// Internal state
	ScriptWorld * m_world;
	const ScopedPropertyBag * m_scopes;
};


class TextPropertyBag : public IFormulaContext {
public:			// IFormulaContext interface
	Result ResolveNumber(const IFormulaContext & context, unsigned scope, unsigned token) const override;
	ListResult ResolveList(const IFormulaContext & context, unsigned scope, unsigned token) const override;

public:			// Text configuration and retrieval
	void AddLine(unsigned token, const char * str);
	const char * GetLine(unsigned token) const;

private:		// Internal state
	std::map<unsigned, std::string> m_bag;
};


class TokenPropertyBag : public IPropertyBag {
public:			// IPropertyBag interface
	void Set (unsigned token, const Result & value) override;

public:			// IFormulaContext interface
	Result ResolveNumber (const IFormulaContext & context, unsigned scope, unsigned token) const override;
	ListResult ResolveList (const IFormulaContext & context, unsigned scope, unsigned token) const override;

	bool ResolveToken (unsigned scope, unsigned token, std::string * out) const override;

public:
	unsigned AddToken (const std::string & token);

private:
	TokenPool m_pool;
	std::map<unsigned, Result> m_bag;
};

