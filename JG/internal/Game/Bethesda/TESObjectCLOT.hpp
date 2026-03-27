#pragma once

#include "BGSDestructibleObjectForm.hpp"
#include "BGSEquipType.hpp"
#include "TESBipedModelForm.hpp"
#include "TESBoundObject.hpp"
#include "TESEnchantableForm.hpp"
#include "TESFullName.hpp"
#include "TESScriptableForm.hpp"
#include "TESValueForm.hpp"
#include "TESWeightForm.hpp"

class TESObjectCLOT : public TESBoundObject, public TESFullName, public TESScriptableForm, public TESEnchantableForm, public TESValueForm, public TESWeightForm, public TESBipedModelForm, public BGSDestructibleObjectForm, public BGSEquipType {
public:
	TESObjectCLOT();
	~TESObjectCLOT();

	TESFORM_TYPE(TESObjectCLOT);
};

ASSERT_SIZE(TESObjectCLOT, 0x154);