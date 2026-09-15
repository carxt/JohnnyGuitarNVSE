#pragma once

// Tweaks gets rid of debug data, as it's unused and just wastes memory
#if !USE_MODDED_CHANGES
#include "BSDebugSoundInfo.hpp"
#endif

class BSSoundInfo {
public:
	uint32_t			uiID;
	float				fFrequency;
	float				fVolume;
	Bitfield32			uiAudioFlags;
	uint32_t			uiDuration;
	bool				bIsPlaying;
#if !USE_MODDED_CHANGES
	BSDebugSoundInfo	kDebugData;
#endif
};

#if USE_MODDED_CHANGES
ASSERT_SIZE(BSSoundInfo, 0x18);
#else
ASSERT_SIZE(BSSoundInfo, 0x254);
#endif