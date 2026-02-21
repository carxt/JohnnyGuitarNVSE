#pragma once
// Region functions
DEFINE_COMMAND_PLUGIN(GetRegionWeatherOverride, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetRegionWeatherOverride, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetRegionWeatherPriority, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetRegionWeatherPriority, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(IsWeatherInRegion, , false, kParams_TwoForms);
DEFINE_COMMAND_PLUGIN(RemoveRegionWeather, , false, kParams_TwoForms);
DEFINE_COMMAND_PLUGIN(AddRegionWeather, , false, kParams_OneForm_OneWeatherID_OneInt_OneOptionalGlobal);
DEFINE_COMMAND_PLUGIN(GetRegionWeathers, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(ClearRegionWeathers, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetRegionMapName, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetRegionMapName, , false, kParams_OneForm_OneString);
DEFINE_COMMAND_PLUGIN(GetNthRegionWeatherType, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetNthRegionWeatherChance, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetNthRegionWeatherGlobal, , false, kParams_OneForm_OneInt);

bool Cmd_GetNthRegionWeatherGlobal_Execute(COMMAND_ARGS) {
	TESRegion* region = nullptr;
	int id = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &region, &id) && id > 0 && region && IS_TYPE(region, TESRegion)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData && !weatherData->weatherTypes.Empty()) {
			WeatherEntry* entry = weatherData->weatherTypes.GetNthItem(id);
			if (entry && entry->chance) *(uint32_t*)result = entry->global->GetFormID();
		}
	}
	return true;
}

bool Cmd_GetNthRegionWeatherChance_Execute(COMMAND_ARGS) {
	TESRegion* region = nullptr;
	int id = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &region, &id) && id > 0 && region && IS_TYPE(region, TESRegion)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData && !weatherData->weatherTypes.Empty()) {
			WeatherEntry* entry = weatherData->weatherTypes.GetNthItem(id);
			if (entry && entry->chance) *result = entry->chance;
		}
	}
	return true;
}
bool Cmd_GetNthRegionWeatherType_Execute(COMMAND_ARGS) {
	TESRegion* region = nullptr;
	int id = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &region, &id) && id > 0 && region && IS_TYPE(region, TESRegion)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData && !weatherData->weatherTypes.Empty()) {
			WeatherEntry* entry = weatherData->weatherTypes.GetNthItem(id);
			if (entry && entry->weather) *(uint32_t*)result = entry->weather->GetFormID();
		}
	}
	return true;
}
bool Cmd_SetRegionMapName_Execute(COMMAND_ARGS) {
	TESRegion* region = nullptr;
	char newName[MAX_PATH];
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &region, &newName) && region && IS_TYPE(region, TESRegion)) {
		TESRegionDataMap* mapData = GetMapData(region);
		if (mapData) {
			mapData->mapName.Set(newName);
		}
		else {
			mapData = BSMemory::malloc<TESRegionDataMap>();
			ThisCall(0x4F3CA0, mapData);
			mapData->mapName.Set(newName);
			region->dataEntries->Append(mapData);
		}
		*result = 1;
	}
	return true;
}
bool Cmd_GetRegionMapName_Execute(COMMAND_ARGS) {
	TESRegion* region = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &region) && region && IS_TYPE(region, TESRegion)) {
		TESRegionDataMap* mapData = GetMapData(region);
		if (mapData) g_strInterface->Assign(PASS_COMMAND_ARGS, mapData->mapName.c_str());
	}
	return true;
}

