#include "TESCondition.hpp"

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
    return ThisCall<CONDITION_COMPARISON>(0x5EC060, this);
}

// GAME - 0x681530
void TESConditionItem::SetComparisonCondition(CONDITION_COMPARISON aeComparison) {
    ThisCall(0x681530, this, aeComparison);
}

// GAME - 0x681490
float TESConditionItem::GetComparisonValue() const {
    return ThisCall<float>(0x681490, this);
}

// GAME - 0x681500
void TESConditionItem::SetComparisonValueFloat(float afValue) {
    ThisCall(0x681500, this, afValue);
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

const char* TESCondition::GetComparisonConditionSymbol(CONDITION_COMPARISON aeComparison) {
    if (aeComparison >= CONDITION_COMPARISON::COUNT)
        return "";
    else
		return pComparisonConditionSymbols[aeComparison];
}
