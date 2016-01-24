## FormulaMUD: a game built on FormulaEngine

FormulaMUD is a Multi-User Dungeon system designed as a proof of concept for the FormulaEngine technology. It is currently fairly simplistic, but shows many techniques used in constructing game logic with FormulaEngine, and hopefully offers a reasonable framework for studying the use of FormulaEngine. The ideal goal of FormulaMUD is to demonstrate that nontrivial and interesting games can be built in a flexible, effective, and designer-friendly manner using the principles of FormulaEngine.

There are three primary components to the FormulaMUD project:

 * The game engine, written in C++, which hosts the MUD and handles low-level issues like connecting users and saving world state.
 * The core game data, written in JSON, which describes the world and includes scripts for making the world "go".
 * FormulaEdit, written in C#, which provides a convenient UI for editing the core game data safely and efficiently.
 
The C++ engine is designed to do a minimum amount of work. It hosts FormulaEngine and uses it for the vast majority of the game's logic. For example, "items" have no corresponding C++ implementation at all. Users and Rooms are the primary entities with C++ code involved. This document is intended to cover the design and content creation sides of FormulaMUD, so we'll mostly ignore the engine for now.

Core game data is split into a few parts:

 * `FormulaMUD.json` contains the core game logic and mechanics, and some scripting scaffolding for helping everything along.
 * `Rooms.json` describes the game world and all the rooms, items, monster spawns, and so on scattered throughout.
 * `CommandList.json` is a whitelist of things users may type to affect the game world in some way.
 
Last but very much not least, FormulaEdit is the most friendly and bulletproof way to work on the FormulaMUD world data. It provides a GUI for working on all aspects of the game logic, with one notable exception: it is not designed to handle creation of entirely new game features, which may require manual updates to the JSON files, manual updates to the C# tool itself, and also (in rare cases) some C++ bindings work.

### Getting started

I highly recommend reading through the documentation for FormulaEngine before getting too far into content creation. Understanding how all the pieces work is important for being comfortable with FormulaEdit and the underlying JSON systems.

### Commands

Let's start by considering *commands*, the fundamental mechanism by which a player interacts with FormulaMUD. There are three elements to a command:

 * The "command" itself, such as `north` or `take`
 * The *event* generated in FormulaEngine when a user types the command
 * Some help text that can explain the command if the user types `help foo-command`
 
Eventually commands will be able to have *parameters* which allow the user to be more specific, such as `take doodad` or `kill goblin`. This is not yet hooked up, however; watch this space!

The most important aspect of a command is its *event*. Events are sent to FormulaEngine and can be handled by the User script. We'll see more about how to handle events, as well as the User script itself, later on.

### Rooms

WIP - describe rooms and how their events work

### User Script

WIP - cover the User archetype and how it works

### Items

I'm changing how items work soon so I don't want to document the old setup and then have to rewrite it for the new hotness. Watch this space.

### The Text Bag

WIP - explain the text bag and how to use it from script
