#pragma once
#include <unordered_map>

namespace ExtraReputationIcons {
	void Install();
	void Set(uint32_t formID, uint32_t tierID, const char* path);
	void Dump();
}