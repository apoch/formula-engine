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

#include "Pch.h"

#include "Tests.h"

#include "FormulaEngine/Formula.h"
#include "FormulaEngine/Actions.h"
#include "FormulaEngine/Parser.h"
#include "FormulaEngine/PropertyBag.h"
#include "FormulaEngine/TokenPool.h"
#include "FormulaEngine/EventHandler.h"
#include "FormulaEngine/Scriptable.h"
#include "FormulaEngine/ScriptWorld.h"
#include "FormulaEngine/DeserializerFactory.h"



namespace {

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
void TestSimpleFormulaBag () {
	TokenPool pool;
	FormulaParser parser;

	Result hr;
	hr.value = 20.0;

	SimplePropertyBag bag;
	bag.Set(pool.AddToken("twenty"), hr);

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
void TestFormulas () {
	TokenPool pool;
	FormulaParser parser;

	FormulaPropertyBag fbag;
	fbag.Set(pool.AddToken("alpha"), parser.Parse("32.0 + 5.0", &pool));
	fbag.Set(pool.AddToken("beta"), parser.Parse("alpha + 5.0", &pool));

	double val = fbag.ResolveNumber(fbag, 0, pool.AddToken("beta")).value;

	assert(val == 42.0);
	((void)(val));
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
void TestScopedBag () {
	TokenPool pool;
	FormulaParser parser;

	FormulaPropertyBag eventbag;
	eventbag.Set(pool.AddToken("damageAmount"), parser.Parse("health * 0.1", &pool));

	ScopedPropertyBag scopes;
	scopes.GetScopes().AddScope(pool.AddToken("event"), eventbag);

	Result hr;
	hr.value = 100.0;

	scopes.GetProperties().Set(pool.AddToken("health"), hr);

	Formula modifiedHealth = parser.Parse("health - event:damageAmount", &pool);

	double val = modifiedHealth.Evaluate(&scopes).value;

	assert(val == 90.0);
	((void)(val));
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
void TestActionSets () {
	TokenPool pool;
	FormulaParser parser;

	ActionSet actions;
	actions.AddAction(new ActionSetProperty(pool.AddToken("health"), parser.Parse("health - event:damageAmount", &pool)));

	FormulaPropertyBag eventbag;
	eventbag.Set(pool.AddToken("damageAmount"), parser.Parse("health * 0.1", &pool));

	Result hr;
	hr.value = 100.0;

	Scriptable scriptable;
	scriptable.GetScopes().GetProperties().Set(pool.AddToken("health"), hr);


	actions.Execute(nullptr, &scriptable, pool.AddToken("event"), &eventbag);


	double val = scriptable.GetScopes().ResolveNumber(scriptable.GetScopes(), 0, pool.AddToken("health")).value;
	assert(val == 90.0);
	((void)(val));
}

//
// Basic test of entity lists, and functions that operate on them
//
// Makes sure that fuctions are evaluated correctly when fed
// entity lists, and that lists update as expected when member
// objects are destructed.
//
// Asserts that list-based computations yield expected values.
//
void TestListsAndFunctions () {
	TokenPool pool;
	FormulaParser parser;

	Scriptable test;

	Result hr;
	hr.value = 10.0;

	Scriptable tenbag;
	tenbag.GetScopes().GetProperties().Set(pool.AddToken("value"), hr);
	test.GetScopes().ListAddEntry(pool.AddToken("testlist"), tenbag);


	hr.value = 30.0;

	Scriptable thirtybag;
	thirtybag.GetScopes().GetProperties().Set(pool.AddToken("value"), hr);
	test.GetScopes().ListAddEntry(pool.AddToken("testlist"), thirtybag);

	test.GetScopes().GetProperties().Set(pool.AddToken("computed"), parser.Parse("SumOf(testlist:value)", &pool));

	{
		hr.value = 2.0;

		Scriptable twobag;
		twobag.GetScopes().GetProperties().Set(pool.AddToken("value"), hr);
		test.GetScopes().ListAddEntry(pool.AddToken("testlist"), twobag);

		double val1 = test.GetScopes().ResolveNumber(test.GetScopes(), 0, pool.AddToken("computed")).value;
		assert(val1 == 42.0);
		((void)(val1));
	}

	double val2 = test.GetScopes().ResolveNumber(test.GetScopes(), 0, pool.AddToken("computed")).value;
	assert(val2 == 40.0);
	((void)(val2));

	Scriptable twobagalso;
	twobagalso.GetScopes().GetProperties().Set(pool.AddToken("value"), hr);

	// TODO - unbreak this test
	/*
	ActionSet actions;
	actions.AddAction(new ActionListAddEntry(pool.AddToken("testlist"), twobagalso));
	actions.Execute(nullptr, &test, 0, nullptr);

	double val3 = test.GetScopes().ResolveNumber(test.GetScopes(), 0, pool.AddToken("computed")).value;
	assert(val3 == 42.0);
	((void)(val3));
	*/
}

//
// Basic test of deserialization mechanisms
//
// Loads a test JSON file from disk and tests that the
// world it contains evaluates formulas as expected.
//
// Asserts that the deserialzed world contains a
// particular expected entity, and that computed
// properties of that entity have expected values.
//
void TestDeserialization () {
	TokenPool pool;
	FormulaParser parser;

	ScriptWorld world(&pool, nullptr);
	DeserializerFactory::LoadFileIntoScriptWorld("Data\\test.json", &world);

	unsigned computedToken = world.GetTokenPool().AddToken("computed");
	unsigned testToken = world.GetTokenPool().AddToken("test");

	assert(world.GetScriptable(testToken) != nullptr);

	auto & scopes = world.GetScriptable(testToken)->GetScopes();
	double val = scopes.ResolveNumber(scopes, 0, computedToken).value;

	assert(val == 42.0);
	((void)(val));
}

//
// Basic test of vector functions
//
// Evaluates simple formulas containing vector operations
// and ensures that they return correct results.
//
// Asserts that the results from vector operations are
// expected values and success codes.
//
void TestVectors () {
	FormulaParser parser;

	Formula formula = parser.Parse("Vec(2, 8)", nullptr);
	Result res = formula.Evaluate(nullptr);
	assert(res.code == RESULT_CODE_OK);
	assert(res.type == RESULT_TYPE_VECTOR2);
	assert(res.value == 2.0);
	assert(res.value2 == 8.0);


	Formula summation = parser.Parse("Vec(1, 7) + Vec(1, 1)", nullptr);
	Result sum = summation.Evaluate(nullptr);
	assert(sum.code == RESULT_CODE_OK);
	assert(sum.type == RESULT_TYPE_VECTOR2);
	assert(sum.value == 2.0);
	assert(sum.value2 == 8.0);
}



} // Anonymous internal namespace



namespace Tests {


//
// Externally visible API for invoking the complete test suite
//
void RunAll() {
	TestSimpleFormulaBag();
	TestFormulas();
	TestScopedBag();
	TestActionSets();
	TestListsAndFunctions();
	TestDeserialization();
	TestVectors();
}


} // Tests namespace


