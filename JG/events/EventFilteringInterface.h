#pragma once
#include <variant>
#include <unordered_set>

//using RefID = UInt32;
UInt32 const g_xMarkerID = 0x3B;

using FilterTypes = std::variant<TESForm*, int, float, std::string>;

// If there are more than 1 item per filter, will search for any match.
// Example: can fill an IntSet with multiple EquipSlot codes, and if any are matched, then event handler will fire.
using StringSet = std::unordered_set<std::string>;
using FloatSet = std::unordered_set<float>;
using IntSet = std::unordered_set<int>;
using FormSet = std::unordered_set<TESForm*>;
//using RefIDSet = std::unordered_set<RefID>;
// Removed support for direct RefIDs, as it is cumbersome to look-up the form each time to check if it's a form-list.

using FilterTypeSets = std::variant<FormSet, IntSet, FloatSet, StringSet>;
using FilterTypeSetArray = std::vector<FilterTypeSets>;

static_assert(std::variant_size_v<FilterTypeSets> == std::variant_size_v<FilterTypes>);

class EventHandlerInterface
{
public:
	FilterTypeSetArray filtersArr;
	
	// Framework passes the objects to add to filter here
	virtual ~EventHandlerInterface() = default;
	
	// Used to filter out "-1" int codes, transform a form-list TESForm* into a bunch of TESForm*s, etc.
	// Alternatively, can set up one's own data structures here.
	virtual void SetUpFiltering() = 0;

	// Checks if an object is in the filter, recommended to use a fast lookup data structure
	virtual bool IsInFilter(UInt32 filterNum, FilterTypes toSearch) = 0;
	
	// Inserts the desired element to the Nth filter.
	virtual bool InsertToFilter(UInt32 filterNum, FilterTypes toInsert) = 0;
	
	// Deletes an object from the Nth filter
	virtual bool DeleteFromFilter(UInt32 filterNum, FilterTypes toDelete) = 0;
	
	// Returns if the filter is empty
	virtual bool IsFilterEmpty(UInt32 filterNum) = 0;
	
	// Used by the framework to check if the Nth filter equals the passed value set. Useful to avoid adding the same event repeatedly
	virtual bool IsFilterEqual(UInt32 filterNum, FilterTypeSets cmpFilterSet) = 0;
	
	// Function used by the filter to check if the object passed is an accepted parameter
	virtual bool IsAcceptedParameter(FilterTypes parameter) = 0;
	
	// Hope a UInt32 is large enough.
	virtual UInt32 GetNumFilters() { return filtersArr.size(); }
	
	// numFilter is 0-indexed	//todo: add to private or w/e
	FilterTypeSets* GetFilter(UInt32 numFilter)
	{
		if (numFilter >= filtersArr.size()) return nullptr;
		return &filtersArr[numFilter];
	}
};

/* UNUSED
class EventContainerInterface
{
public:
	void virtual RegisterEvent(Script* script, void** filters);
	void virtual RemoveEvent(Script* script, void** filters);
};

EventContainerInterface* (_cdecl* CreateScriptEvent)(const char* EventName, UInt8 maxArgs, UInt8 maxFilters, void* (__fastcall* CustomConstructor)(void**, UInt32));
void(__cdecl* FreeScriptEvent)(EventContainerInterface*& toRemove);
*/

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

