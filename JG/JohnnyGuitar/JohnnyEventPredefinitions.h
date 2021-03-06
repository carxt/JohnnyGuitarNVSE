#pragma once
#include "JohnnyGuitar/EventFilteringInterface.h"

bool (*FunctionCallScript)(Script* funcScript, TESObjectREFR* callingObj, TESObjectREFR* container, NVSEArrayElement* result, UInt8 numArgs, ...);
NVSEArrayElement EventResultPtr;
class EventInformation;
void*  __fastcall GenericCreateFilterFunction( void** maxFilters, UInt32 numFilters);


class JohnnyEventFiltersForm : EventHandlerInterface
{


	typedef  std::unordered_set<unsigned int> RefUnorderedSet;
private:
	RefUnorderedSet* Filters = 0;

	RefUnorderedSet* GetFilter(UInt32 filter)
	{
		if (filter >= numFilters) return NULL;
		return &(Filters[filter]);
	}
public:

	
	JohnnyEventFiltersForm(void** filters, UInt32 nuFilters)
	{
		numFilters = nuFilters;
		Filters = new RefUnorderedSet[numFilters];
		GenFilters = new GenericFilters[numFilters];
		for (int i = 0; i < nuFilters; i++) GenFilters[i].ptr = filters[i];

	}
	virtual ~JohnnyEventFiltersForm()
	{
		delete[] Filters;
		delete[] GenFilters;
	}

	virtual bool IsInFilter(UInt32 filterNum, GenericFilters toSearch)
	{
		RefUnorderedSet* FilterSet;
		if (!(FilterSet = GetFilter(filterNum))) return false;
		//RefUnorderedSet::const_iterator got = FilterSet->find(toSearch);
		return  FilterSet->empty() || (FilterSet->find(toSearch.refID) != FilterSet->end());
	}


	virtual void InsertToFilter(UInt32 filterNum, GenericFilters toInsert)
	{
		RefUnorderedSet* FilterSet;
		if (!(FilterSet = GetFilter(filterNum))) return;
		FilterSet->insert(toInsert.refID);
	}
	virtual void DeleteFromFilter(UInt32 filterNum, GenericFilters toDelete)
	{
		RefUnorderedSet* FilterSet;
		if (!(FilterSet = GetFilter(filterNum))) return;
		FilterSet->erase(toDelete.refID);

	}
	virtual bool IsFilterEmpty(UInt32 filterNum)
	{
		RefUnorderedSet* FilterSet = GetFilter(filterNum);
		if (!FilterSet) return true;
		return FilterSet->empty();
	}
	virtual bool IsFilterEqual(GenericFilters Filter, UInt32 nuFilter)
	{
		return (Filter.ptr == GenFilters[nuFilter].ptr);
	}
	virtual bool IsAcceptedParameter(GenericFilters parameter)
	{

		return parameter.form->typeID != kFormType_TESObjectSTAT;

	}

	virtual void SetUpFiltering()
	{
		for (int i = 0; i < numFilters; i++)
		{
			TESForm* currentFilter = GenFilters[i].form;
			if (!currentFilter) continue;
			if (!(IsAcceptedParameter(currentFilter))) continue;
			if (currentFilter->GetIsReference())
			{
				InsertToFilter(i, ((TESObjectREFR*)currentFilter)->baseForm->refID);
				continue;
			}
			if (IS_TYPE(currentFilter, BGSListForm))
			{
				//Console_Print("filter looping");
				ListNode<TESForm>* iterator = ((BGSListForm*)currentFilter)->list.Head();
				do {
					TESForm* it = iterator->data;
					if (it->GetIsReference()) continue;
					if (IsAcceptedParameter(it))
						InsertToFilter(i, it->refID);
				} while (iterator = iterator->next);

			}
			else InsertToFilter(i, currentFilter->refID);


		}


	}

	__forceinline bool IsBaseInFilter(UInt32 filterNum, TESForm* form)
	{
		if (!form) return false;
		if (form->GetIsReference()) return IsInFilter(filterNum, ((TESObjectREFR*)form)->baseForm->refID);
		return IsInFilter(filterNum, form->refID);
	}

	void insertFormList(BGSListForm* List, UInt32 filter)
	{
		ListNode<TESForm>* iterator = ((BGSListForm*)List)->list.Head();
		do {
			InsertToFilter(filter, iterator->data->refID);
		} while (iterator = iterator->next);
	}
};





inline UInt32 RetrieveAddrFromDisp32Opcode(UInt32 address)
{
	//works for 5 byte opcodes like far call, far jmp, etc
	//for a 6 byte opcode you should pass address + 1
	return *(UInt32*)(address + 1) + address + 5;
}

UInt32 NumEvents = 0;



NVSEArrayElement e_eventResult;




