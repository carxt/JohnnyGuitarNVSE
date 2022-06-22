#pragma once

union GenericFilters {
	void* ptr;
	TESForm* form;
	UInt32        refID;
	int            intVal;
	float        fltVal;
	char* str;
	GenericFilters() {
		this->ptr = NULL;
	}
	GenericFilters(void* ptr) {
		this->ptr = ptr;
	}
	GenericFilters(TESForm* form) {
		this->form = form;
	}
	GenericFilters(UInt32 refID) {
		this->refID = refID;
	}
	GenericFilters(int intVal) {
		this->intVal = intVal;
	}
	GenericFilters(float fltVal) {
		this->fltVal = fltVal;
	}
	GenericFilters(char* str) {
		this->str = str;
	}
};

class EventHandlerInterface {
public:
	//Framework passes the objects to add to filter here
	GenericFilters* GenFilters = 0;
	//Used to know how many filters in total (aka the size of the GenericFilters array) the filter uses
	UInt32 numFilters = 0;
	//Default destructor
	virtual ~EventHandlerInterface() {};
	//When the framework passes filters, it passes them to the GenFilters array pointer, specifying the number of filters in the numFilters member
	//This function is called by the framework so you can add the objects inside a struct more suitable for search, such as an unordered set
	virtual void SetUpFiltering() = 0;

	//Checks if an object is in the filter, recommended to use a fast lookup data structure
	virtual bool IsInFilter(UInt32 filterNum, GenericFilters toSearch) = 0;
	//Inserts the desired element to the Nth filter.
	virtual void InsertToFilter(UInt32 filterNum, GenericFilters toInsert) = 0;
	//Deletes an object from the Nth filter
	virtual void DeleteFromFilter(UInt32 filterNum, GenericFilters toDelete) = 0;
	//Returns if the filter is empty
	virtual bool IsFilterEmpty(UInt32 filterNum) = 0;
	//Used by the framework to check if the Nth filter equals the passed value. Useful to avoid adding the same event repeatedly
	virtual bool IsFilterEqual(GenericFilters Filter, UInt32 filterNum) = 0;
	//Function used by the filter to check if the object passed is an accepted parameter
	virtual bool IsAcceptedParameter(GenericFilters toCheck) = 0;
	virtual UInt32 GetNumFilters() { return numFilters; }
};

class EventContainerInterface {
public:
	void virtual RegisterEvent(Script* script, void** filters);
	void virtual RemoveEvent(Script* script, void** filters);
};

EventContainerInterface* (_cdecl* CreateScriptEvent)(const char* EventName, UInt8 maxArgs, UInt8 maxFilters, void* (__fastcall* CustomConstructor)(void**, UInt32));
void(__cdecl* FreeScriptEvent)(EventContainerInterface*& toRemove);

class BaseEventClass {
public:
	ULONG_PTR Flags = 0;
	Script* ScriptForEvent = NULL;
	EventHandlerInterface* eventFilter = NULL;
	LambdaVariableContext capturedLambdaVars;

	BaseEventClass() : capturedLambdaVars(nullptr) {}

	enum GlobalEventFlags {
		kEventFlag_Deleted = 1 << 0,
	};

	bool GetDeleted() {
		return Flags & kEventFlag_Deleted;
	}
	void SetDeleted(bool doSet) {
		doSet ? Flags |= kEventFlag_Deleted : Flags &= ~kEventFlag_Deleted;
	}
};
