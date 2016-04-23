//
// FormulaEngine Project
// By Mike Lewis - 2015
//
// Precompiled header
//
// Commonly used but rarely changed headers can be included
// here for more optimal build times. See your compiler's
// documentation on precompiled headers for details on how
// this works and how to port it around to new compilers.
//

#pragma once

// C++ standard library includes
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cassert>
#include <random>
#include <atomic>
#include <thread>


// Third party library includes
#include "Shared/PicoJSON.h"


// Utility includes
#include "Shared/Utilities.h"
#include "Shared/ValueT.h"


// FormulaEngine dependencies
#include "FormulaEngine/Interfaces.h"
#include "FormulaEngine/Formula.h"
#include "FormulaEngine/Actions.h"
#include "FormulaEngine/Parser.h"
#include "FormulaEngine/TokenPool.h"
#include "FormulaEngine/PropertyBag.h"
#include "FormulaEngine/EventHandler.h"
#include "FormulaEngine/Scriptable.h"
#include "FormulaEngine/ScriptWorld.h"
#include "FormulaEngine/DeserializerFactory.h"
#include "FormulaEngine/EngineBind.h"
