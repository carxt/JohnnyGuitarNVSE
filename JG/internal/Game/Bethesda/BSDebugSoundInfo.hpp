#pragma once

#include "Gamebryo/NiPoint3.hpp"

struct BSDebugSoundInfo {
	char*		pName;
	char		cName[260];
	char*		pFileName;
	char		cFileName[260];
	float		fRadiusMin;
	float		fRadiusMax;
	NiPoint3	kLocation;
	uint32_t	uiStateFlags;
	float		fBeginTime;
	float		fEndTime;
	uint32_t	uiStaticAttenuation;
	uint32_t	uiSystemAttenuation;
	uint32_t	uiDistanceAttenuation;
};

ASSERT_SIZE(BSDebugSoundInfo, 0x23C);
