#pragma once


class Scriptable;
class ScriptWorld;


struct IEngineBinding {
	virtual void SetGoalState(unsigned token, unsigned tokenValue) = 0;
	virtual void SetGoalState(unsigned token, double state) = 0;
	virtual void SetGoalState(unsigned token, double statex, double statey) = 0;

	virtual bool HasPropertyBinding(unsigned token) const = 0;
	virtual unsigned GetPropertyBinding(unsigned token, unsigned * out) const = 0;
	virtual unsigned GetPropertyBinding(unsigned token, double * out1, double * out2) const = 0;
};


struct IEngineBinder {
	virtual IEngineBinding * CreateBinding(Scriptable * scriptable, ScriptWorld * world, unsigned token) = 0;
};


