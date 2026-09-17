#include "fn_region.h"
#include "Bethesda/TESRegionDataManager.hpp"
#include "Bethesda/TESDataHandler.hpp"
#include "Bethesda/Interface.hpp"

TESRegionDataWeather* __fastcall GetWeatherData(const TESRegion* apRegion) {
	TESRegionData* pData = apRegion->GetRegionDataList()->Find(REGION_DATA_ID::WEATHER);
	if (pData)
		return static_cast<TESRegionDataWeather*>(pData);
	return nullptr;
}

TESRegionDataMap* __fastcall GetMapData(const TESRegion* apRegion) {
	TESRegionData* pData = apRegion->GetRegionDataList()->Find(REGION_DATA_ID::MAP);
	if (pData)
		return static_cast<TESRegionDataMap*>(pData);
	return nullptr;
}

bool Cmd_GetNthRegionWeatherGlobal_Execute(COMMAND_ARGS) {
	TESRegion* pRegion = nullptr;
	int iIndex = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion, &iIndex) && iIndex > 0 && pRegion && IS_TYPE(pRegion, TESRegion)) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData && !pWeatherData->kWeatherList.IsEmpty()) {
			auto pItem = pWeatherData->kWeatherList.GetAt(iIndex);
			if (pItem && pItem->GetItem() && pItem->GetItem()->uiChance)
				*reinterpret_cast<FormID*>(result) = pItem->GetItem()->pChanceVar->GetFormID();
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
		if (pWeatherData && !pWeatherData->kWeatherList.IsEmpty()) {
			auto pItem = pWeatherData->kWeatherList.GetAt(iIndex);
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
		if (pWeatherData && !pWeatherData->kWeatherList.IsEmpty()) {
			auto pItem = pWeatherData->kWeatherList.GetAt(iIndex);
			if (pItem && pItem->GetItem() && pItem->GetItem()->pWeather)
				*result = pItem->GetItem()->pWeather->GetFormID();
		}
	}
	return true;
}

bool Cmd_SetRegionMapName_Execute(COMMAND_ARGS) {
	*result = 0;
	TESRegion* pRegion = nullptr;
	char cName[MAX_PATH];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion, &cName) && pRegion && IS_TYPE(pRegion, TESRegion)) {
		TESRegionDataMap* pMapData = GetMapData(pRegion);
		if (pMapData) {
			pMapData->SetMapName(cName);
		}
		else {
			pMapData = static_cast<TESRegionDataMap*>(TESDataHandler::GetSingleton()->GetRegionDataManager()->ConstructRegionData(REGION_DATA_ID::MAP));
			pMapData->SetMapName(cName);
			pRegion->GetRegionDataList()->AddHead(pMapData);
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
			g_strInterface->Assign(PASS_COMMAND_ARGS, pMapData->GetMapName());
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
			auto pIter = pWeatherData->kWeatherList.GetHead();
			while (pIter && !pIter->IsEmpty()) {
				WeatherEntry* pEntry = pIter->GetItem();
				if (pEntry) {
					g_arrInterface->AppendElement(pArray, NVSEArrayElement(pEntry->pWeather));
					if (Script::GetConsoleOuput())
						Interface::PrintLine(pEntry->pWeather->GetFormEditorID());
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
			if (Script::GetConsoleOuput()) {
				Interface::PrintLine("GetRegionWeatherOverride >> %.f", *result);
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
		TESRegionDataWeather* weatherData = GetWeatherData(pRegion);
		if (weatherData) {
			weatherData->bOverride = bOverride;
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
			*result = pWeatherData->GetPriority();
			if (Script::GetConsoleOuput()) {
				Interface::PrintLine("GetRegionWeatherPriority >> %.f", *result);
			}
		}
	}
	return true;
}

bool Cmd_SetRegionWeatherPriority_Execute(COMMAND_ARGS) {
	TESRegion* pRegion = nullptr;
	int32_t iPriority = -1;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRegion, &iPriority) && pRegion && IS_TYPE(pRegion, TESRegion) && iPriority >= 0 && iPriority <= 100) {
		TESRegionDataWeather* pWeatherData = GetWeatherData(pRegion);
		if (pWeatherData) {
			pWeatherData->SetPriority(iPriority);
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
			auto pIter = pWeatherData->kWeatherList.GetHead();
			while (pIter && !pIter->IsEmpty()) {
				WeatherEntry* pEntry = pIter->GetItem();
				if (pEntry && pEntry->pWeather == pWeather) {
					if (Script::GetConsoleOuput())
						Interface::PrintLine("The weather is found in Region Data");

					*result = 1;
					return true;
				}

				pIter = pIter->GetNext();
			}
			if (Script::GetConsoleOuput())
				Interface::PrintLine("The weather is NOT found in Region Data");
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
			auto pIter = pWeatherData->kWeatherList.GetHead();
			while (pIter && !pIter->IsEmpty()) {
				WeatherEntry* pEntry = pIter->GetItem();
				if (pEntry && pEntry->pWeather == pWeather) {
					pIter->RemoveHead();
					if (Script::GetConsoleOuput())
						Interface::PrintLine("The weather is removed from Region Data");
					*result = 1;
					return true;
				}

				pIter = pIter->GetNext();
			}
			if (Script::GetConsoleOuput())
				Interface::PrintLine("The pWeather is NOT found in Region Data");
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