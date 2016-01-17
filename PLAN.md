## formula-engine plans

### Jan. 17, 2016
Thanks to a flash of inspiration, my goals have shifted a bit on the demo side of this project. Instead of building the abstract demos that I had lined up previously, most of which were just meant to exercise specific features of the FormulaEngine code, I've decided to work on a simple MUD engine.

The goal is to design as much of the game as possible using only FormulaEngine scripting, with a minimum of bindings to the C++ side for flexibility. Ideally it should be possible to build radically different MUD games without touching a single line of C++. So far this means I need to flesh out a few aspects of the FormulaEngine implementation but that's a good thing.

So far I have users who can "connect" and play via the text console (no networking code yet, sorry). There are rooms they can wander around in, and items that can be placed in the rooms and gathered by users. I'm making an effort to implement things in the most sensible way, so rooms and users have bindings to C++, but items for example do not; this is mostly expedience and simplicity talking, not necessarily optimal elegance.

The current batch of script actions is sufficient to implement a decent game shell, and I don't anticipate needing a huge number more to make it all work nicely - which is good, because a simple but powerful action set is precisely the ideal behind FormulaEngine.

My favorite part of working on this is that it's very open ended. I can make the MUD as rich or simple as I get time and energy for, and everything is gravy. Plus it goes well beyond the limited purpose of the FormulaEngine demo and really drives home the fact that the concepts of FormulaEngine do scale to real games.

<br>

### Sept. 20, 2015
Starting to rough in support for vectors/coordinates. Not happy with the implied performance overhead but I'll live for now. Eventually I might come back and optimize some of the core support stuff. Bindings are working somewhat and I want to continue forward with building the KingdomWar example.

<br>

### Sept. 8, 2015
Mostly intend to do documentation and cleanup work for a little while. Would like to start circulating the project a bit and gathering early feedback, so it would help if the stuff was readable and properly commented.