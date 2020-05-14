#pragma once

NVSEScriptInterface* scrInterface;
bool (*FunctionCallScript)(Script* funcScript, TESObjectREFR* callingObj, TESObjectREFR* container, NVSEArrayElement* result, UInt8 numArgs, ...);
NVSEArrayElement EventResultPtr;
class EventInformation;
bool __fastcall GenericAcceptedParameter(TESForm* parameter);
void  __fastcall GenericFilter(EventInformation* eventinfo, BaseEventClass* BaseToFilter);

// = sizeof(JGEventIDs) / sizeof(UInt32);


UInt32 NumEvents = 0;



NVSEArrayElement e_eventResult;





class EventInformation
{
public:
	EventInformation(const char* EventName, UInt8& numMaxArgs, UInt8& numMaxFilters, bool(__fastcall*GetAcceptedParameter)(TESForm*), void(__fastcall* SetUpFiltering)(EventInformation*, BaseEventClass*))
	{
		this->EventName = EventName;
		this->numMaxArgs = numMaxArgs;
		this->numMaxFilters = numMaxFilters;
		if (!GetAcceptedParameter) GetAcceptedParameter = GenericAcceptedParameter;
		this->IsAcceptedParameter = GetAcceptedParameter;
		if (!SetUpFiltering) SetUpFiltering = GenericFilter;
		 this->SetUpFiltering =  SetUpFiltering;
	}
	const char* EventName;
	bool  (__fastcall* IsAcceptedParameter)(TESForm*);
	void(__fastcall* SetUpFiltering)(EventInformation*, BaseEventClass*); // supposed to be passing itself
	UInt8 numMaxArgs;
	UInt8 numMaxFilters;
	EventContainer<BaseEventClass> EventCallbacks;

	void RegisterEvent(Script* script, TESForm** filters)
	{
		UInt32 maxFilters = this->numMaxFilters;
		for (EventContainer<BaseEventClass>::iterator it = this->EventCallbacks.begin(); it != this->EventCallbacks.end(); ++it)
		{
			if (script == (*it)->ScriptForEvent)
			{
				if (!maxFilters) return;
				for (int i = 0; i < maxFilters; i++)
				{
					if (filters[i] != (*it)->Filters[i]) break;
				}
				return;
			}

		}

		BaseEventClass* NewEvent = new BaseEventClass();
		NewEvent->ScriptForEvent = script;
		if (maxFilters)
		{
			NewEvent->eventFilter = new JohnnyEventFilters(maxFilters);
			SetUpFiltering(this, NewEvent);
		}
		this->EventCallbacks.push_back(NewEvent);
	}
	void RemoveEventFromGame(Script* script, TESForm** filters)
	{
		UInt32 maxFilters = this->numMaxFilters;
		auto it = EventCallbacks.begin();
		while (it != EventCallbacks.end())
		{
			if (script == (*it)->ScriptForEvent)
			{
				if (maxFilters);
				{
					for (int i = 0; i < maxFilters; i++)
					{
						if (filters[i] != (*it)->Filters[i]) goto NotFound;

					}
				}

				delete (*it)->eventFilter;
				delete (*it);
				it = EventCallbacks.erase(it);
				continue;
			}
		NotFound:
			it++;

		}
	}

	

};

std::vector<EventInformation*> EventsArray;

bool __fastcall GenericAcceptedParameter(TESForm* parameter)
{
	return true;
}


void __fastcall GenericFilter(EventInformation* eventinfo, BaseEventClass* BaseToFilter)
{
	for (int i = 0; i < eventinfo->numMaxFilters; i++)
	{
		TESForm* currentFilter = BaseToFilter->Filters[i];
		if (!currentFilter) continue;
		if (currentFilter->GetIsReference()) continue;
		if (IS_TYPE(currentFilter, BGSListForm))
		{
			ListNode<TESForm>* iterator = ((BGSListForm*)currentFilter)->list.Head();
			do {
				TESForm* it = iterator->data;
				if (it->GetIsReference()) continue;
				if (GenericAcceptedParameter(it))
					BaseToFilter->eventFilter->InsertToFilter(i, it->refID);
			} while (iterator = iterator->next);

		}
		else BaseToFilter->eventFilter->InsertToFilter(i, currentFilter->refID);

	}

	

}
EventInformation* FindHandlerInfoByChar(const char* nameToFind)
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

EventInformation* DefineEvent(const char* EventName, UInt8 maxArgs, UInt8 maxFilters, bool(__fastcall *GetAcceptedParameter)(TESForm*), void(__fastcall* SetUpFiltering)(EventInformation*, BaseEventClass*))
{
	EventInformation* eventinfo = new EventInformation(EventName, maxArgs, maxFilters, GetAcceptedParameter, SetUpFiltering);
	EventsArray.push_back(eventinfo);
	return eventinfo;
		
}





ParamInfo kParamsJohnnyEventOneForm_OneOptionalIntFourOptionalForms[7] =
{
	{ "Event name", kParamType_String, 0 },
	{ "Script", kParamType_AnyForm, 0 },
	{ "flags", kParamType_Integer, 1 },
	{ "Form", kParamType_AnyForm, 1 },
	{ "Form", kParamType_AnyForm, 1 },
	{ "Form", kParamType_AnyForm, 1 },
	{ "Form", kParamType_AnyForm, 1 }

};

DEFINE_COMMAND_PLUGIN(RegisterEventHandlerScript, , 0, 7, kParamsJohnnyEventOneForm_OneOptionalIntFourOptionalForms);
DEFINE_COMMAND_PLUGIN(UnregisterEventHandlerScript, , 0, 7, kParamsJohnnyEventOneForm_OneOptionalIntFourOptionalForms);

bool Cmd_RegisterEventHandlerScript_Execute(COMMAND_ARGS)
{
	Script* script;
	TESForm* filters[4];
	UInt32 flags;
	char EventName[MAX_PATH];
	if (!(ExtractArgs(EXTRACT_ARGS,&EventName , &script, &flags, &filters[1], &filters[2], &filters[3], &filters[4]) || !IS_TYPE(script, Script))) return true;
	{	
		EventInformation* EventHand = FindHandlerInfoByChar(EventName);
		if (EventHand)
		{
			EventHand->RegisterEvent(script, filters);

		}
		return true;
	}
}

bool Cmd_UnregisterEventHandlerScript_Execute(COMMAND_ARGS)
{
	Script* script;
	TESForm* filters[4];
	char EventName[MAX_PATH];
	UInt32 flags;
	if (!(ExtractArgs(EXTRACT_ARGS, &EventName, &script, &flags, &filters[1], &filters[2], &filters[3], &filters[4]) || !IS_TYPE(script, Script))) return true;
	{
		EventInformation* EventHand = FindHandlerInfoByChar(EventName);
		if (EventHand)
		{
			EventHand->RemoveEventFromGame(script, filters);
		}
		return true;
	}
}






