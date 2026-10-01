#pragma once

class CharacterProgressionData {
public:
	bool		bReadyToLevelUp;
	int32_t		iNextThreshold;
	bool		bIgnoreCallback;
};

ASSERT_SIZE(CharacterProgressionData, 0xC);

class CharacterProgression {
public:
	CharacterProgressionData* pData;
};

ASSERT_SIZE(CharacterProgression, 0x4);