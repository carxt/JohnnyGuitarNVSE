#pragma once

#include "BSExtraData.hpp"
#include "BSSimpleList.hpp"

class TESObjectREFR;

class ReflectedRefData {
public:
  TESObjectREFR*	pReference;
  Bitfield32 		uiEffectFlags;
};

class ExtraReflectedRefs : public BSExtraData {
public:
	ExtraReflectedRefs();
	~ExtraReflectedRefs();

	BSSimpleList<ReflectedRefData*> kReflectedRefs;

	BSEXTRA_TYPE(ExtraReflectedRefs);
};

ASSERT_SIZE(ExtraReflectedRefs, 0x14);