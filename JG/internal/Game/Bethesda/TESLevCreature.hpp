#pragma once

#include "TESBoundObject.hpp"
#include "TESModelTextureSwap.hpp"
#include "TESLeveledList.hpp"

class TESActorBase;

class TESLevCreature : public TESBoundObject, public TESLeveledList, public TESModelTextureSwap {
public:
	TESLevCreature();
	~TESLevCreature();

	TESActorBase* pTemplate;

	TESFORM_TYPE(TESLevCreature);
};

ASSERT_SIZE(TESLevCreature, 0x70);