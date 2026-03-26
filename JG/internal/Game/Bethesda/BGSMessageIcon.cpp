#include "BGSMessageIcon.hpp"

// GAME - 0x47A300
const char* BGSMessageIcon::GetMessageIconTextureName() const {
    return kIcon.GetTextureName();
}

// GAME - 0x47A380
void BGSMessageIcon::SetMessageIconTextureName(const char* apName) {
	kIcon.SetTextureName(apName);
}

// GAME - 0x4812D0
uint32_t BGSMessageIcon::GetMessageIconTextureNameLength() const {
    return kIcon.GetTextureNameLength();
}
