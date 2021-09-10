#pragma once
#include <variant>
#include <unordered_set>

using RefID = UInt32;	// todo: place higher in the include order.

using FilterTypes = std::variant<RefID, TESForm*, int, float, std::string>;
//using FilterTypeSet = std::unordered_set<FilterTypes>; // too flexible

// Set shortcuts 
using StringSet = std::unordered_set<std::string>;
using FloatSet = std::unordered_set<float>;
using IntSet = std::unordered_set<int>;
using FormSet = std::unordered_set<TESForm*>;
using RefIDSet = std::unordered_set<RefID>;

using FilterTypeSets = std::variant<RefIDSet, FormSet, IntSet, FloatSet, StringSet>;
using FilterTypeSetArray = std::vector<FilterTypeSets>;

static_assert(std::variant_size_v<FilterTypeSets> == std::variant_size_v<FilterTypes>);
// todo: Assert that for each type in FilterTypes, the matching base type from FilterTypeSets must have the same index.
//static_assert(std::is_same_v<RefID, std::variant_alternative_t<0, FilterTypes>>);
/*static_assert(std::is_same_v<
	std::decltype(std::declval<std::variant_alternative_t<0, FilterTypeSets>>().begin().),
	std::variant_alternative_t<0, FilterTypes>>);*/
//static_assert(std::is_same_v<float, std::variant_alternative_t<1, my_variant>>);

class EventHandlerInterface
{
public:
	FilterTypeSetArray filtersArr;
	//Framework passes the objects to add to filter here
	virtual ~EventHandlerInterface() = default;
	//When the framework passes filters, it passes them to the GenFilters array pointer, specifying the number of filters in the numFilters member
	//This function is called by the framework so you can add the objects inside a struct more suitable for search, such as an unordered set
	virtual void SetUpFiltering() = 0;

	//Checks if an object is in the filter, recommended to use a fast lookup data structure
	virtual bool IsInFilter(UInt32 filterNum, FilterTypes toSearch) = 0;
	//Inserts the desired element to the Nth filter.
	virtual bool InsertToFilter(UInt32 filterNum, FilterTypes toInsert) = 0;
	//Deletes an object from the Nth filter
	virtual bool DeleteFromFilter(UInt32 filterNum, FilterTypes toDelete) = 0;
	//Returns if the filter is empty
	virtual bool IsFilterEmpty(UInt32 filterNum) = 0;
	//Used by the framework to check if the Nth filter equals the passed value. Useful to avoid adding the same event repeatedly
	virtual bool IsFilterEqual(UInt32 filterNum, FilterTypes filter) = 0;
	//Function used by the filter to check if the object passed is an accepted parameter
	virtual bool IsAcceptedParameter(FilterTypes toCheck) = 0;
	//Hope a UInt32 is large enough.
	virtual UInt32 GetNumFilters() { return filtersArr.size(); }
	
	//numFilter is 0-indexed	//todo: add to private or w/e
	FilterTypeSets* GetFilter(UInt32 numFilter)
	{
		if (numFilter >= filtersArr.size()) return nullptr;
		return &filtersArr[numFilter];
	}
};

/*
class EventContainerInterface
{
public:
	void virtual RegisterEvent(Script* script, void** filters);
	void virtual RemoveEvent(Script* script, void** filters);
};


EventContainerInterface* (_cdecl* CreateScriptEvent)(const char* EventName, UInt8 maxArgs, UInt8 maxFilters, void* (__fastcall* CustomConstructor)(void**, UInt32));
void(__cdecl* FreeScriptEvent)(EventContainerInterface*& toRemove);

class BaseEventClass
{
public:
	ULONG_PTR Flags = 0;
	Script* ScriptForEvent = NULL;
	EventHandlerInterface* eventFilter = NULL;
	LambdaVariableContext capturedLambdaVars;

	BaseEventClass() : capturedLambdaVars(nullptr){}

	enum GlobalEventFlags
	{
		kEventFlag_Deleted = 1 << 0,
	};

	bool GetDeleted()
	{
		return Flags & kEventFlag_Deleted;
	}
	void SetDeleted(bool doSet)
	{

		doSet ? Flags |= kEventFlag_Deleted : Flags &= ~kEventFlag_Deleted;
	}
};
*/
