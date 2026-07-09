#include "fn_region.h"

#include <Bethesda/TESRegion.hpp>
#include <Bethesda/TESRegionDataWeather.hpp>
#include <Bethesda/TESRegionDataMap.hpp>

TESRegionDataWeather* GetWeatherData(TESRegion* apRegion) {
	if (apRegion->pDataList->IsEmpty())
		return nullptr;

	return static_cast<TESRegionDataWeather*>(apRegion->pDataList->Find(REGION_DATA_ID::WEATHER));
}

TESRegionDataMap* GetMapData(TESRegion* apRegion) {
	if (apRegion->pDataList->IsEmpty())
		return nullptr;

	return static_cast<TESRegionDataMap*>(apRegion->pDataList->Find(REGION_DATA_ID::MAP));
}

bool Cmd_GetNthRegionWeatherGlobal_Execute(COMMAND_ARGS) {
	TESRegion* pRegion = nullptr;
	int32_t iIndex = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion, &iIndex) && iIndex > 0 && pRegion && IS_TYPE(pRegion, TESRegion)) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData && !pWeatherData->kWeatherList.IsEmpty()) {
			auto pItem = pWeatherData->kWeatherList.GetAt(iIndex);
			if (pItem && pItem->GetItem() && pItem->GetItem()->uiChance)
				*(uint32_t*)result = pItem->GetItem()->pChanceVar->GetFormID();
		}
	}
	return true;
}

bool Cmd_GetNthRegionWeatherChance_Execute(COMMAND_ARGS) {
	TESRegion* pRegion = nullptr;
	int32_t iIndex = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion, &iIndex) && iIndex > 0 && pRegion && IS_TYPE(pRegion, TESRegion)) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData && !pWeatherData->kWeatherList.IsEmpty()) {
			auto pItem = pWeatherData->kWeatherList.GetAt(iIndex);
			if (pItem && pItem->GetItem())
				*result = pItem->GetItem()->uiChance;
		}
	}
	return true;
}
bool Cmd_GetNthRegionWeatherType_Execute(COMMAND_ARGS) {
	TESRegion* pRegion = nullptr;
	int32_t iIndex = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion, &iIndex) && iIndex > 0 && pRegion && IS_TYPE(pRegion, TESRegion)) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData && !pWeatherData->kWeatherList.IsEmpty()) {
			auto pItem = pWeatherData->kWeatherList.GetAt(iIndex);
			if (pItem && pItem->GetItem() && pItem->GetItem()->pWeather)
				*result = pItem->GetItem()->pWeather->GetFormID();
		}
	}
	return true;
}
bool Cmd_SetRegionMapName_Execute(COMMAND_ARGS) {
	TESRegion* pRegion = nullptr;
	char cName[MAX_PATH];
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion, &cName) && pRegion && IS_TYPE(pRegion, TESRegion)) {
		TESRegionDataMap* pMapData = GetMapData(pRegion);
		if (pMapData) {
			pMapData->SetMapName(cName);
		}
		else {
			pMapData = BSMemory::malloc<TESRegionDataMap>();
			ThisCall(0x4F3CA0, pMapData); // TESRegionDataMap::TESRegionDataMap
			pMapData->SetMapName(cName);
			pRegion->pDataList->Add(pMapData);
		}
		*result = 1;
	}
	return true;
}

bool Cmd_GetRegionMapName_Execute(COMMAND_ARGS) {
	TESRegion* pRegion = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion) && pRegion && IS_TYPE(pRegion, TESRegion)) {
		TESRegionDataMap* pMapData = GetMapData(pRegion);
		if (pMapData)
			g_strInterface->Assign(PASS_COMMAND_ARGS, pMapData->strMapName.c_str());
	}
	return true;
}

bool Cmd_GetRegionWeathers_Execute(COMMAND_ARGS) {
	TESRegion* pRegion = nullptr;
	NVSEArrayVar* pArray = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion) && pRegion && IS_TYPE(pRegion, TESRegion)) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData) {
			auto pIter = pWeatherData->kWeatherList.GetHead();
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
	TESRegion* pRegion = nullptr;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion) && pRegion && IS_TYPE(pRegion, TESRegion)) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData) {
			pWeatherData->kWeatherList.FlushList();
			*result = 1;
		}
	}
	return true;
}

