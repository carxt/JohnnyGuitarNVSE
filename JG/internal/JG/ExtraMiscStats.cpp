#include "ExtraMiscStats.hpp"
#include "GameUI.h"
#include "Bethesda/Setting.hpp"

namespace ExtraMiscStats {
	std::unordered_map<std::string, int> miscStatMap;
	std::unordered_set<std::string> availableMiscStats;

	uint8_t recalculateStatFilters = 0;

	Setting** g_miscStatData = (Setting**)0x11C6D50;

	void __cdecl MiscStatRefreshHook(Tile* tile, int id) {
		int value = 0;
		if (id < 43) {
			value = g_miscStatData[id]->Int();
		}
		else {
			std::string sName = tile->name.pString;
			auto it = miscStatMap.find(sName);
			if (it != miscStatMap.end()) {
				value = it->second;
			}
		}

		tile->SetFloat(kTileValue_user1, (float)value, 1);
	}
	bool __cdecl ShouldHideStat(uint32_t* id) {
		if ((uint32_t)id >= 43) {
			Tile* tile = StatsMenu::Get()->miscStatIDList.GetTileFromItem(&id);
			std::string sName = tile->name.c_str();
			if (miscStatMap.find(sName) == miscStatMap.end()) return true;
		}
		return false;
	}
	void UpdateMiscStatList(const char* name, int value) {
		Tile* tile = nullptr;
		auto iter = StatsMenu::Get()->miscStatIDList.GetHead();
		do
		{
			if (iter->GetItem() && iter->GetItem()->tile && !strcmp(iter->GetItem()->tile->name.c_str(), name)) {
				tile = iter->GetItem()->tile;
				break;
			}
		} while (iter = iter->GetNext());
		if (!tile) {
			tile = ThisCall<Tile*>(0x7E1190, &StatsMenu::Get()->miscStatIDList, StatsMenu::Get()->miscStatIDList.itemCount, 0, 0, 0);
			tile->SetString(kTileValue_string, name, 1);
			tile->name.Set(name);
			recalculateStatFilters = true;
		}
		else if (auto listIdxTileVal = tile->GetValue(kTileValue_listindex)) {
			if (listIdxTileVal && listIdxTileVal->num < 0) {
				recalculateStatFilters = true;
			}
		}
		tile->SetFloat(kTileValue_user1, (float)value, 1);
	}

	void ResetMap() {
		miscStatMap.clear();
		for (auto& element : availableMiscStats) {
			miscStatMap[element] = 0;
			UpdateMiscStatList(element.c_str(), 0);
		}

	}

	void Hook() {
		// Get/ModExtraMiscStat
		SafeWrite32(0x7DDAB1, uint32_t(MiscStatRefreshHook));
	}
};