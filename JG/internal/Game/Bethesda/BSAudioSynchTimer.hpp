#pragma once

class BSAudioSynchTimer {
public:
	BSAudioSynchTimer();
	~BSAudioSynchTimer();
	
	struct ALIGN4 _TickFlags {
		enum Flags : uint32_t {
			PAUSED = 1u << 0,
		};

		bool bPaused : 1;
	};

	uint32_t				uiMilliseconds;
	uint32_t				uiLastUpdateTime;
	Bitfield<_TickFlags>	uiFlags;
};

ASSERT_SIZE(BSAudioSynchTimer, 0xC);