//
// FormulaEngine Project
// By Mike Lewis - 2015
//
// Unit test suite
//
// This module implements various unit tests for elements
// of the FormulaEngine library. Testing is predominantly
// intended to be for catching regressions, so coverage
// is imperfect and most tests are some loose variant of
// integration tests in reality. There's also not really
// any harness to speak of, just basic assertions.
//
// Additional tests may be added over time as the surface
// of the APIs grows and shifts, but mostly for this code
// testing is of limited application, so it doesn't get a
// ton of attention.
//

#include "stdafx.h"

#include "Tests.h"

#include "Formula.h"
#include "Actions.h"
#include "Parser.h"
#include "PropertyBag.h"
#include "TokenPool.h"
#include "EventHandler.h"
#include "Scriptable.h"
#include "ScriptWorld.h"
#include "DeserializerFactory.h"


namespace Tests {


//
// Basic test for the SimpleFormulaBag class
//
// Tests the functionality of Formulas, TokenPools,
// FormulaParsers, and SimplePropertyBags. Combines
// the aforementioned objects to evaluate a simple
// formula-based property.
//
// Asserts that evaluation succeeds and the result
// value is the expected number.
//
static void TestSimpleFormulaBag() {
	TokenPool pool;
	FormulaParser parser;

	SimplePropertyBag bag;
	bag.Set(pool.AddToken("twenty"), 20.0);

	Formula f = parser.Parse("((1.75 + 2.25) * 6) + twenty - 2", &pool);
	Result res = f.Evaluate(&bag);

	assert(res.code == RESULT_CODE_OK);
	assert(res.value == 42.0);
}

//
// Basic test for the FormulaPropertyBag class
//
// Computes dependent, named property values using
// a FormulaPropertyBag. Also incidentally tests
// Formulas, TokenPools, and FormulaParsers.
//
// Asserts that evaluation results in the expected
// number value.
//
static void TestFormulas() {
	TokenPool pool;
	FormulaParser parser;

	FormulaPropertyBag fbag;
	fbag.Set(pool.AddToken("alpha"), parser.Parse("32.0 + 5.0", &pool));
	fbag.Set(pool.AddToken("beta"), parser.Parse("alpha + 5.0", &pool));

	double val = fbag.ResolveNumber(fbag, 0, pool.AddToken("beta")).value;

	assert(val == 42.0);
}

//
// Basic test for the ScopedPropertyBag class
//
// Wraps some named properties in scopes and checks
// that the results are sane.
//
// Asserts that the result of evaluation matches
// the expected numeric value.
//
static void TestScopedBag() {
	TokenPool pool;
	FormulaParser parser;

	FormulaPropertyBag eventbag;
	eventbag.Set(pool.AddToken("damageAmount"), parser.Parse("health * 0.1", &pool));

	ScopedPropertyBag scopes;
	scopes.GetScopes().AddScope(pool.AddToken("event"), eventbag);
	scopes.GetProperties().Set(pool.AddToken("health"), 100.0);

	Formula modifiedHealth = parser.Parse("health - event:damageAmount", &pool);

	double val = modifiedHealth.Evaluate(&scopes).value;

	assert(val == 90.0);
}

//
// Basic test of the ActionSet class
//
// Makes sure that actions can be applied to Scriptables
// correctly and cleanly. Incidentally tests TokenPool,
// FormulaParser, Formula, FormulaPropertyBag, and a bit
// of Scriptable.
//
// Asserts that the result of action execution is the
// expected numeric value.
//
static void TestActionSets() {
	TokenPool pool;
	FormulaParser parser;

	ActionSet actions;
	actions.AddActionSetProperty(pool.AddToken("health"), parser.Parse("health - event:damageAmount", &pool));

	FormulaPropertyBag eventbag;
	eventbag.Set(pool.AddToken("damageAmount"), parser.Parse("health * 0.1", &pool));

	Scriptable scriptable;
	scriptable.GetScopes().GetProperties().Set(pool.AddToken("health"), 100.0);


	actions.Execute(nullptr, &scriptable, pool.AddToken("event"), &eventbag);


	double val = scriptable.GetScopes().ResolveNumber(scriptable.GetScopes(), 0, pool.AddToken("health")).value;
	assert(val == 90.0);
}

static void TestListsAndFunctions() {
	TokenPool pool;
	FormulaParser parser;

	Scriptable test;

	Scriptable tenbag;
	tenbag.GetScopes().GetProperties().Set(pool.AddToken("value"), 10.0);
	test.GetScopes().ListAddEntry(pool.AddToken("testlist"), tenbag);

	Scriptable thirtybag;
	thirtybag.GetScopes().GetProperties().Set(pool.AddToken("value"), 30.0);
	test.GetScopes().ListAddEntry(pool.AddToken("testlist"), thirtybag);

	test.GetScopes().GetProperties().Set(pool.AddToken("computed"), parser.Parse("SumOf(testlist:value)", &pool));

	{
		Scriptable twobag;
		twobag.GetScopes().GetProperties().Set(pool.AddToken("value"), 2.0);
		test.GetScopes().ListAddEntry(pool.AddToken("testlist"), twobag);

		double val1 = test.GetScopes().ResolveNumber(test.GetScopes(), 0, pool.AddToken("computed")).value;
		assert(val1 == 42.0);
	}

	double val2 = test.GetScopes().ResolveNumber(test.GetScopes(), 0, pool.AddToken("computed")).value;
	assert(val2 == 40.0);

	Scriptable twobagalso;
	twobagalso.GetScopes().GetProperties().Set(pool.AddToken("value"), 2.0);

	ActionSet actions;
	actions.AddActionListAddEntry(pool.AddToken("testlist"), twobagalso);
	actions.Execute(nullptr, &test, 0, nullptr);

	double val3 = test.GetScopes().ResolveNumber(test.GetScopes(), 0, pool.AddToken("computed")).value;
	assert(val3 == 42.0);
}

static void TestDeserialization() {
	TokenPool pool;
	FormulaParser parser;

	ScriptWorld world;
	DeserializerFactory factory;

	factory.LoadFileIntoScriptWorld("Data\\test.json", &world);

	unsigned computedToken = world.GetTokenPool().AddToken("computed");
	unsigned testToken = world.GetTokenPool().AddToken("test");

	assert(world.GetScriptable(testToken) != nullptr);

	auto & scopes = world.GetScriptable(testToken)->GetScopes();
	double val = scopes.ResolveNumber(scopes, 0, computedToken).value;

	assert(val == 42.0);
}


void RunAll() {
	TestSimpleFormulaBag();
	TestFormulas();
	TestScopedBag();
	TestActionSets();
	TestListsAndFunctions();
	TestDeserialization();
}


}

