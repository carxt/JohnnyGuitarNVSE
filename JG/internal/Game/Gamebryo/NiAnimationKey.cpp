#include "NiAnimationKey.hpp"

void NiAnimationKey::SetTime(float afTime) {
	m_fTime = afTime;
}

float NiAnimationKey::GetTime() const {
	return m_fTime;
}

NiAnimationKey* NiAnimationKey::GetKeyAt(uint32_t auiIndex, uint8_t aucKeySize) const {
	return reinterpret_cast<NiAnimationKey*>((uint8_t*)this + auiIndex * aucKeySize);
}
