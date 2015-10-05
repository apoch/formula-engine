#include "Pch.h"

#include "Formula.h"
#include "Actions.h"
#include "PropertyBag.h"
#include "EventHandler.h"
#include "Scriptable.h"


void SimplePropertyBag::MaintainSorted() {
	std::sort(std::begin(m_bag), std::end(m_bag), [](const BagPair & l, const BagPair & r) {
		return l.first < r.first;
	});
}

void SimplePropertyBag::Set(unsigned token, double value) {
	auto iter = std::remove_if(std::begin(m_bag), std::end(m_bag), [token](const std::pair<unsigned, double> & item) {
		return item.first == token;
	});
	m_bag.erase(iter, m_bag.end());

	m_bag.emplace_back(std::make_pair(token, value));
	MaintainSorted();
}

Result SimplePropertyBag::ResolveNumber(const IFormulaContext & context, unsigned scope, unsigned token) const {
	Result ret;
	ret.code = RESULT_CODE_MISSING_DEFINITION;
	ret.value = 0.0;

	if(scope != 0) {
		if(&context != this)
			return context.ResolveNumber(context, scope, token);

		return ret;
	}

	auto iter = std::lower_bound(std::begin(m_bag), std::end(m_bag), token, [](const BagPair & l, unsigned token) {
		return l.first < token;
	});
	if(iter != m_bag.end() && iter->first == token) {
		ret.code = RESULT_CODE_OK;
		ret.value = iter->second;
	}

	return ret;
}

ListResult SimplePropertyBag::ResolveList(const IFormulaContext & context, unsigned scope, unsigned token) const {
	((void)(context));
	((void)(scope));
	((void)(token));

	ListResult ret;
	ret.code = RESULT_CODE_MISSING_DEFINITION;
	return ret;
}



void FormulaPropertyBag::Clear() {
	m_bag.clear();
}

void FormulaPropertyBag::Flatten(SimplePropertyBag * bag, const ScopedPropertyBag * scopes) const {
	for(auto & pair : m_bag) {
		Result result = pair.second.Evaluate(scopes);
		if(result.code != RESULT_CODE_OK)
			std::cout << "FAIL\n";

		bag->Set(pair.first, result.value);
	}
}

void FormulaPropertyBag::MaintainSorted() {
	std::sort(std::begin(m_bag), std::end(m_bag), [](const BagPair & l, const BagPair & r) {
		return l.first < r.first;
	});
}

void FormulaPropertyBag::Set(unsigned token, Formula && formula) {
	auto iter = std::remove_if(std::begin(m_bag), std::end(m_bag), [token](const std::pair<unsigned, Formula> & item) {
		return item.first == token;
	});
	m_bag.erase(iter, m_bag.end());

	m_bag.emplace_back(std::make_pair(token, formula));
	MaintainSorted();
}

void FormulaPropertyBag::Set(unsigned token, const Formula & formula) {
	auto iter = std::remove_if(std::begin(m_bag), std::end(m_bag), [token](const std::pair<unsigned, Formula> & item) {
		return item.first == token;
	});
	m_bag.erase(iter, m_bag.end());

	m_bag.emplace_back(std::make_pair(token, formula));
	MaintainSorted();
}

Result FormulaPropertyBag::ResolveNumber(const IFormulaContext & context, unsigned scope, unsigned token) const {
	if(scope == 0) {
		auto iter = std::lower_bound(std::begin(m_bag), std::end(m_bag), token, [](const BagPair & l, unsigned token) {
			return l.first < token;
		});

		if(iter != m_bag.end() && iter->first == token)
			return iter->second.Evaluate(&context);
	}

	Result ret;
	ret.code = RESULT_CODE_MISSING_DEFINITION;
	ret.value = 0.0;
	return ret;
}

ListResult FormulaPropertyBag::ResolveList(const IFormulaContext & context, unsigned scope, unsigned token) const {
	((void)(context));
	((void)(scope));
	((void)(token));

	ListResult ret;
	ret.code = RESULT_CODE_MISSING_DEFINITION;
	return ret;
}


