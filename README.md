## formula-engine: a scripting approach for games

The Formula Engine is designed to operate around a small yet highly composable set of primitives. These are:

 * Properties, which are defined by Formulas
 * Entities, which can be organized into Lists
 * Events, as well as Actions (which are performed in response to events)

By using these primitives judiciously, it is possible to express quite rich game systems and game logic without needing heavy bindings from engine code to script code. Moreover, the project aims to demonstrate a moderately detailed simulation using these tools alongside a stripped-down grid-based game engine.

Code is exclusively C++11; data is exclusively JSON. Examples of the input scripts can be found in the [`Data` directory](./Data/). Compiler is assumed to be Visual Studio 2013 or newer; if you'd like to see other compilers supported, I would gladly take a pull request!

<br>

### Properties and Formulas
Properties are simply numeric data, either statically defined or dynamically computed. Static properties are useful for describing data-driven aspects of a design. Dynamic properties are expressed in terms of _formulas_, which are simply arithmetic expressions such as `1 + (health * 4)`.

The implementation of formulas can be found in `Formula.h` and `Formula.cpp` under the `FormulaEngine` directory. Formulas are often (but not always!) parsed from text strings, using a class implemented in `Parser.h` and `Parser.cpp`.

Groups of properties are implemented as so-called "bags" and the code for them can be found in `PropertyBag.h` and `PropertyBag.cpp`.

<br>

### Entities and Lists
Entities are primarily used as groupings of properties, although they are also used as targets of Events. They are organized into Lists as a mechanism of representing ownership or composition. Entities do not carry much behavior of their own; they are mostly there for organizational purposes.

The class `ScopedPropertyBag` implements support for both sets of properties (inside of optional, named _scopes_) and lists (each of which must have a unique name). This class lives in `PropertyBag.h` and `PropertyBag.cpp`.

Entities are generally implemented in terms of the class `Scriptable`, which exists in `Scriptable.h` and `Scriptable.cpp`. `Scriptables` combine the storage of properties (via a `ScopedPropertyBag`) as well as responding to _events_ (see below).

List membership is automatically managed. If an entity (specifically a `Scriptable`) is added to a list, it recieves a callback. Similarly, a callback is invoked if the entity is removed from the list. An entity being destructed will automatically remove itself from all lists to which it has been added.

<br>

### Events and Actions
When the game engine detects that something has occurred which might be of interest to a script, it propagates an _event_. In response to these events, entities may fire a sequence of _actions_. Unlike most traditional game scripting models, actions are not a rich set of verbs exposed by the game engine. Instead, actions fall into a relatively small set of highly generic behaviors that modify critical data used by the game engine itself.

Event handling is implemented inside `EventHandler.h` and `EventHandler.cpp`. The specific actions of each _event handler_ are represented by the `ActionSet` class, which predictably can be found in `Actions.h` and `Actions.cpp`.

<br>

### Worlds
Entities are typically managed inside a _world_. Worlds act as the container for all entities as well as a central dispatching mechanism for events. The implementation can be found in `ScriptWorld.h` and `ScriptWorld.cpp`.

<br>

### Archetypes and Spawning Entities
It is often convenient to define an entity in terms of some kind of template or "class" and instantiate new entities by copying from that template. This is the exact purpose of _archetypes_. An archetype can be defined in the world at any time, and instances of entities mimicking that archetype can be spawned on demand. Spawned entities are required to be placed into a list of some kind. Unless explicity destroyed by a script, spawned entities live until the end of the world that owns them.

<br>

## FAQ

 1. **How do I do (x) in this paradigm?**
Please stand by and watch this space. The ideas behind the Formula Engine are still undergoing a lot of refinement, so examples for a wide variety of use cases are still being worked out.

 2. **How do I represent things that happen over time?**
The non-answer is that _you don't_. A more accurate reflection of things would look something like this: events, and the actions that respond to them, are immediate and atemporal. They do not model the notion of time elapsing, and this is on purpose. One of the goals of this project is to build a simulation that _does_ handle complex time-based scripts (such as strategies or plans). The honest answer is that we don't know yet how that will play out.

 3. **Is there more documentation?**
Not yet. This is still a very nascent project and it'll get fleshed out more as time goes on.

 4. **How do I embed this in my own game?**
For now, the basics of what you need are in the `Formula Engine` filter in the Visual Studio solution. Examples of composing and constructing larger systems from those basic ingredients can be found in various places, such as `Tests.cpp`. In general the stuff that lives in `Game Engine` and `Support` filters can be replaced with whatever engine you're working with.

## Future Plans

There should be a PLAN.md file in the root directory with relatively up-to-date thoughts and notes on where this whole thing is heading.