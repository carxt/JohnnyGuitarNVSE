#pragma once
// Region functions
DEFINE_COMMAND_PLUGIN(GetRegionWeatherOverride, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetRegionWeatherOverride, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetRegionWeatherPriority, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetRegionWeatherPriority, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(IsWeatherInRegion, , 0, 2, kParamsJohnny_TwoForms);
DEFINE_COMMAND_PLUGIN(RemoveRegionWeather, , 0, 2, kParamsJohnny_TwoForms);
DEFINE_COMMAND_PLUGIN(AddRegionWeather, , 0, 4, kParams_Johnny_OneForm_OneWeatherID_OneInt_OneOptionalGlobal);
DEFINE_COMMAND_PLUGIN(GetRegionWeathers, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(ClearRegionWeathers, , 0, 1, kParams_OneForm);

bool Cmd_GetRegionWeathers_Execute(COMMAND_ARGS) {
	TESRegion* region = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &region) && IS_TYPE(region, TESRegion)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			NVSEArrayVar* weatherArr = ArrIfc->CreateArray(NULL, 0, scriptObj);
			ListNode<WeatherEntry>* iter = weatherData->weatherTypes.Head();
			do
			{
				if (iter->data) {
					ArrIfc->AppendElement(weatherArr, NVSEArrayElement(iter->data->weather));
					if (IsConsoleMode())
						Console_Print(iter->data->weather->GetName());
				}
			} while (iter = iter->next);
			if (ArrIfc->GetArraySize(weatherArr)) ArrIfc->AssignCommandResult(weatherArr, result);
		}
	}
	return true;
}
bool Cmd_ClearRegionWeathers_Execute(COMMAND_ARGS) {
	TESRegion* region = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &region) && IS_TYPE(region, TESRegion)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			ListNode<WeatherEntry>* headNode = weatherData->weatherTypes.Head(), * iter = headNode->next;
			while (iter)
			{
				GameHeapFree(iter->data);
				iter = iter->RemoveMe();
			}
			if (headNode->next) {
				headNode->RemoveNext();
			}
			else {
				GameHeapFree(headNode->data);
				headNode->RemoveMe();
			}
		}
	}
	return true;
}
bool Cmd_GetRegionWeatherOverride_Execute(COMMAND_ARGS) {
	TESRegion* region = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &region) && IS_TYPE(region, TESRegion)) {
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
	TESRegion* region = NULL;
	int bOverride = -1;
	if (ExtractArgs(EXTRACT_ARGS, &region, &bOverride) && IS_TYPE(region, TESRegion)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData)
			weatherData->bOverride = bOverride;
	}
	return true;
}
bool Cmd_GetRegionWeatherPriority_Execute(COMMAND_ARGS) {
	TESRegion* region = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &region) && IS_TYPE(region, TESRegion)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			*result = weatherData->priority;
			if (IsConsoleMode()) {
				Console_Print("GetRegionWeatherPriority >> %.f", *result);
			}
		}
	}
	return true;
}
bool Cmd_SetRegionWeatherPriority_Execute(COMMAND_ARGS) {
	TESRegion* region = NULL;
	int priority = -1;
	if (ExtractArgs(EXTRACT_ARGS, &region, &priority) && IS_TYPE(region, TESRegion) && priority >= 0 && priority <= 100) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData)
			weatherData->priority = priority;
	}
	return true;
}
bool Cmd_IsWeatherInRegion_Execute(COMMAND_ARGS) {
	TESRegion* region = NULL;
	TESWeather* weather = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &region, &weather) && IS_TYPE(region, TESRegion) && IS_TYPE(weather, TESWeather)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			ListNode<WeatherEntry>* iter = weatherData->weatherTypes.Head();
			WeatherEntry* weatherType;
			do
			{
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
	TESRegion* region = NULL;
	TESWeather* weather = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &region, &weather) && IS_TYPE(region, TESRegion) && IS_TYPE(weather, TESWeather)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			ListNode<WeatherEntry>* iter = weatherData->weatherTypes.Head();
			WeatherEntry* weatherType;
			do
			{
				weatherType = iter->data;
				if (weatherType->weather == weather) {
					iter = iter->RemoveMe();
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
	TESRegion* region = NULL;
	TESWeather* weather = NULL;
	UInt32 chance = 0;
	TESGlobal* global = NULL;
	WeatherEntry* entry;
	if (ExtractArgs(EXTRACT_ARGS, &region, &weather, &chance, &global) && IS_TYPE(region, TESRegion) && IS_TYPE(weather, TESWeather)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			ListNode<WeatherEntry>* iter = weatherData->weatherTypes.Head();
			do
			{
				if (iter->data)
					if (iter->data->weather == weather) return true;
			} while (iter = iter->next);
			entry = (WeatherEntry*)GameHeapAlloc(sizeof(WeatherEntry));
			entry->chance = chance;
			entry->global = global;
			entry->weather = weather;
			weatherData->weatherTypes.Insert(entry);
		}
	}
	return true;
}