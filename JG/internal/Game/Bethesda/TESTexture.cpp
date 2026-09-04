#include "TESTexture.hpp"

// GAME - 0x408DA0
const char* TESTexture::GetTextureName() const {
	return ThisCall<const char*>(0x408DA0, this);
}

// GAME - 0x48E730
// GECK - 0x50C960
const char* TESTexture::GetTextureName(const TESForm* apForm, const TESObjectREFR* apRef) {
#ifdef GAME
	return CdeclCall<const char*>(0x48E730, apForm, apRef);
#else
	return CdeclCall<const char*>(0x50C960, apForm, apRef);
#endif
}

// GAME - 0x489100
void TESTexture::SetTextureName(const char* apName) {
	ThisCall(0x489100, this, apName);
}

// GAME - 0x48CEE0
uint32_t TESTexture::GetTextureNameLength() const {
	return ThisCall<uint32_t>(0x48CEE0, this);
}