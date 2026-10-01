#include "FalloutAudioMedia.hpp"

// GAME - 0x8300C0
void FalloutAudioMedia::MediaOpen(Type aeMediaType, const char* apFileName, uint32_t auiFadeTime, bool abLoop, bool abForce, float afAttenuation, uint32_t auiSynchTime) {
	CdeclCall(0x8300C0, aeMediaType, apFileName, auiFadeTime, abLoop, abForce, afAttenuation, auiSynchTime);
}

// GAME - 0x8304A0
void FalloutAudioMedia::MediaClose() {
	CdeclCall(0x8304A0);
}
