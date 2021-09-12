#pragma once
#include <variant>
#include <unordered_set>
#include "PluginAPI.h"
#include "events/LambdaVariableContext.h"

using RefID = UInt32;
using FilterTypes = std::variant<RefID, int, float, std::string>;

// The following filter values are ignored by GenericEventFilters (unfiltered).
enum IgnoreFilter_Values
{
	// For RefID filters
	kIgnFilter_xMarkerID = 0x3B,
	kIgnFilter_RefID = kIgnFilter_xMarkerID,
	kIgnFilter_FormID = kIgnFilter_xMarkerID,
	kIgnFilter_Form = kIgnFilter_xMarkerID,

	// For int filters
	kIgnFilter_Int = -1,
};

// If there are more than 1 item per filter, will search for any match.
// Example: can fill an IntSet with multiple EquipSlot codes, and if any are matched, then event handler will fire.
using StringSet = std::unordered_set<std::string>;
using FloatSet = std::unordered_set<float>;
using IntSet = std::unordered_set<int>;
// Storing TESForm* can cause rare crashes due to dynamic refs, so use RefIDs.
using RefIDSet = std::unordered_set<RefID>;

using FilterTypeSets = std::variant<RefIDSet, IntSet, FloatSet, StringSet>;
using FilterTypeSetArray = std::vector<FilterTypeSets>;

static_assert(std::variant_size_v<FilterTypeSets> == std::variant_size_v<FilterTypes>);

#if NULL //examples:
	FilterTypeSets testFilter1 = { IntSet {5, 0x7} };
	FilterTypeSets testFilter2 = { StringSet {"testStr", "testStr2", "tt"}};
	FilterTypeSetArray testFilters = { testFilter1, testFilter2 };
#endif


class EventHandlerFilterBase
{
public:
	FilterTypeSetArray filtersArr;
	
	// The original filters array that was passed, before SetUpFiltering() was called.
	// Costs more mem, but saves us from having to deep-check form-lists when checking IsGenFilterEqual().
	FilterTypeSetArray genFiltersArr; 
	
	// Framework passes the objects to add to filter here
	virtual ~EventHandlerFilterBase() = default;
	
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
	
	// Used by the framework to check if the Nth Gen filter equals the passed value set. Useful to avoid adding the same event repeatedly
	virtual bool IsGenFilterEqual(UInt32 filterNum, FilterTypeSets const &cmpFilterSet) = 0;

	// Used to check if the Nth Gen filter equals the passed value set.
	// ALL default-value Gen filters are said to be "equal".
	// Useful to mass-remove events by using default filters.
	virtual bool IsGenFilterEqualAlt(UInt32 filterNum, FilterTypeSets const &cmpFilterSet) = 0;
	
	// Function used by the filter to check if the object passed is an accepted parameter
	virtual bool IsAcceptedParameter(FilterTypes parameter) = 0;
	
	// Hope a UInt32 is large enough.
	virtual UInt32 GetNumFilters() { return filtersArr.size(); }
	virtual UInt32 GetNumGenFilters() { return genFiltersArr.size(); }
	
	// numFilter is 0-indexed
	FilterTypeSets* GetNthFilter(UInt32 numFilter)
	{
		if (numFilter >= filtersArr.size()) return nullptr;
		return &filtersArr[numFilter];
	}
	FilterTypeSets* GetNthGenFilter(UInt32 numFilter)
	{
		if (numFilter >= genFiltersArr.size()) return nullptr;
		return &genFiltersArr[numFilter];
	}
};

// All event filters should inherit from this.
// Used by EventInformation class to ensure that the declared filter type is the same when registering/removing events.
struct EventFilter_Base
{
	virtual ~EventFilter_Base() = default;
	[[nodiscard]] virtual FilterTypeSetArray ToFilter() const = 0;
};