class EventInformation
{
private:
	void* (__fastcall* CreateFilter)(void**, UInt32); // supposed to be passing itself
	std::vector<BaseEventClass> EventQueueAdd;
public:
	const char* EventName;
	UInt8 numMaxArgs;
	UInt8 numMaxFilters;
	std::vector<BaseEventClass> EventCallbacks;
	EventInformation(const char* EventName, UInt8& numMaxArgs, UInt8& numMaxFilters, void* (__fastcall* CreatorFunction)(void**, UInt32))
	{
		this->EventName = EventName;
		this->numMaxArgs = numMaxArgs;
		this->numMaxFilters = numMaxFilters;
		this->CreateFilter = GenericCreateFilterFunction;
		if (CreatorFunction) this->CreateFilter = CreatorFunction;
	}
	virtual ~EventInformation()
	{
		FlushEventCallbacks();
	}
	void FlushEventCallbacks()
	{
		auto it = EventCallbacks.begin();
		while (it != EventCallbacks.end())
		{
			delete it->eventFilter;
			++it;
		}
		EventCallbacks.clear();
	}


	void virtual RegisterEvent(Script* script, void** filters)
	{
		UInt32 maxFilters = this->numMaxFilters;
		for (std::vector<BaseEventClass>::iterator it = this->EventCallbacks.begin(); it != this->EventCallbacks.end(); ++it)
		{
			if (script == it->ScriptForEvent)
			{
				if (!maxFilters) return;
				if (!it->eventFilter->GetNumFilters()) continue;
				int i = 0; // filter iterator
				for (; i < maxFilters; i++)
				{
					if (!(it->eventFilter->IsFilterEqual(filters[i],i ))) break;
				}
				if (i >= maxFilters) return;
			}

		}
		for (std::vector<BaseEventClass>::iterator it = this->EventQueueAdd.begin(); it != this->EventQueueAdd.end(); ++it)
		{
			if (script == it->ScriptForEvent)
			{
				if (!maxFilters) return;
				if (!it->eventFilter->GetNumFilters()) continue;
				int i = 0; // filter iterator
				for (; i < maxFilters; i++)
				{
					if (!(it->eventFilter->IsFilterEqual(filters[i], i))) break;
				}
				if (i >= maxFilters) return;
			}

		}
		BaseEventClass NewEvent;
		NewEvent.ScriptForEvent = script;
		if (maxFilters)
		{

			*(void**) &(NewEvent.eventFilter) = this->CreateFilter(filters, maxFilters);
			NewEvent.eventFilter->SetUpFiltering();
		}
		this->EventQueueAdd.push_back(NewEvent);
	}
	void virtual RemoveEventFromGame(Script* script, void** filters)
	{
		auto it = EventCallbacks.begin();
		while (it != EventCallbacks.end())
		{
			if (script == it->ScriptForEvent)
			{
				UInt32 maxFilters = it->eventFilter->GetNumFilters();

				if (maxFilters)
				{
					for (int i = 0; i < maxFilters; i++)
					{
						if (!(it->eventFilter->IsFilterEqual(filters[i], i))) goto NotFound;

					}
				}
				it->SetDeleted(true);
			}
		NotFound:
			it++;

		}
	}
	void virtual AddQueuedEvents()
	{

		EventCallbacks.insert(EventCallbacks.end(), EventQueueAdd.begin(), EventQueueAdd.end());
		EventQueueAdd.clear();
	}
	void virtual DeleteEventsFromMemory()
	{
		auto it = EventCallbacks.begin();
		while (it != EventCallbacks.end())
		{
			if (it->GetDeleted())
			{
				UInt32 maxFilters = it->eventFilter->GetNumFilters();

				if (maxFilters)
				{
					delete it->eventFilter;
				}

				it = EventCallbacks.erase(it);
				continue;
			}
		NotFound:
			it++;

		}
	}
	int a = sizeof(std::unordered_set<char>);
};
typedef EventInformation* EventInfo;
std::vector<EventInfo> EventsArray;



void*  __fastcall GenericCreateFilterFunction(void** Filters, UInt32 numFilters) {
	return new JohnnyEventFiltersForm( Filters, numFilters );
}



EventInfo FindHandlerInfoByChar(const char* nameToFind)
{
	auto it = EventsArray.begin();
	while (it != EventsArray.end())
	{
		if (!(_stricmp((*it)->EventName, nameToFind)))
			return *it;
		it++;
	}
	return NULL;
}

EventInfo __cdecl JGCreateEvent(const char* EventName, UInt8 maxArgs, UInt8 maxFilters, void* (__fastcall* CreatorFunction)( void**, UInt32) )
{
	EventInfo eventinfo = new EventInformation(EventName, maxArgs, maxFilters, CreatorFunction);
	EventsArray.push_back(eventinfo);
	return eventinfo;

}


void __cdecl JGFreeEvent(EventInfo& toRemove)
{
	if (!toRemove) return;
	auto it = std::find(std::begin(EventsArray), std::end(EventsArray), toRemove);
	if (it != EventsArray.end())
	{
		delete* it;
		it = EventsArray.erase(it);
	}
	toRemove = NULL;
}








