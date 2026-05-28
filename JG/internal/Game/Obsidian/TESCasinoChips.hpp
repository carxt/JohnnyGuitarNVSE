#pragma once

#include "Bethesda/BGSDestructibleObjectForm.hpp"
#include "Bethesda/BGSMessageIcon.hpp"
#include "Bethesda/BGSPickupPutdownSounds.hpp"
#include "Bethesda/TESBoundObject.hpp"
#include "Bethesda/TESFullName.hpp"
#include "Bethesda/TESModelTextureSwap.hpp"
#include "Bethesda/TESValueForm.hpp"

class TESCasinoChips : public TESBoundObject, public TESFullName, public TESModelTextureSwap, public TESIcon, 
	public BGSMessageIcon, public TESValueForm, public BGSDestructibleObjectForm, public BGSPickupPutdownSounds {
public:
	TESCasinoChips();
	~TESCasinoChips();

	BSString	strDesc;

	TESFORM_TYPE(TESCasinoChips);
};

ASSERT_SIZE(TESCasinoChips, 0x9C);