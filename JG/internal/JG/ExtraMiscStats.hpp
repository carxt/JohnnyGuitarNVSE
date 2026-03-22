#pragma once
#include <unordered_map>
#include <unordered_set>

namespace ExtraMiscStats {
	extern std::unordered_map<std::string, int> miscStatMap;
	extern std::unordered_set<std::string> availableMiscStats;
	extern uint8_t recalculateStatFilters;
	void Reset();
	void UpdateMiscStatList(const char* name, int value);
	bool __cdecl ShouldHideStat(uint32_t* id);

	void Install();
	void Update();
}