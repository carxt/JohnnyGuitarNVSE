#pragma once

namespace DisabledSaves {
	void Init();
	void Install();
	void Reset();
	void Toggle(uint8_t aucMod, bool abToggle, uint32_t auiTypeFlags);
}