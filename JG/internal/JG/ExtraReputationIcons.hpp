#pragma once
#include <unordered_map>

namespace ExtraReputationIcons {
	extern std::unordered_map <uint32_t, std::vector<const char*>> factionRepIcons;
	void Install();
}