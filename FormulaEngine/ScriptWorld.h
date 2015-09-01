#pragma once


class ScriptWorld {
public:			// Setup interface
	void AddScriptable(const std::string & name, Scriptable && scriptable);
	Scriptable * GetScriptable(unsigned token);

	TokenPool & GetTokenPool()			{ return m_tokens; }

private:		// Internal state
	TokenPool m_tokens;
	std::map<unsigned, Scriptable> m_scriptables;
};


