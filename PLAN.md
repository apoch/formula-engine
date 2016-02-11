## formula-engine plans

### Feb. 10, 2016
FormulaEdit has undergone a substantial polish and usability pass. There's still plenty of stuff to do, including populating fields with hints when possible, but the basics are looking fairly solid.

Documentation is going to be the next major chunk of effort for a while.

<br>


### Jan. 31, 2016
FormulaEngine is officially going to be presented at GDC 2016... which is both exciting and daunting as it means I have a lot of preparation to do! Fortunately I can safely say that the code that is in FormulaMUD is a good representation of what I want to show off, and I'm treating everything else as a luxury.

"Everything else" principally means FormulaEdit right now. I want to show that it's not hard to build a really snazzy UI that can make the creation of FormulaEngine content a lot less annoying. Mucking around in JSON files is not fun for anyone - well, except for Pat. Having a solid UI on top of the data makes creating FormulaMUD content a lot more fun, even in the nascent state that it's in right now.

<br>


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
