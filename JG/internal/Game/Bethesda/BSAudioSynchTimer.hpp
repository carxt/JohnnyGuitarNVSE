#pragma once

class BSAudioSynchTimer {
public:
	struct ALIGN4 _Flags {
		enum Flags : uint32_t {
			PAUSED = 1u << 0,
		};

		bool bPaused : 1;
	};
	using Flags = _Flags::Flags;

	uint32_t			uiTime;	// In ms
	uint32_t			uiLastUpdateTime;
	Bitfield<_Flags>	uiFlags;

	uint32_t GetSynchTime() const;
};

ASSERT_SIZE(BSAudioSynchTimer, 0xC);