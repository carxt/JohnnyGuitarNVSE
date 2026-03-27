#pragma once

#include "Bethesda/TESBoundObject.hpp"
#include "Bethesda/TESModelTextureSwap.hpp"
#include "Bethesda/BGSMessageIcon.hpp"
#include "Bethesda/TESValueForm.hpp"
#include "Bethesda/TESScriptableForm.hpp"
#include "Bethesda/BGSPickupPutdownSounds.hpp"

class TESCaravanCard : public TESBoundObject, public TESFullName, public TESModelTextureSwap, public TESIcon, public BGSMessageIcon, public TESValueForm, public TESScriptableForm, public BGSPickupPutdownSounds {
public:
	TESCaravanCard();
	~TESCaravanCard();

	struct Data {
		uint32_t	uiCardSuit;
		uint32_t	uiCardValue;
	};

	bool		bIsActive;
	TESTexture	kFace;
	TESTexture	kBack;
	Data		kData;

	TESFORM_TYPE(TESCaravanCard);
};

ASSERT_SIZE(TESCaravanCard, 0xBC);