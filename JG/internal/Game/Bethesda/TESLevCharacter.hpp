#pragma once

#include "TESBoundAnimObject.hpp"
#include "TESModelTextureSwap.hpp"
#include "TESLeveledList.hpp"

class TESNPC;

class TESLevCharacter : public TESBoundAnimObject, public TESLeveledList, public TESModelTextureSwap {
public:
	TESLevCharacter();
	~TESLevCharacter();

	TESNPC* pTemplate;

	TESFORM_TYPE(TESLevCharacter);
};

#ifdef GAME
ASSERT_SIZE(TESLevCharacter, 0x70);
#else
ASSERT_SIZE(TESLevCharacter, 0x9C);
#endif