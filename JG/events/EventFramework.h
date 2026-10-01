#pragma once
#include <unordered_set>
#include <vector>
#include <shared_mutex>
#include <algorithm>
#include "nvse/nvse/PluginAPI.h"
#include "LambdaVariableContext.h"

extern bool (*CallUDF)(class Script* funcScript, class TESObjectREFR* callingObj, uint8_t numArgs, ...);

class EventInformation;
extern void* __fastcall GenericCreateFilter(void** appFilters, uint32_t auiFilterCount);

using FormID = uint32_t;

union FilterType {
	void*			pVal;
	const TESForm*	pForm;
	FormID			uiFormID;
	int32_t			iVal;
	float			fVal;
	char*			pcVal;

	FilterType() : pVal(nullptr) {}

	FilterType(void* apVal) : pVal(apVal) {}

	FilterType(const TESForm* apForm) : pForm(apForm) {}

	FilterType(FormID auiFormID) : uiFormID(auiFormID) {}

	FilterType(int32_t aiVal) : iVal(aiVal) {}

	FilterType(float fltVal) : fVal(fltVal) {}

	FilterType(char* str) : pcVal(str) {}
};

class IFilter {
public:
	//Framework passes the objects to add to filter here
	FilterType* pFilterTypes = 0;

	//Used to know how many pFilterSets in total (aka the size of the FilterType array) the filter uses
	uint32_t uiFilterCount = 0;

	//Default destructor
	virtual ~IFilter() = default;

	//When the framework passes pFilterSets, it passes them to the pFilterTypes array pointer, specifying the number of pFilterSets in the auiFilterCount member
	//This function is called by the framework so you can add the objects inside a struct more suitable for search, such as an unordered set
	virtual void SetUpFiltering() = 0;

	//Checks if an object is in the filter, recommended to use a fast lookup data structure
	virtual bool IsInFilter(uint32_t auiIndex, FilterType auFilter) const = 0;

	//Inserts the desired element to the Nth filter.
	virtual void InsertToFilter(uint32_t auiIndex, FilterType auFilter) = 0;

	//Deletes an object from the Nth filter
	virtual void DeleteFromFilter(uint32_t auiIndex, FilterType auFilter) = 0;

	//Returns if the filter is empty
	virtual bool IsFilterEmpty(uint32_t auiIndex) = 0;

	//Used by the framework to check if the Nth filter equals the passed value. Useful to avoid adding the same event repeatedly
	virtual bool IsFilterEqual(FilterType auFilter, uint32_t auiIndex) = 0;

	//Function used by the filter to check if the object passed is an accepted parameter
	virtual bool IsAcceptedParameter(FilterType auFilter) = 0;

	virtual uint32_t GetNumFilters() { return uiFilterCount; }
};


class FilterBase : protected IFilter {
protected:
	using FilterSet = std::unordered_set<unsigned int>;

	FilterSet* pFilterSets = nullptr;

	FilterSet* __fastcall GetFilter(uint32_t auiIndex) const;

public:
	FilterBase(void** appFilters, uint32_t auiFilterCount);

	virtual ~FilterBase();

	bool IsInFilter(uint32_t auiIndex, FilterType auFilter) const override;

	bool IsFilterEmpty(uint32_t auiIndex) override;

	void InsertToFilter(uint32_t auiIndex, FilterType auFilter) override;

	void DeleteFromFilter(uint32_t auiIndex, FilterType auFilter) override;

	bool IsFilterEqual(FilterType auFilter, uint32_t auiIndex) override;
};

class FilterForm : public FilterBase {
protected:
	static bool __fastcall DoFilterForm(const FilterSet& arSet, const TESForm* apForm);
	static bool __fastcall DoFilterRef(const FilterSet& arSet, const TESObjectREFR* apRef);

public:
	FilterForm(void** appFilters, uint32_t auiFilterCount) : FilterBase(appFilters, auiFilterCount) {}

	bool IsAcceptedParameter(FilterType auFilter) override;

