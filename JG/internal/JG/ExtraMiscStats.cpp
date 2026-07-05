#include "ExtraMiscStats.hpp"
#include "GameUI.h"
#include "Bethesda/Setting.hpp"

namespace ExtraMiscStats {
	std::unordered_map<std::string, int> miscStatMap;
	std::unordered_set<std::string> availableMiscStats;

	uint8_t recalculateStatFilters = 0;

	Setting** g_miscStatData = (Setting**)0x11C6D50;

	constexpr size_t maxMiscStatCount = UINT16_MAX;

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

	void Reset() {
		miscStatMap.clear();
		for (auto& element : availableMiscStats) {
			miscStatMap[element] = 0;
			UpdateMiscStatList(element.c_str(), 0);
		}

	}

	void Update() {
		if (StatsMenu::Get() && InterfaceManager::GetSingleton() && Menu::IsMenuVisible(Interface::Menus::Stats) && recalculateStatFilters) {
			recalculateStatFilters = false;
			StatsMenu::Get()->miscStatIDList.Filter(ShouldHideStat);

		}
	}

	void ForceUpdate() {
		if (StatsMenu::Get()) {
			StatsMenu::Get()->miscStatIDList.Filter(ShouldHideStat);
		}
	}

	void Install() {
		// Get/ModExtraMiscStat
		HookUtils::SafeWrite32(0x7DDAB1, uint32_t(MiscStatRefreshHook));
	}

	bool InitStat(const char* name) {

		std::string sName = name;
		if (availableMiscStats.size() > maxMiscStatCount) {
			// lmao
			TerminateProcess(GetCurrentProcess(), 0xE);
		}
		if (bool(availableMiscStats.count(sName))) return false;
		availableMiscStats.emplace(sName);
		miscStatMap[sName] = 0;
		return true;
	}

	bool ModStat(const char* name, int mod) {
		int value = 0;
		std::string sName = name;
		if (!bool(availableMiscStats.count(sName))) return false;
		auto it = miscStatMap.find(sName);
		if (it != miscStatMap.end()) {
			it->second += mod;
			value = it->second;
		}
		else {
			miscStatMap[sName] = mod;
			value = mod;
		}
		// creating/updating menu entry
		UpdateMiscStatList(name, value);
		return true;
	}

	void SetStat(const char* name, int value)
	{
		std::string sName = std::string(name);
		auto statIter = miscStatMap.find(sName);
		if (statIter != miscStatMap.end()) {
			miscStatMap[sName] = value;
			UpdateMiscStatList(name, value);
		}
	}

	int GetStat(const char* name) {
		std::string sName = name;
		if (!availableMiscStats.count(sName)) return -1;
		auto it = miscStatMap.find(sName);
		if (it != miscStatMap.end()) return it->second;
		return 0;
	}

	bool HasDataToSave()
	{
		return !miscStatMap.empty();
	}

	void SerializeData(WriteFunc writeFunc) {
		uint16_t mapLen = static_cast<uint16_t>(miscStatMap.size());
		writeFunc(&mapLen, sizeof(uint16_t));

		for (auto& it : miscStatMap) {
			uint16_t len = static_cast<uint16_t>(it.first.length());
			writeFunc(&len, sizeof(uint16_t));
			writeFunc(it.first.c_str(), it.first.length());
			writeFunc(&it.second, sizeof(int));
		}
	}

	void DeserializeData(ReadFunc readFunc) {
		uint16_t mapLen = 0;
		readFunc(&mapLen, sizeof(uint16_t));

		if (mapLen > 0) {
			char buffer[MAX_PATH] = { 0 };
			for (int i = 0; i < mapLen; i++) {
				uint16_t len = 0;
				readFunc(&len, sizeof(uint16_t));
				readFunc(buffer, len);
				buffer[len] = 0;
				int value = 0;
				readFunc(&value, sizeof(int));
				SetStat(buffer, value);
			}
		}
		ForceUpdate();
	}
};