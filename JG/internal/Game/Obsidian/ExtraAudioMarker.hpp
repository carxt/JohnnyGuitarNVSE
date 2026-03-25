#pragma once

#include "Bethesda/BSExtraData.hpp"
#include "AudioMarkerData.hpp"

class ExtraAudioMarker : public BSExtraData {
public:
	ExtraAudioMarker();
	~ExtraAudioMarker();

	AudioMarkerData* pData;

	BSEXTRA_TYPE(ExtraAudioMarker);
};

ASSERT_SIZE(ExtraAudioMarker, 0x10);