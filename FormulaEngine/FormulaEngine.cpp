// FormulaEngine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Formula.h"
#include "Actions.h"
#include "Parser.h"
#include "PropertyBag.h"
#include "TokenPool.h"
#include "Scriptable.h"
#include "ScriptWorld.h"
#include "DeserializerFactory.h"


int _tmain(int argc, _TCHAR* argv[])
{
	TokenPool pool;
	FormulaParser parser;

	// Simple formula/bag test
	{
		SimplePropertyBag bag;
		bag.Set(pool.AddToken("twenty"), 20.0);

		Formula f = parser.Parse("((1.75 + 2.25) * 6) + twenty - 2", &pool);
		Result res = f.Evaluate(&bag);

		assert(res.value == 42.0);
		std::cout << "Simple: " << res.value << std::endl;
	}

	// Formula bag test
	{
		FormulaPropertyBag fbag;
		fbag.Set(pool.AddToken("alpha"), parser.Parse("32.0 + 5.0", &pool));
		fbag.Set(pool.AddToken("beta"), parser.Parse("alpha + 5.0", &pool));

		std::cout << "Formula: " << fbag.ResolveNumber(fbag, 0, pool.AddToken("beta")).value << std::endl;
	}

	// Scoped bag test
	{
		FormulaPropertyBag eventbag;
		eventbag.Set(pool.AddToken("damageAmount"), parser.Parse("health * 0.1", &pool));

		ScopedPropertyBag scopes;
		scopes.GetScopes().AddScope(pool.AddToken("event"), eventbag);
		scopes.GetProperties().Set(pool.AddToken("health"), 100.0);

		Formula modifiedHealth = parser.Parse("health - event:damageAmount", &pool);

		std::cout << "Scopes: " << modifiedHealth.Evaluate(&scopes).value << std::endl;
	}

	// Action set test
	{
		ActionSet actions;
		actions.AddActionSetProperty(pool.AddToken("health"), parser.Parse("health - event:damageAmount", &pool));

		FormulaPropertyBag eventbag;
		eventbag.Set(pool.AddToken("damageAmount"), parser.Parse("health * 0.1", &pool));

		ScopedPropertyBag statsbag;
		statsbag.GetProperties().Set(pool.AddToken("health"), 100.0);


		actions.Execute(&statsbag, pool.AddToken("event"), &eventbag);


		std::cout << "Actions: " << statsbag.ResolveNumber(statsbag, 0, pool.AddToken("health")).value << std::endl;
	}

	// List/function test
	{
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

			std::cout << "List 1: " << test.GetScopes().ResolveNumber(test.GetScopes(), 0, pool.AddToken("computed")).value << std::endl;
		}

		std::cout << "List 2: " << test.GetScopes().ResolveNumber(test.GetScopes(), 0, pool.AddToken("computed")).value << std::endl;

		Scriptable twobagalso;
		twobagalso.GetScopes().GetProperties().Set(pool.AddToken("value"), 2.0);

		ActionSet actions;
		actions.AddActionListAddEntry(pool.AddToken("testlist"), twobagalso);
		actions.Execute(&test.GetScopes(), 0, nullptr);

		std::cout << "List 3: " << test.GetScopes().ResolveNumber(test.GetScopes(), 0, pool.AddToken("computed")).value << std::endl;
	}

	// Deserialization test
	{
		ScriptWorld world;
		DeserializerFactory factory;

		factory.LoadFileIntoScriptWorld("e:\\test.json", &world);

		unsigned computedToken = world.GetTokenPool().AddToken("computed");
		unsigned testToken = world.GetTokenPool().AddToken("test");

		auto & scopes = world.GetScriptable(testToken)->GetScopes();
		std::cout << "JSON: " << scopes.ResolveNumber(scopes, 0, computedToken).value << std::endl;
	}

	return 0;
}

