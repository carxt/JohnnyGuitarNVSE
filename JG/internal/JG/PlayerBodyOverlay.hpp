#pragma once

#include <cstdint>

namespace PlayerBodyOverlay {

	void Install();
	void Reset();
	int32_t SetEnabled(bool abEnable, int32_t aiDisableSuppressFrames);
	bool IsEnabled();
	uint32_t SetCullParts(int32_t aiMode, uint32_t auiPartBits);
	uint32_t GetCullPartBits();
	uint32_t BuildPartBits(const int32_t* apParts, uint32_t auiCount);
}
