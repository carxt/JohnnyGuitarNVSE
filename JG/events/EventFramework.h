#pragma once
#include <unordered_set>
#include <vector>
#include <shared_mutex>
#include <mutex>
#include <algorithm>
#include "nvse/nvse/PluginAPI.h"
#include "LambdaVariableContext.h"

extern bool (*CallUDF)(class Script* funcScript, class TESObjectREFR* callingObj, uint8_t numArgs, ...);

class EventInformation;
extern void* __fastcall GenericCreateFilter(void** maxFilters, uint32_t numFilters);

union FilterType
{
	void* ptr;
	TESForm* form;
	uint32_t refID;
	int intVal;
	float fltVal;
	char* str;

	FilterType() : ptr(nullptr) {}

	FilterType(void* ptr) : ptr(ptr) {}

	FilterType(TESForm* form) : form(form) {}

	FilterType(uint32_t refID) : refID(refID) {}

	FilterType(int intVal) : intVal(intVal) {}

	FilterType(float fltVal) : fltVal(fltVal) {}

	FilterType(char* str) : str(str) {}
};

class IFilter
{
public:
	//Framework passes the objects to add to filter here
	FilterType* genFilters = 0;
	//Used to know how many filterSet in total (aka the size of the FilterType array) the filter uses
	uint32_t numFilters = 0;
	//Default destructor
	virtual ~IFilter() = default;
	//When the framework passes filterSet, it passes them to the genFilters array pointer, specifying the number of filterSet in the numFilters member
	//This function is called by the framework so you can add the objects inside a struct more suitable for search, such as an unordered set
	virtual void SetUpFiltering() = 0;

	//Checks if an object is in the filter, recommended to use a fast lookup data structure
	virtual bool IsInFilter(uint32_t filterNum, FilterType toSearch) = 0;
	//Inserts the desired element to the Nth filter.
	virtual void InsertToFilter(uint32_t filterNum, FilterType toInsert) = 0;
	//Deletes an object from the Nth filter
	virtual void DeleteFromFilter(uint32_t filterNum, FilterType toDelete) = 0;
	//Returns if the filter is empty
	virtual bool IsFilterEmpty(uint32_t filterNum) = 0;
	//Used by the framework to check if the Nth filter equals the passed value. Useful to avoid adding the same event repeatedly
	virtual bool IsFilterEqual(FilterType Filter, uint32_t filterNum) = 0;
	//Function used by the filter to check if the object passed is an accepted parameter
	virtual bool IsAcceptedParameter(FilterType toCheck) = 0;
	virtual uint32_t GetNumFilters() { return numFilters; }
};


class FilterBase : protected IFilter
{
protected:
	using FilterSet = std::unordered_set<unsigned int>;

	FilterSet* filterSet = nullptr;

	FilterSet* GetFilter(uint32_t index);

public:
	FilterBase(void** filters, uint32_t nuFilters);

	virtual ~FilterBase();

	bool IsInFilter(uint32_t filterNum, FilterType toSearch) override;

	bool IsFilterEmpty(uint32_t num) override;

	void InsertToFilter(uint32_t num, FilterType toInsert) override;

	void DeleteFromFilter(uint32_t num, FilterType toDelete) override;

	bool IsFilterEqual(FilterType filter, uint32_t num) override;

};


class FilterNull : public FilterBase
{
public:
	FilterNull(void** filters, uint32_t nuFilters) : FilterBase(filters, nuFilters){}

	virtual bool IsInFilter(uint32_t filterNum, FilterType toSearch) override { return true; }
	virtual void InsertToFilter(uint32_t filterNum, FilterType toInsert) override {}
	virtual void DeleteFromFilter(uint32_t filterNum, FilterType toDelete) override {}
	virtual bool IsFilterEqual(FilterType Filter, uint32_t nuFilter) override { return true; }
	virtual bool IsAcceptedParameter(FilterType parameter) override { return true; }
	virtual void SetUpFiltering() override {}
};

class FilterForm : public FilterBase
{
public:
	FilterForm(void** filters, uint32_t nuFilters) : FilterBase(filters, nuFilters){}

	bool IsAcceptedParameter(FilterType parameter) override;

	void SetUpFiltering() override;

	bool IsBaseInFilter(uint32_t filterNum, TESForm* form);

	void insertFormList(BGSListForm* formlist, uint32_t filter);
};

class FilterInt : public FilterBase
{
public:
	FilterInt(void** filters, uint32_t nuFilters) : FilterBase(filters, nuFilters){}

	bool IsFilterEqual(FilterType Filter, uint32_t nuFilter) override;

	bool IsAcceptedParameter(FilterType parameter) override
	{
		return true;
	}

	void SetUpFiltering() override;

	struct Data
	{
		int intID;
	};

	static void* __fastcall Create(void** filters, uint32_t nuFilters);
};


class FilterFormInt : public FilterBase
{

public:
	FilterFormInt(void** filters, uint32_t nuFilters) : FilterBase(filters, nuFilters) {}

	bool IsAcceptedParameter(FilterType parameter) override
	{
		return parameter.form->refID != 0x3B; // xMarker
	}

	void SetUpFiltering() override;

	struct Data
	{
		TESForm* form;
		int intID;
	};

	static void* __fastcall Create(void** filters, uint32_t nuFilters);
};

class EventBase
{
public:
	uint32_t Flags = 0;
	Script* script = nullptr;
	IFilter* eventFilter = nullptr;
	LambdaVariableContext capturedLambdaVars;

	EventBase() : capturedLambdaVars(nullptr){}

	enum GlobalEventFlags
	{
		kEventFlag_Deleted = 1 << 0,
	};

	bool GetDeleted() const
	{
		return Flags & kEventFlag_Deleted;
	}

	void SetDeleted(bool doSet)
	{
		doSet ? Flags |= kEventFlag_Deleted : Flags &= ~kEventFlag_Deleted;
	}
};

class EventInformation
{
private:
	void* (__fastcall*CreateFilter)(void**, uint32_t); // supposed to be passing itself
	std::vector<EventBase> eventAddQueue;
	std::shared_mutex queueLock;
	//need a readers writer lock to protect from multiple users registering an event in the same frame (very rare, but can happen)
public:
	const char* name;
	uint8_t numMaxArgs;
	uint8_t numMaxFilters;
	std::vector<EventBase> callbacks;

	EventInformation(const char* EventName, uint8_t& numMaxArgs, uint8_t& numMaxFilters, void* (__fastcall* CreatorFunction)(void**, uint32_t));

	virtual ~EventInformation();

	void FlushEventCallbacks();

	void virtual RegisterEvent(Script* script, void** filters);

	void virtual RemoveEvent(Script* script, void** filters);

	void virtual AddQueuedEvents();

	void virtual DeleteEvents();
};

typedef EventInformation* EventInfo;
extern std::mutex eventInfosMutex;
extern std::vector<EventInfo> EventInfos;

extern void* __fastcall GenericCreateFilter(void** Filters, uint32_t numFilters);

extern EventInfo __cdecl JGCreateEvent(const char* EventName, uint8_t maxArgs, uint8_t maxFilters, void* (__fastcall* CreatorFunction)(void**, uint32_t) = nullptr);

extern void __cdecl JGFreeEvent(EventInfo& toRemove);