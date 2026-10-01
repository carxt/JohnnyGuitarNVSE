#pragma once

#include "TESForm.hpp"
#include "BGSPreloadable.hpp"

class BGSImpactData;
class ImpactSwap;

class BGSImpactDataSet : public TESForm, public BGSPreloadable {
public:
	BGSImpactDataSet();
	~BGSImpactDataSet();

	BGSImpactData* pImpactDatas[IMPACT_MATERIAL_TYPE::COUNT];

	TESFORM_TYPE(BGSImpactDataSet);

#ifdef GAME
	BGSImpactData* GetImpactData(IMPACT_MATERIAL_TYPE aeType) const;

	BGSImpactData* GetImpactData(HK_MATERIAL_TYPE aeHavokType) const;

	static void ApplyImpactSwap(ImpactSwap* apSwap);

	static IMPACT_MATERIAL_TYPE GetImpactMaterialType(HK_MATERIAL_TYPE aeHavokMaterial);
#endif

	static BGSImpactDataSet* GetDefaultImpactDataSet();

	static const char* GetImpactMaterialName(IMPACT_MATERIAL_TYPE aeType);

protected:
#ifdef GAME
	static constexpr AddressPtr<BGSImpactDataSet*, 0x11CA830> pDefaultImpactDataSet;
	static constexpr AddressPtr<const char*, 0x118C4A0, IMPACT_MATERIAL_TYPE::COUNT> pImpactMaterialString;
#else
	static constexpr AddressPtr<BGSImpactDataSet*, 0xED9674> pDefaultImpactDataSet;
	static constexpr AddressPtr<const char*, 0xE9B8BC, IMPACT_MATERIAL_TYPE::COUNT> pImpactMaterialString;
#endif
};

#ifdef GAME
ASSERT_SIZE(BGSImpactDataSet, 0x4C);
#else
ASSERT_SIZE(BGSImpactDataSet, 0x60);
#endif