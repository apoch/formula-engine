#pragma once


struct IEngineBinding {
	virtual void SetGoalState(unsigned token, double state) = 0;
	virtual void SetGoalState(unsigned token, double statex, double statey) = 0;
};


struct IEngineBinder {
	virtual IEngineBinding * CreateBinding(unsigned token) = 0;
};


