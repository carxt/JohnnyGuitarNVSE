#pragma once

#include "TESBoundObject.hpp"
#include "TESFullName.hpp"
#include "TESModelTextureSwap.hpp"
#include "TESIcon.hpp"
#include "TESScriptableForm.hpp"
#include "TESValueForm.hpp"
#include "TESWeightForm.hpp"
#include "BGSDestructibleObjectForm.hpp"
#include "BGSMessageIcon.hpp"
#include "BGSPickupPutdownSounds.hpp"

class TESObjectMISC : public TESBoundObject, public TESFullName, public TESModelTextureSwap, public TESIcon,
						public TESScriptableForm, public TESValueForm, public TESWeightForm, public BGSDestructibleObjectForm,
							public BGSMessageIcon, public BGSPickupPutdownSounds {
public:
	TESObjectMISC();
	~TESObjectMISC();

	TESSound* pLoopingSound;

	TESFORM_TYPE(TESObjectMISC);

	TESSound* GetLoopingSound() const;
	void SetLoopingSound(TESSound* apSound);
};

ASSERT_SIZE(TESObjectMISC, 0xAC);