#include "TESTexture.hpp"

// GAME - 0x408DA0
const char* TESTexture::GetTextureName() const {
#ifdef GAME
	return ThisCall<const char*>(0x408DA0, this);
#else
	return strTextureName.c_str();
#endif
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
#ifdef GAME
	ThisCall(0x489100, this, apName);
#else
	strTextureName.Set(apName);
#endif
}

// GAME - 0x48CEE0
uint32_t TESTexture::GetTextureNameLength() const {
#ifdef GAME
	return ThisCall<uint32_t>(0x48CEE0, this);
#else
	return strTextureName.GetLength();
#endif
}