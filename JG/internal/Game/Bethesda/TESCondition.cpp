#include "TESCondition.hpp"

// GAME - 0x825C00
CONDITION_RUN_ON TESConditionItem::GetRunOn() const {
    return static_cast<CONDITION_RUN_ON>(kData.eRunOn);
}

// GAME - 0x5EB680
uint32_t TESConditionItem::GetConditionFunction() const {
    return kData.kFunctionData.usFunction;
}

// GAME - 0x681460
void TESConditionItem::SetConditionFunction(uint16_t ausFunction) {
#ifdef GAME
    ThisCall(0x681460, this, ausFunction);
#else
    kData.kFunctionData = {};
    kData.kFunctionData.usFunction = ausFunction;
#endif
}

// GAME - 0x5EC060
CONDITION_COMPARISON TESConditionItem::GetComparisonCondition() const {
#ifdef GAME
    return ThisCall<CONDITION_COMPARISON>(0x5EC060, this);
#else
    return static_cast<CONDITION_COMPARISON>(kData.ucType.eComparisonCondition);
#endif
}

// GAME - 0x681530
void TESConditionItem::SetComparisonCondition(CONDITION_COMPARISON aeComparison) {
#ifdef GAME
    ThisCall(0x681530, this, aeComparison);
#else
    if (aeComparison >= CONDITION_COMPARISON::COUNT)
        aeComparison = CONDITION_COMPARISON::EQUAL;

    kData.ucType.eComparisonCondition = aeComparison;
#endif
}

// GAME - 0x681490
// GECK - 0x4A3B30
float TESConditionItem::GetComparisonValue() const {
#ifdef GAME
    return ThisCall<float>(0x681490, this);
#else
    return ThisCall<float>(0x4A3B30, this);
#endif
}

// GAME - 0x681500
void TESConditionItem::SetComparisonValueFloat(float afValue) {
#ifdef GAME
    ThisCall(0x681500, this, afValue);
#else
    if (!GetValueIsGlobal())
        kData.uComparisonValue.fValue = afValue;
#endif
}

// GAME - 0x5EC040
bool TESConditionItem::GetOr() const {
    return kData.ucType.bOr;
}

// GAME - 0x6814E0
bool TESConditionItem::GetValueIsGlobal() const {
    return kData.ucType.bUseGlobal;
}

#ifdef GAME
// GAME - 0x680C30
bool TESCondition::IsTrue(TESObjectREFR* apActionRef, TESObjectREFR* apTargetRef) const {
	return ThisCall<bool>(0x680C30, this, apActionRef, apTargetRef);
}
#endif

#ifdef EDITOR
void TESCondition::RegisterForm(TESForm* apForm) {
    ThisCall(0x4A2810, this, apForm);
}
#endif

// GECK - 0x4A1B10
const char* TESCondition::GetComparisonConditionSymbol(CONDITION_COMPARISON aeComparison) {
#ifdef GAME
    if (aeComparison >= CONDITION_COMPARISON::COUNT)
        return "";
    else
		return pComparisonConditionSymbols[aeComparison];
#else
    return CdeclCall<const char*>(0x4A1B10, aeComparison);
#endif
}
