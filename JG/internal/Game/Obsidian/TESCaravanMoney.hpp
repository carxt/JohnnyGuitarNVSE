#pragma once

#include "Bethesda/TESBoundObject.hpp"
#include "Bethesda/TESModelTextureSwap.hpp"
#include "Bethesda/BGSMessageIcon.hpp"
#include "Bethesda/TESValueForm.hpp"
#include "Bethesda/TESFullName.hpp"
#include "Bethesda/BGSPickupPutdownSounds.hpp"

class TESCaravanMoney : public TESBoundObject, public TESFullName, public TESModelTextureSwap, public TESIcon, public BGSMessageIcon, public TESValueForm, public BGSPickupPutdownSounds {
public:
	TESCaravanMoney();
	~TESCaravanMoney();

	TESModelTextureSwap kAnteModels[2];

	TESFORM_TYPE(TESCaravanMoney);
};

ASSERT_SIZE(TESCaravanMoney, 0xCC);