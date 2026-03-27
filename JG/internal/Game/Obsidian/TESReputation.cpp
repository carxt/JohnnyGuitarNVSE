#include "TESReputation.hpp"

// GAME - 0x6155C0
float TESReputation::GetReputation(bool abPositive) const {
    if (abPositive)
        return fPositiveReputation;
    else
        return fNegativeReputation;
}

// GAME - 0x616A60
float TESReputation::GetReputationPercent(bool abPositive) const {
    if (abPositive)
        return GetPositiveRatio();
    else
        return GetNegativeRatio();
}

// GAME - 0x616950
uint8_t TESReputation::GetThreshold(bool abPositive) const {
    return ThisCall<uint8_t>(0x616950, this, static_cast<uint32_t>(abPositive));
}

// GAME - 0x616A20
float TESReputation::GetPositiveRatio() const {
    return fPositiveReputation / fMaxReputation;
}

// GAME - 0x616A40
float TESReputation::GetNegativeRatio() const {
    return fNegativeReputation / fMaxReputation;
}
