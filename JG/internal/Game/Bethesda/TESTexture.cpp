#include "TESTexture.hpp"

// GAME - 0x408DA0
const char* TESTexture::GetTextureName() const {
	return ThisCall<const char*>(0x408DA0, this);
}

// GAME - 0x48E730
const char* TESTexture::GetTextureName(const TESForm* apForm, const TESObjectREFR* apRef) {
	return CdeclCall<const char*>(0x48E730, apForm, apRef);
}

// GAME - 0x489100
void TESTexture::SetTextureName(const char* apName) {
	ThisCall(0x489100, this, apName);
}

// GAME - 0x48CEE0
uint32_t TESTexture::GetTextureNameLength() const {
	return ThisCall<uint32_t>(0x48CEE0, this);
}