//
// FormulaEngine Project
// By Mike Lewis - 2016
//
// Deserialization infrastructure
//
// Provides a compact interface for loading script data
// from disk into a running ScriptWorld instance. There
// are also some utility methods for loading subsets of
// a full script file, though these methods technically
// leak abstraction details.
//

#pragma once


// Forward declarations
class FormulaParser;
class Scriptable;
class ScriptWorld;


namespace picojson {

class value;
typedef std::vector<value> array;

}


//
// Deserialization API
//
namespace DeserializerFactory {

// Primary function for deserializing script data
void LoadFileIntoScriptWorld (const char filename[], ScriptWorld * world);

// Helpers for deserializing script subsets
void LoadArrayOfEvents (const picojson::value & eventarray, ScriptWorld * world, FormulaParser * parser, Scriptable * scriptable);
void LoadArrayOfLists (const picojson::array & listarray, ScriptWorld * world, Scriptable * instance);

}