void FormulaPropertyBag::Set(unsigned token, double value) {
	Formula f;
	f.Push(value);
	Set(token, std::move(f));
}



void ScopeResolver::AddScope(unsigned token, const IFormulaContext & context) {
	m_bag[token] = &context;
}

const IFormulaContext * ScopeResolver::GetScope(unsigned token) const {
	auto iter = m_bag.find(token);
	if(iter == m_bag.end())
		return nullptr;

	return iter->second;
}

void ScopeResolver::Clear() {
	m_bag.clear();
}



ScopedPropertyBag::ScopedPropertyBag() {
	m_thisBag = &m_builtInBag;
}

ScopedPropertyBag::ScopedPropertyBag(ScopedPropertyBag && other) {
	std::swap(m_lists, other.m_lists);
	std::swap(m_builtInBag, other.m_builtInBag);
	std::swap(m_resolver, other.m_resolver);
	
	m_thisBag = &m_builtInBag;
	if(other.m_thisBag != &other.m_builtInBag)
		m_thisBag = other.m_thisBag;
}

ScopedPropertyBag::~ScopedPropertyBag() {
	for(auto & pair : m_lists) {
		for(auto & member : pair.second) {
			member->OnListMembershipRemoved(pair.first, this);
		}
	}
}


void ScopedPropertyBag::Clear() {
	m_lists.clear();
	m_builtInBag.Clear();
	m_resolver.Clear();

	m_thisBag = &m_builtInBag;
}

void ScopedPropertyBag::InstantiateFrom(const ScopedPropertyBag & other) {
	m_resolver = other.m_resolver;
	m_builtInBag = other.m_builtInBag;
	m_thisBag = (other.m_thisBag == &other.m_builtInBag ? &m_builtInBag : other.m_thisBag);
}


void ScopedPropertyBag::ListAddEntry(unsigned listToken, const Scriptable & entry) {
	m_lists[listToken].push_back(&entry);
	entry.OnListMembershipAdded(listToken, this);
}

void ScopedPropertyBag::ListRemoveEntry(unsigned listToken, const Scriptable & entry) {
	auto iter = m_lists.find(listToken);
	if(iter == m_lists.end())
		return;

	auto memberiter = std::find(std::begin(iter->second), std::end(iter->second), &entry);
	if(memberiter == std::end(iter->second))
		return;

	iter->second.erase(memberiter);
}

Result ScopedPropertyBag::ResolveNumber(const IFormulaContext & originalContext, unsigned scope, unsigned token) const {
	auto resolved = scope ? m_resolver.GetScope(scope) : m_thisBag;
	if(resolved == nullptr) {
		Result ret;
		ret.code = RESULT_CODE_MISSING_DEFINITION;
		ret.value = 0.0;
		return ret;
	}

	return resolved->ResolveNumber(originalContext, 0, token);
}

ListResult ScopedPropertyBag::ResolveList(const IFormulaContext & context, unsigned scope, unsigned token) const {
	ListResult ret;

	auto iter = m_lists.find(scope);
	if(iter != m_lists.end()) {
		ret.code = RESULT_CODE_OK;

		if(!iter->second.empty()) {
			ret.values.reserve(iter->second.size());

			for(const auto & scriptable : iter->second) {
				Result result = scriptable->GetScopes().ResolveNumber(context, 0, token);
				if(result.code != RESULT_CODE_OK) {
					ret.code = result.code;
					ret.values.clear();
					break;
				}

				ret.values.push_back(result.value);
			}
		}

		return ret;
	}

	ret.code = RESULT_CODE_MISSING_DEFINITION;
	return ret;
}

void ScopedPropertyBag::SetFormula(unsigned token, const Formula & formula) {
	m_thisBag->Set(token, formula);
}

void ScopedPropertyBag::SetProperty(unsigned token, double value) {
	m_thisBag->Set(token, value);
}

void ScopedPropertyBag::SetProperties(FormulaPropertyBag * refbag) {
	m_thisBag = refbag;
}


