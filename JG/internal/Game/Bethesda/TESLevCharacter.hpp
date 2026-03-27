#pragma once

#include "TESBoundObject.hpp"
#include "TESModelTextureSwap.hpp"
#include "TESLeveledList.hpp"

class TESActorBase;

class TESLevCharacter : public TESBoundObject, public TESLeveledList, public TESModelTextureSwap {
public:
	TESLevCharacter();
	~TESLevCharacter();

	TESActorBase* pTemplate;

	TESFORM_TYPE(TESLevCharacter);
};

ASSERT_SIZE(TESLevCharacter, 0x70);