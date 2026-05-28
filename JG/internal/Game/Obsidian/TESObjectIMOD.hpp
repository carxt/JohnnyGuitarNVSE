#pragma once

#include "Bethesda/BGSDestructibleObjectForm.hpp"
#include "Bethesda/BGSMessageIcon.hpp"
#include "Bethesda/BGSPickupPutdownSounds.hpp"
#include "Bethesda/TESBoundObject.hpp"
#include "Bethesda/TESDescription.hpp"
#include "Bethesda/TESFullName.hpp"
#include "Bethesda/TESIcon.hpp"
#include "Bethesda/TESModelTextureSwap.hpp"
#include "Bethesda/TESScriptableForm.hpp"
#include "Bethesda/TESValueForm.hpp"
#include "Bethesda/TESWeightForm.hpp"

class TESObjectIMOD : public TESBoundObject, public TESFullName, public TESModelTextureSwap, public TESIcon, public TESScriptableForm, public TESDescription,
	public TESValueForm, public TESWeightForm, public BGSDestructibleObjectForm, public BGSMessageIcon, public BGSPickupPutdownSounds {
public:
	TESObjectIMOD();
	~TESObjectIMOD();

	TESFORM_TYPE(TESObjectIMOD);
};

ASSERT_SIZE(TESObjectIMOD, 0xB0);