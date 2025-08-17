#pragma once

#include "BSStringT.hpp"

class TESIdleForm;
class TESSound;

class DialogueResponse {
public:
	BSString		strResponseText;
	uint32_t		uiEmotionType;
	uint32_t		uiEmotionValue;
	BSString		strVoiceFilePath;
	TESIdleForm*	pSpeakerAnimation;
	TESIdleForm*	pListenerAnimation;
	TESSound*		pSound;
	uint8_t			ucFlags;
	uint32_t		uiResponseNumber;
};

ASSERT_SIZE(DialogueResponse, 0x2C);