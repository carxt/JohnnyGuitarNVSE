#pragma once

#include "TESForm.hpp"
#include "BGSPreloadable.hpp"

class BGSDebrisData;
class NiPoint3;
class TESObjectCELL;

class BGSDebris : public TESForm, public BGSPreloadable {
public:
	BGSDebris();
	~BGSDebris();

	BSSimpleList<BGSDebrisData*> kDatas;

	TESFORM_TYPE(BGSDebris);

	void SpawnDebris(TESObjectCELL* apCell, const NiPoint3& arLocation, uint32_t auiParticleCount, float afScale);
};

ASSERT_SIZE(BGSDebris, 0x24);