	void SetUpFiltering() override;

	bool __fastcall IsAnyFormInFilter(uint32_t auiIndex, const TESForm* apForm) const;
	
	bool __fastcall IsNonRefFormInFilter(uint32_t auiIndex, const TESForm* apForm) const;

	bool __fastcall IsRefInFilter(uint32_t auiIndex, const TESObjectREFR* apRef) const;

	void __fastcall InsertForm(uint32_t auiIndex, const TESForm* apForm);

	void __fastcall InsertFormList(uint32_t auiIndex, const BGSListForm* apFormList);

	void __fastcall InsertReference(uint32_t auiIndex, const TESObjectREFR* apRef);
};

class FilterInt : public FilterBase {
public:
	FilterInt(void** appFilters, uint32_t auiFilterCount) : FilterBase(appFilters, auiFilterCount) {}

	bool IsAcceptedParameter(FilterType auFilter) final { return true; }

	void SetUpFiltering() final;

	struct Data {
		int32_t		iVal;
	};

	bool __fastcall IsIntInFilter(uint32_t auiIndex, int32_t aiVal) const { return FilterBase::IsInFilter(auiIndex, aiVal); };

	static void* __fastcall Create(void** appFilters, uint32_t auiFilterCount);
};


class FilterFormInt : public FilterForm {
public:
	FilterFormInt(void** appFilters, uint32_t auiFilterCount) : FilterForm(appFilters, auiFilterCount) {}

	bool IsAcceptedParameter(FilterType auFilter) final;

	void SetUpFiltering() final;

	struct Data {
		TESForm*	pForm;
		int32_t		iVal;
	};

	bool __fastcall IsIntInFilter(int32_t aiVal) const { return FilterBase::IsInFilter(1, aiVal); }

	static void* __fastcall Create(void** appFilters, uint32_t auiFilterCount);
};

class EventBase
{
public:
	Bitfield16				usFlags;
	Bitfield16				usUserFlags;
	Script*					pScript = nullptr;
	IFilter*				pFilter = nullptr;
	LambdaVariableContext	pLambdaVars;

	EventBase() : pLambdaVars(nullptr) {}

	enum GlobalEventFlagBits {
		DELETED = 0,
	};

	bool GetDeleted() const { return usFlags.GetBit<DELETED>(); }
	void SetDeleted(bool abVal) { usFlags.SetBit<DELETED>(abVal); }
};

class EventInformation
{
private:
	void* (__fastcall*		CreateFilter)(void**, uint32_t); // supposed to be passing itself
	std::vector<EventBase>	kEventAddQueue;
	std::shared_mutex		kQueueLock;
	//need a readers writer lock to protect from multiple users registering an event in the same frame (very rare, but can happen)
public:
	const char*				pName;
	uint8_t					ucMaxArgsCount;
	uint8_t					ucMaxFilterCount;
	std::vector<EventBase>	kCallbacks;

	EventInformation(const char* apEventName, uint8_t& arMaxArgs, uint8_t& arMaxFilters, void* (__fastcall* CreatorFunction)(void**, uint32_t));

	virtual ~EventInformation() final;

	void FlushEventCallbacks();

	void virtual RegisterEvent(Script* apScript, void** appFilters, uint32_t auiUserFlags = 0) final;

	void virtual RemoveEvent(Script* apScript, void** appFilters) final;

	void virtual AddQueuedEvents() final;

	void virtual DeleteEvents() final;
};

typedef EventInformation* EventInfo;
extern std::vector<EventInfo> kEventInfos;

extern void* __fastcall GenericCreateFilter(void** appFilters, uint32_t auiFilterCount);

extern EventInfo __cdecl JGCreateEvent(const char* apEventName, uint8_t aucMaxArgs, uint8_t aucMaxFilters, void* (__fastcall* CreatorFunction)(void**, uint32_t) = nullptr);

extern void __cdecl JGFreeEvent(EventInfo& arEvent);