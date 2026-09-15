#pragma once

#include "BGSPerkEntry.hpp"

class TESQuest;

class BGSQuestPerkEntry : public BGSPerkEntry {
public:
	BGSQuestPerkEntry();
	~BGSQuestPerkEntry();

	struct Data {
		TESQuest*	pQuest;
		uint8_t		ucQuestStage;
	};

	Data kData;
};

ASSERT_SIZE(BGSQuestPerkEntry, 0x10);