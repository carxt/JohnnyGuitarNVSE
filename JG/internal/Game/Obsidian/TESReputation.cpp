#include "TESReputation.hpp"

// GAME - 0x6166E0
const char* TESReputation::GetReputationMainIcon() const {
#ifdef GAME
    return ThisCall<const char*>(0x6166E0, this);
#else
    if (GetTextureNameLength())
        return GetTextureName();
    return "";
#endif
}

void TESReputation::SetReputationMainIcon(const char* apPath) {
    SetTextureName(apPath);
}

// GAME - 0x6155C0
float TESReputation::GetReputationValue(Type aeType) const {
#ifdef GAME
    return ThisCall<float>(0x6155C0, this, aeType);
#else
    if (aeType == Type::POSITIVE)
        return fPositiveReputation;
    else
		return fNegativeReputation;
#endif
}

// GAME - 0x615580
void TESReputation::SetReputationValue(Type aeType, float afValue) {
#ifdef GAME
    ThisCall(0x615580, this, aeType, afValue);
#else
    if (aeType == Type::POSITIVE)
        fPositiveReputation = afValue;
    else
        fNegativeReputation = afValue;
#endif
}

#ifdef GAME
// GAME - 0x615730
void TESReputation::AddReputationValue(Type aeType, float afValue) {
    ThisCall(0x615730, this, aeType, afValue);
}

// GAME - 0x615A00
void TESReputation::RemoveReputationValue(Type aeType, float afValue) {
    ThisCall(0x615A00, this, aeType, afValue);
}

// GAME - 0x615C90
void TESReputation::AddReputationValueByLevel(Type aeType, int32_t aiValue) {
    ThisCall(0x615C90, this, aeType, aiValue);
}

// GAME - 0x615FA0
void TESReputation::RemoveReputationValueByLevel(Type aeType, int32_t aiValue) {
    ThisCall(0x615FA0, this, aeType, aiValue);
}

// GAME - 0x616C20
void TESReputation::CommitCrime(bool abMajor) {
    ThisCall(0x616C20, this, abMajor);
}

// GAME - 0x616950
uint8_t TESReputation::GetReputationLevel(Type aeType) const {
    return ThisCall<uint8_t>(0x616950, this, aeType);
}

// GAME - 0x616A60
float TESReputation::GetReputationPercent(Type aeType) const {
    return ThisCall<float>(0x616A60, this, aeType);
}

// GAME - 0x616950
uint8_t TESReputation::GetThreshold(Type aeType) const {
    return ThisCall<uint8_t>(0x616950, this, aeType);
}

// GAME - 0x616A20
float TESReputation::GetPositiveRatio() const {
    return ThisCall<float>(0x616A20, this);
}

// GAME - 0x616A40
float TESReputation::GetNegativeRatio() const {
    return ThisCall<float>(0x616A40, this);
}

// GAME - 0x616710
const char* TESReputation::GetReputationTitle() const {
    return ThisCall<const char*>(0x616710, this);
}

// GAME - 0x616890
const char* TESReputation::GetReputationDesc() const {
    return ThisCall<const char*>(0x616890, this);
}

// GAME - 0x6167D0
const char* TESReputation::GetReputationIcon() const {
    return ThisCall<const char*>(0x6167D0, this);
}
#endif