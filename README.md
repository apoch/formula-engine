## formula-engine: a scripting approach for games

The Formula Engine is designed to operate around a small yet highly composable set of primitives. These are:

 * Properties, which are defined by Formulas
 * Entities, which can be organized into Lists
 * Events, as well as Actions (which are performed in response to events)

By using these primitives judiciously, it is possible to express quite rich game systems and game logic without needing heavy bindings from engine code to script code. Moreover, the project aims to demonstrate a moderately detailed simulation using these tools to implement a basic but functional MUD (Multi-User Dungeon).

Code is exclusively C++11; data is exclusively JSON. Examples of the input scripts can be found in [`FormulaMUD/Data`](./FormulaMUD/Data/) as well as in the [`Demos/Data` directory](./Demos/Data/). Compiler is assumed to be Visual Studio 2015 or newer; if you'd like to see other compilers supported, I would gladly take a pull request!

<br>

### Properties and Formulas
Properties are simply numeric data, either statically defined or dynamically computed. Static properties are useful for describing data-driven aspects of a design. Dynamic properties are expressed in terms of _formulas_, which are simply arithmetic expressions such as `1 + (health * 4)`. Properties can also refer to text strings.

The implementation of formulas can be found in [`Formula.h`](./FormulaEngine/Formula.h) and [`Formula.cpp`](./FormulaEngine/Formula.cpp) under the [`FormulaEngine` directory](./FormulaEngine/). Formulas are often (but not always!) parsed from text strings, using a class implemented in [`Parser.h`](./FormulaEngine/Parser.h) and [`Parser.cpp`](./FormulaEngine/Parser.cpp).

Groups of properties are implemented as so-called "bags" and the code for them can be found in [`PropertyBag.h`](./FormulaEngine/PropertyBag.h) and [`PropertyBag.cpp`](./FormulaEngine/PropertyBag.cpp).

<br>

### Entities and Lists
Entities are primarily used as groupings of properties, although they are also used as targets of Events. They are organized into Lists as a mechanism of representing ownership or composition. Entities do not carry much behavior of their own; they are mostly there for organizational purposes.

The class `ScopedPropertyBag` implements support for both sets of properties (inside of optional, named _scopes_) and lists (each of which must have a unique name). This class lives in [`PropertyBag.h`](./FormulaEngine/PropertyBag.h) and [`PropertyBag.cpp`](./FormulaEngine/PropertyBag.cpp).

Entities are generally implemented in terms of the class `Scriptable`, which exists in [`Scriptable.h`](./FormulaEngine/Scriptable.h) and [`Scriptable.cpp`](./FormulaEngine/Scriptable.cpp). `Scriptables` combine the storage of properties (via a `ScopedPropertyBag`) as well as responding to _events_ (see below).

List membership is automatically managed. If an entity (specifically a `Scriptable`) is added to a list, it recieves a callback. Similarly, a callback is invoked if the entity is removed from the list. An entity being destructed will automatically remove itself from all lists to which it has been added. Note that the inverse is not true - an entity can be removed from all lists in the game and still exist as a standalone object.

<br>

### Events and Actions
When the game engine detects that something has occurred which might be of interest to a script, it propagates an _event_. In response to these events, entities may fire a sequence of _actions_. Unlike most traditional game scripting models, actions are not a rich set of verbs exposed by the game engine. Instead, actions fall into a relatively small set of highly generic behaviors that modify critical data used by the game engine itself.

Event handling is implemented inside [`EventHandler.h`](./FormulaEngine/EventHandler.h) and [`EventHandler.cpp`](./FormulaEngine/EventHandler.cpp). The specific actions of each _event handler_ are represented by the `ActionSet` class, which predictably can be found in [`Actions.h`](./FormulaEngine/Actions.h) and [`Actions.cpp`](./FormulaEngine/Actions.cpp).

Scripts can also propagate events internally without needing any bindings to the game engine itself.

<br>

### Worlds
Entities are typically managed inside a _world_. Worlds act as the container for all entities as well as a central dispatching mechanism for events. The implementation can be found in [`ScriptWorld.h`](./FormulaEngine/ScriptWorld.h) and [`ScriptWorld.cpp`](./FormulaEngine/ScriptWorld.cpp).

<br>

### Archetypes and Spawning Entities
It is often convenient to define an entity in terms of some kind of template or "class" and instantiate new entities by copying from that template. This is the exact purpose of _archetypes_. An archetype can be defined in the world at any time, and instances of entities mimicking that archetype can be spawned on demand. Spawned entities are required to be placed into a list of some kind. Unless explicity destroyed by a script, spawned entities live until the end of the world that owns them.

<br>

## Additional Resources

Be sure to check out the wiki (link at the top of this page) for fully fleshed-out documentation.

There should be a PLAN.md file in the root directory with relatively up-to-date thoughts and notes on where this whole thing is heading.
