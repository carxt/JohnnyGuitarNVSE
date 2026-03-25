#pragma once
#include <unordered_map>
#include "JG\JGSetList.hpp"

namespace BarterFilter {

	void Install();
	void Reset();
	void Add(uint32_t item, uint32_t flags, uint32_t vendor);
	void Remove(uint32_t item, uint32_t flags, uint32_t vendor);
	uint32_t IsHidden(uint32_t item);
}