#include "TESBoundObject.hpp"

// GAME - 0x50EC30
TESBoundObject::Bounds TESBoundObject::Bounds::operator-(const Bounds& aOther) const {
	return Bounds(x - aOther.x, y - aOther.y, z - aOther.z);
}

// GAME - 0x50EC80
float TESBoundObject::Bounds::Length() const {
	return std::sqrt(x * x + y * y + z * z);
}

// GAME - 0x50EBF0
// GECK - 0x5EF8F0
float TESBoundObject::GetBoundSize() const {
	return (kBoundData.kMin - kBoundData.kMax).Length() * 0.5f;
}