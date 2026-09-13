#include "fn_region.h"

TESRegionDataWeather* GetWeatherData(TESRegion* region) {
	if (region->dataEntries->Empty()) return nullptr;
	ListNode<TESRegionData>* iter = region->dataEntries->Head();
	TESRegionData* regData;
	do {
		regData = iter->data;
		if ((*(uint32_t*)regData == 0x1023E18))
			return (TESRegionDataWeather*)regData;
	} while (iter = iter->next);
	return nullptr;
}

TESRegionDataMap* GetMapData(TESRegion* region) {
	if (region->dataEntries->Empty()) return nullptr;
	ListNode<TESRegionData>* iter = region->dataEntries->Head();
	TESRegionData* regData;
	do {
		regData = iter->data;
		if ((*(uint32_t*)regData == 0x1023D28))
			return (TESRegionDataMap*)regData;
	} while (iter = iter->next);
	return nullptr;
}

bool Cmd_GetNthRegionWeatherGlobal_Execute(COMMAND_ARGS) {
	TESRegion* pRegion = nullptr;
	int iIndex = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion, &iIndex) && iIndex > 0 && pRegion && IS_TYPE(pRegion, TESRegion)) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData && !pWeatherData->weatherTypes.IsEmpty()) {
			auto pItem = pWeatherData->weatherTypes.GetAt(iIndex);
			if (pItem && pItem->GetItem() && pItem->GetItem()->uiChance)
				*reinterpret_cast<uint32_t*>(result) = pItem->GetItem()->pChanceVar->GetFormID();
		}
	}
	return true;
}

bool Cmd_GetNthRegionWeatherChance_Execute(COMMAND_ARGS) {
	*result = 0;
	TESRegion* pRegion = nullptr;
	int32_t iIndex = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion, &iIndex) && iIndex > 0 && pRegion && IS_TYPE(pRegion, TESRegion)) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData && !pWeatherData->weatherTypes.IsEmpty()) {
			auto pItem = pWeatherData->weatherTypes.GetAt(iIndex);
			if (pItem && pItem->GetItem())
				*result = pItem->GetItem()->uiChance;
		}
	}
	return true;
}

bool Cmd_GetNthRegionWeatherType_Execute(COMMAND_ARGS) {
	*result = 0;
	TESRegion* pRegion = nullptr;
	int32_t iIndex = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion, &iIndex) && iIndex > 0 && pRegion && IS_TYPE(pRegion, TESRegion)) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData && !pWeatherData->weatherTypes.IsEmpty()) {
			auto pItem = pWeatherData->weatherTypes.GetAt(iIndex);
			if (pItem && pItem->GetItem() && pItem->GetItem()->pWeather)
				*result = pItem->GetItem()->pWeather->GetFormID();
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
	*result = 0;
	TESRegion* pRegion = nullptr;
	NVSEArrayVar* pArray = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion) && pRegion && IS_TYPE(pRegion, TESRegion)) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData) {
			auto pIter = pWeatherData->weatherTypes.GetHead();
			while (pIter && !pIter->IsEmpty()) {
				WeatherEntry* pEntry = pIter->GetItem();
				if (pEntry) {
					g_arrInterface->AppendElement(pArray, NVSEArrayElement(pEntry->pWeather));
					if (IsConsoleMode())
						Console_Print(pEntry->pWeather->GetFormEditorID());
				}
				pIter = pIter->GetNext();
			}
		}
	}
	g_arrInterface->AssignCommandResult(pArray, result);
	return true;
}

bool Cmd_ClearRegionWeathers_Execute(COMMAND_ARGS) {
	*result = 0;
	TESRegion* pRegion = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion) && pRegion && IS_TYPE(pRegion, TESRegion)) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData) {
			pWeatherData->weatherTypes.FlushList();
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
			*result = weatherData->GetPriority();
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
			weatherData->SetPriority(priority);
			*result = 1;
		}
	}
	return true;
}

bool Cmd_IsWeatherInRegion_Execute(COMMAND_ARGS) {
	*result = 0;
	TESRegion* pRegion = nullptr;
	TESWeather* pWeather = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion, &pWeather) && pRegion && IS_TYPE(pRegion, TESRegion) && pWeather && IS_TYPE(pWeather, TESWeather)) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData) {
			auto pIter = pWeatherData->weatherTypes.GetHead();
			while (pIter && !pIter->IsEmpty()) {
				WeatherEntry* pEntry = pIter->GetItem();
				if (pEntry && pEntry->pWeather == pWeather) {
					if (IsConsoleMode())
						Console_Print("The weather is found in Region Data");

					*result = 1;
					return true;
				}

				pIter = pIter->GetNext();
			}
			if (IsConsoleMode())
				Console_Print("The weather is NOT found in Region Data");
		}
	}
	return true;
}

bool Cmd_RemoveRegionWeather_Execute(COMMAND_ARGS) {
	*result = 0;
	TESRegion* pRegion = nullptr;
	TESWeather* pWeather = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion, &pWeather) && pRegion && IS_TYPE(pRegion, TESRegion) && pWeather && IS_TYPE(pWeather, TESWeather)) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData) {
			auto pIter = pWeatherData->weatherTypes.GetHead();
			while (pIter && !pIter->IsEmpty()) {
				WeatherEntry* pEntry = pIter->GetItem();
				if (pEntry && pEntry->pWeather == pWeather) {
					pIter->RemoveHead();
					if (IsConsoleMode())
						Console_Print("The weather is removed from Region Data");
					*result = 1;
					return true;
				}

				pIter = pIter->GetNext();
			}
			if (IsConsoleMode())
				Console_Print("The pWeather is NOT found in Region Data");
		}
	}
	return true;
}

bool Cmd_AddRegionWeather_Execute(COMMAND_ARGS) {
	*result = 0;
	TESRegion* pRegion = nullptr;
	TESWeather* pWeather = nullptr;
	uint32_t uiChance = 0;
	TESGlobal* pChanceVar = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion, &pWeather, &uiChance, &pChanceVar) && pRegion && IS_TYPE(pRegion, TESRegion) && pWeather && IS_TYPE(pWeather, TESWeather)) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData) {
			auto pIter = pWeatherData->weatherTypes.GetHead();
			while (pIter && !pIter->IsEmpty()) {
				WeatherEntry* pEntry = pIter->GetItem();
				if (pEntry && pEntry->pWeather == pWeather)
					return true;

				pIter = pIter->GetNext();
			}

			WeatherEntry* pEntry = BSMemory::malloc<WeatherEntry>();
			pEntry->uiChance = uiChance;
			pEntry->pChanceVar = pChanceVar;
			pEntry->pWeather = pWeather;
			pWeatherData->weatherTypes.AddHead(pEntry);
			*result = 1;
		}
	}
	return true;
}