#include "ScreenCustomSplatter.hpp"

// GAME - 0x8746A0
NiNode* ScreenCustomSplatter::GetCurrentRoot() {
    return CdeclCall<NiNode*>(0x8746A0);
}

// GAME - 0x8746B0
NiCamera* ScreenCustomSplatter::GetCamera() {
    return CdeclCall<NiCamera*>(0x8746B0);
}

// GAME - 0x871260
bool ScreenCustomSplatter::IsActiveSplatter() {
	return CdeclCall<bool>(0x871260);
}

// GAME - 0x4DF040
NiNode* ScreenCustomSplatter::CreateGeometry(uint32_t auiCount, float afSizeMult, float afOpacityMult) {
	return CdeclCall<NiNode*>(0x4DF040, auiCount, afSizeMult, afOpacityMult);
}

// GAME - 0x4DE8E0
void ScreenCustomSplatter::Activate(uint32_t auiCount, float afDuration, uint32_t aeType, float afSizeMult, float afOpacityMult) {
	CdeclCall(0x4DE8E0, auiCount, afDuration, aeType, afSizeMult, afOpacityMult);
}
