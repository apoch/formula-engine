#pragma once



// Forward declarations
class Scriptable;



struct IListContainer {
	virtual void ListAddEntry (unsigned listToken, Scriptable * entry) = 0;
	virtual void ListRemoveEntry (unsigned listToken, const Scriptable & entry) = 0;
};



