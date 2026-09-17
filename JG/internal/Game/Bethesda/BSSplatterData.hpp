#pragma once

struct BSSplatterData {
	float		fAge;
	float		fDuration;
	float		fAlpha;
	uint32_t	uiCount;
};

ASSERT_SIZE(BSSplatterData, 0x10);