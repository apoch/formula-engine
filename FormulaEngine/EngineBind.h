//
// FormulaEngine Project
// By Mike Lewis - 2016
//
// Interfaces for binding between script and engine layers
//
// This is not the best example of how to bind a scripting language
// to an engine. It is meant solely to demonstrate a minimalist yet
// fully functional "glue layer" between the formula-driven bits of
// the system and the more "engine-like" areas.
//
// A better system would probably use macro markup to automatically
// create bindings instead of relying on pumping everything through
// one interface keyed off of tokens.
//

#pragma once


// Forward declarations
class Scriptable;
class ScriptWorld;


//
// Interface representing one instance of a script object bound
// onto an engine object. There should be one of these per pair
// of objects. It is the engine side's responsibility to derive
// from this interface and provide the actual linkage between a
// script call and the backing engine data.
//
// Note that engine classes need not derive directly from this,
// which allows for better decoupling of engine and script code
// overall, since only a thin "shim" layer needs to be aware of
// both script and engine concerns.
//
struct IEngineBinding {
	virtual ~IEngineBinding () { }

	virtual void SetGoalState (unsigned token, unsigned tokenValue) = 0;
	virtual void SetGoalState (unsigned token, double state) = 0;
	virtual void SetGoalState (unsigned token, double statex, double statey) = 0;

	virtual bool HasPropertyBinding (unsigned token) const = 0;
	virtual unsigned GetPropertyBinding (unsigned token, unsigned * out) const = 0;
	virtual unsigned GetPropertyBinding (unsigned token, double * out1, double * out2) const = 0;
};


//
// Factory interface for generating binding records
//
struct IEngineBinder {
	virtual IEngineBinding * CreateBinding (Scriptable * scriptable, ScriptWorld * world, unsigned token) = 0;
};


