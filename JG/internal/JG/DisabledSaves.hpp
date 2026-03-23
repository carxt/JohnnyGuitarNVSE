#pragma once

namespace DisabledSaves {
	void Init();
	void Install();
	void Reset();
	void Toggle(uint8_t modId, bool toggle);
}