bool Cmd_GetRegionWeatherOverride_Execute(COMMAND_ARGS) {
	TESRegion* pRegion = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion) && pRegion && IS_TYPE(pRegion, TESRegion)) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData) {
			*result = pWeatherData->bOverride;
			if (IsConsoleMode()) {
				Console_Print("GetRegionWeatherOverride >> %.f", *result);
			}
		}
	}
	return true;
}

bool Cmd_SetRegionWeatherOverride_Execute(COMMAND_ARGS) {
	TESRegion* pRegion = nullptr;
	int bOverride = -1;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion, &bOverride) && pRegion && IS_TYPE(pRegion, TESRegion)) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData) {
			pWeatherData->bOverride = bOverride;
			*result = 1;
		}
	}
	return true;
}

bool Cmd_GetRegionWeatherPriority_Execute(COMMAND_ARGS) {
	TESRegion* pRegion = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion) && pRegion && IS_TYPE(pRegion, TESRegion)) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData) {
			*result = pWeatherData->cPriority;
			if (IsConsoleMode()) {
				Console_Print("GetRegionWeatherPriority >> %.f", *result);
			}
		}
	}
	return true;
}

bool Cmd_SetRegionWeatherPriority_Execute(COMMAND_ARGS) {
	TESRegion* pRegion = nullptr;
	int priority = -1;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion, &priority) && pRegion && IS_TYPE(pRegion, TESRegion) && priority >= 0 && priority <= 100) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData) {
			pWeatherData->cPriority = priority;
			*result = 1;
		}
	}
	return true;
}

bool Cmd_IsWeatherInRegion_Execute(COMMAND_ARGS) {
	TESRegion* pRegion = nullptr;
	TESWeather* pWeather = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion, &pWeather) && pRegion && IS_TYPE(pRegion, TESRegion) && pWeather && IS_TYPE(pWeather, TESWeather)) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData) {
			auto pIter = pWeatherData->kWeatherList.GetHead();
			while (pIter && !pIter->IsEmpty()) {
				WeatherEntry* pEntry = pIter->GetItem();
				if (pEntry && pEntry->pWeather == pWeather) {
					*result = 1;
					if (IsConsoleMode())
						Console_Print("The weather is found in Region Data");
					return true;
				}

				pIter = pIter->GetNext();
			}
			*result = 0;
			if (IsConsoleMode())
				Console_Print("The weather is NOT found in Region Data");
		}
	}
	return true;
}

bool Cmd_RemoveRegionWeather_Execute(COMMAND_ARGS) {
	TESRegion* pRegion = nullptr;
	TESWeather* pWeather = nullptr;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion, &pWeather) && pRegion && IS_TYPE(pRegion, TESRegion) && pWeather && IS_TYPE(pWeather, TESWeather)) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData) {
			auto pIter = pWeatherData->kWeatherList.GetHead();
			while (pIter && !pIter->IsEmpty()) {
				WeatherEntry* pEntry = pIter->GetItem();
				if (pEntry && pEntry->pWeather == pWeather) {
					pIter->RemoveHead();
					*result = 1;
					if (IsConsoleMode())
						Console_Print("The weather is removed from Region Data");
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
	TESRegion* pRegion = nullptr;
	TESWeather* pWeather = nullptr;
	uint32_t uiChance = 0;
	TESGlobal* pChanceVar = nullptr;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion, &pWeather, &uiChance, &pChanceVar) && pRegion && IS_TYPE(pRegion, TESRegion) && pWeather && IS_TYPE(pWeather, TESWeather)) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData) {
			auto pIter = pWeatherData->kWeatherList.GetHead();
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
			pWeatherData->kWeatherList.AddHead(pEntry);
			*result = 1;
		}
	}
	return true;
}