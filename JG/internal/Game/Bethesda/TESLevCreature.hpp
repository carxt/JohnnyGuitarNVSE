#pragma once

#include "TESBoundObject.hpp"
#include "TESModelTextureSwap.hpp"
#include "TESLeveledList.hpp"

class TESCreature;

class TESLevCreature : public TESBoundObject, public TESLeveledList, public TESModelTextureSwap {
public:
	TESLevCreature();
	~TESLevCreature();

	TESCreature* pTemplate;

	TESFORM_TYPE(TESLevCreature);
};

#ifdef GAME
ASSERT_SIZE(TESLevCreature, 0x70);
#else
ASSERT_SIZE(TESLevCreature, 0x9C);
#endif