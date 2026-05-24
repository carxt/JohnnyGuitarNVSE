#include "TESTexture.hpp"

// GAME - 0x408DA0
const char* TESTexture::GetTextureName() const {
    if (strTextureName.GetString())
		return strTextureName.GetString();
	else
		return "";
}

// GAME - 0x48E730
const char* TESTexture::GetTextureName(const TESForm* apForm, const TESObjectREFR* apRef) {
	return CdeclCall<const char*>(0x48E730, apForm, apRef);
}

// GAME - 0x489100
void TESTexture::SetTextureName(const char* apName) {
	strTextureName.Set(apName);
}

// GAME - 0x48CEE0
uint32_t TESTexture::GetTextureNameLength() const {
    return strTextureName.GetLength();
}