#include "TESCondition.hpp"
#include "TESGlobal.hpp"

// GAME - 0x681600
bool TESConditionItem::IsTrue(TESObjectREFR* apActionRef, TESObjectREFR* apTargetRef, bool& abDipositionFailure) const {
    return ThisCall<bool>(0x681600, apActionRef, apTargetRef, &abDipositionFailure);
}

// GAME - 0x825C00
CONDITION_RUN_ON TESConditionItem::GetRunOn() const {
    return CONDITION_RUN_ON(kData.eRunOn);
}

// GAME - 0x5EB680
uint32_t TESConditionItem::GetConditionFunction() const {
    return kData.kFunctionData.usFunction;
}

// GAME - 0x681460
void TESConditionItem::SetConditionFunction(uint16_t ausFunction) {
    ThisCall(0x681460, this, ausFunction);
}

// GAME - 0x5EC060
CONDITION_COMPARISON TESConditionItem::GetComparisonCondition() const {
    return CONDITION_COMPARISON(kData.ucType.Get(0xE0) >> 5);
}

// GAME - 0x681530
void TESConditionItem::SetComparisonCondition(CONDITION_COMPARISON aeComparison) {
    ThisCall(0x681530, this, aeComparison);
}

// GAME - 0x681490
float TESConditionItem::GetComparisonValue() const {
    if (GetValueIsGlobal()) {
        if (kData.uComparisonValue.pGlobal)
            return kData.uComparisonValue.pGlobal->GetValue();
    }
    else {
        return kData.uComparisonValue.fValue;
    }
    return 0.f;
}

// GAME - 0x681500
void TESConditionItem::SetComparisonValueFloat(float afValue) {
    if (!GetValueIsGlobal())
        kData.uComparisonValue.fValue = afValue;
}

// GAME - 0x5EC040
bool TESConditionItem::GetOr() const {
    return kData.ucType.bOr;
}

// GAME - 0x6814E0
bool TESConditionItem::GetValueIsGlobal() const {
    return kData.ucType.bUseGlobal;
}

// GAME - 0x680C30
bool TESCondition::IsTrue(TESObjectREFR* apActionRef, TESObjectREFR* apTargetRef) const {
	return ThisCall<bool>(0x680C30, this, apActionRef, apTargetRef);
}

// GAME - 0x680C60
bool TESCondition::IsTrue(TESObjectREFR* apActionRef, TESObjectREFR* apTargetRef, bool& abDipositionFailure, bool abEssentialPropertiesOnly) const {
    return ThisCall<bool>(0x680C60, this, apActionRef, apTargetRef, &abDipositionFailure, abEssentialPropertiesOnly);
}
