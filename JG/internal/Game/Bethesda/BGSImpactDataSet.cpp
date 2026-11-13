#include "BGSImpactDataSet.hpp"

#ifdef GAME
// GAME - 0x58E9D0
BGSImpactData* BGSImpactDataSet::GetImpactData(IMPACT_MATERIAL_TYPE aeType) const {
    return ThisCall<BGSImpactData*>(0x58E9D0, this, aeType);
}

// GAME - 0x4FB7A0
BGSImpactData* BGSImpactDataSet::GetImpactData(HK_MATERIAL_TYPE aeHavokType) const {
    return ThisCall<BGSImpactData*>(0x4FB7A0, this, aeHavokType);
}

// GAME - 0x58EEB0
void BGSImpactDataSet::ApplyImpactSwap(ImpactSwap* apSwap) {
    CdeclCall(0x58EEB0, apSwap);
}

// GAME - 0x58E8F0
IMPACT_MATERIAL_TYPE BGSImpactDataSet::GetImpactMaterialType(HK_MATERIAL_TYPE aeHavokMaterial) {
    return CdeclCall<IMPACT_MATERIAL_TYPE>(0x58E8F0, aeHavokMaterial);
}
#endif

// GAME - 0x5C02F0
BGSImpactDataSet* BGSImpactDataSet::GetDefaultImpactDataSet() {
    return pDefaultImpactDataSet;
}

const char* BGSImpactDataSet::GetImpactMaterialName(IMPACT_MATERIAL_TYPE aeType) {
    return pImpactMaterialString[aeType];
}
