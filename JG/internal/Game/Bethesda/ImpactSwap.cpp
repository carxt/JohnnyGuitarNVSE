#include "ImpactSwap.hpp"

// GAME - 0x58F6F0
BGSImpactData* ImpactSwap::GetSwappedImpactData(IMPACT_MATERIAL_TYPE aeType, BGSImpactData* apOrgData) const {
    return ThisCall<BGSImpactData*>(0x58F6F0, this, aeType, apOrgData);
}

// GAME - 0x58F740
// GECK - 0x5ACA80
void ImpactSwap::AddSwappedImpactData(IMPACT_MATERIAL_TYPE aeType, BGSImpactData* apOrgData, BGSImpactData* apNewData) {
#ifdef GAME
    ThisCall(0x58F740, this, aeType, apOrgData, apNewData);
#else
    ThisCall(0x5ACA80, this, aeType, apOrgData, apNewData);
#endif
}

// GECK - 0x5AC280
void ImpactSwap::RemoveSwappedImpactData(IMPACT_MATERIAL_TYPE aeType, BGSImpactData* apOrgData) {
#ifdef GAME
    if (pRemappedData[aeType]) {
        pRemappedData[aeType]->RemoveAt(apOrgData);
        if (!pRemappedData[aeType]->GetCount()) {
            delete pRemappedData[aeType];
            pRemappedData[aeType] = nullptr;
        }
    }
#else
    ThisCall(0x5AC280, this, aeType, apOrgData);
#endif
}

// GAME - 0x58F7F0
const char* ImpactSwap::GetAltFootstepMaterialName(FootstepMaterialType aeType) const {
#ifdef GAME
    return ThisCall<const char*>(0x58F7F0, this, aeType);
#else
    if (cAltFootstepMaterialNames[aeType][0])
        return cAltFootstepMaterialNames[aeType];
    return nullptr;
#endif
}

const char* ImpactSwap::GetFootstepMaterialName(FootstepMaterialType aeType) {
    return pFootstepMaterialSoundNames[aeType];
}
