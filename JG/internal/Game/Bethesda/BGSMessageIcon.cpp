#include "BGSMessageIcon.hpp"

// GAME - 0x47A300
const char* BGSMessageIcon::GetMessageIconTextureName() const {
#ifdef GAME
    return ThisCall<const char*>(0x47A300, this);
#else
    return kIcon.GetTextureName();
#endif
}

// GAME - 0x47A380
void BGSMessageIcon::SetMessageIconTextureName(const char* apName) {
#ifdef GAME
    ThisCall(0x47A380, this, apName);
#else
	kIcon.SetTextureName(apName);
#endif
}

// GAME - 0x4812D0
uint32_t BGSMessageIcon::GetMessageIconTextureNameLength() const {
#ifdef GAME
    return ThisCall<uint32_t>(0x4812D0, this);
#else
    return kIcon.GetTextureNameLength();
#endif
}
