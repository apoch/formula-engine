#pragma once


class Scriptable;
class ScriptWorld;


struct IEngineBinding {
	virtual void SetGoalState(unsigned token, double state) = 0;
	virtual void SetGoalState(unsigned token, double statex, double statey) = 0;
};


struct IEngineBinder {
	virtual IEngineBinding * CreateBinding(Scriptable * scriptable, ScriptWorld * world, unsigned token) = 0;
};