bool Cmd_GetRegionWeathers_Execute(COMMAND_ARGS) {
	TESRegion* region = nullptr;
	NVSEArrayVar* weatherArr = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &region) && region && IS_TYPE(region, TESRegion)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			ListNode<WeatherEntry>* iter = weatherData->weatherTypes.Head();
			do {
				if (iter->data) {
					g_arrInterface->AppendElement(weatherArr, NVSEArrayElement(iter->data->weather));
					if (IsConsoleMode())
						Console_Print(iter->data->weather->GetFormEditorID());
				}
			} while (iter = iter->next);
		}
	}
	g_arrInterface->AssignCommandResult(weatherArr, result);
	return true;
}
bool Cmd_ClearRegionWeathers_Execute(COMMAND_ARGS) {
	TESRegion* region = nullptr;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &region) && region && IS_TYPE(region, TESRegion)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			ListNode<WeatherEntry>* headNode = weatherData->weatherTypes.Head(), * iter = headNode->next;
			while (iter) {
				BSMemory::free(iter->data);
				iter = iter->RemoveMe();
			}
			if (headNode->next) {
				headNode->RemoveNext();
			}
			else {
				BSMemory::free(headNode->data);
				headNode->RemoveMe();
			}
			*result = 1;
		}
	}
	return true;
}
bool Cmd_GetRegionWeatherOverride_Execute(COMMAND_ARGS) {
	TESRegion* region = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &region) && region && IS_TYPE(region, TESRegion)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			*result = weatherData->bOverride;
			if (IsConsoleMode()) {
				Console_Print("GetRegionWeatherOverride >> %.f", *result);
			}
		}
	}
	return true;
}
bool Cmd_SetRegionWeatherOverride_Execute(COMMAND_ARGS) {
	TESRegion* region = nullptr;
	int bOverride = -1;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &region, &bOverride) && region && IS_TYPE(region, TESRegion)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			weatherData->bOverride = bOverride;
			*result = 1;
		}
	}
	return true;
}
bool Cmd_GetRegionWeatherPriority_Execute(COMMAND_ARGS) {
	TESRegion* region = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &region) && region && IS_TYPE(region, TESRegion)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			*result = weatherData->cPriority;
			if (IsConsoleMode()) {
				Console_Print("GetRegionWeatherPriority >> %.f", *result);
			}
		}
	}
	return true;
}
bool Cmd_SetRegionWeatherPriority_Execute(COMMAND_ARGS) {
	TESRegion* region = nullptr;
	int priority = -1;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &region, &priority) && region && IS_TYPE(region, TESRegion) && priority >= 0 && priority <= 100) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			weatherData->cPriority = priority;
			*result = 1;
		}
	}
	return true;
}
bool Cmd_IsWeatherInRegion_Execute(COMMAND_ARGS) {
	TESRegion* region = nullptr;
	TESWeather* weather = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &region, &weather) && region && IS_TYPE(region, TESRegion) && weather && IS_TYPE(weather, TESWeather)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			ListNode<WeatherEntry>* iter = weatherData->weatherTypes.Head();
			WeatherEntry* weatherType;
			do {
				weatherType = iter->data;
				if (weatherType->weather == weather) {
					*result = 1;
					if (IsConsoleMode())
						Console_Print("The weather is found in Region Data");
					return true;
				}
			} while (iter = iter->next);
			*result = 0;
			if (IsConsoleMode())
				Console_Print("The weather is NOT found in Region Data");
		}
	}
	return true;
}
bool Cmd_RemoveRegionWeather_Execute(COMMAND_ARGS) {
	TESRegion* region = nullptr;
	TESWeather* weather = nullptr;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &region, &weather) && region && IS_TYPE(region, TESRegion) && weather && IS_TYPE(weather, TESWeather)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			ListNode<WeatherEntry>* iter = weatherData->weatherTypes.Head();
			WeatherEntry* weatherType;
			do {
				weatherType = iter->data;
				if (weatherType->weather == weather) {
					iter = iter->RemoveMe();
					*result = 1;
					if (IsConsoleMode())
						Console_Print("The weather is removed from Region Data");
					return true;
				}
			} while (iter = iter->next);
			if (IsConsoleMode())
				Console_Print("The weather is NOT found in Region Data");
		}
	}
	return true;
}
bool Cmd_AddRegionWeather_Execute(COMMAND_ARGS) {
	TESRegion* region = nullptr;
	TESWeather* weather = nullptr;
	uint32_t chance = 0;
	TESGlobal* global = nullptr;
	WeatherEntry* entry;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &region, &weather, &chance, &global) && region && IS_TYPE(region, TESRegion) && weather && IS_TYPE(weather, TESWeather)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			ListNode<WeatherEntry>* iter = weatherData->weatherTypes.Head();
			do {
				if (iter->data && iter->data->weather == weather) return true;
			} while (iter = iter->next);
			entry = BSMemory::malloc<WeatherEntry>();
			entry->chance = chance;
			entry->global = global;
			entry->weather = weather;
			weatherData->weatherTypes.Insert(entry);
			*result = 1;
		}
	}
	return true;
}