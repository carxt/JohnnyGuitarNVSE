#include "NiExtraData.hpp"

// GAME - 0xA62660
const NiFixedString& NiExtraData::GetName() const {
	return m_kName;
}

// GAME - 0xA5B950
// GECK - 0x818130
void NiExtraData::SetName(const NiFixedString& arName) {
#ifdef GAME
    ThisCall(0xA5B950, this, &arName);
#else
    ThisCall(0x818130, this, &arName);
#endif
}
