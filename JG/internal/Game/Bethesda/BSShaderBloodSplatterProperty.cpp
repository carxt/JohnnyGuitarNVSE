#include "BSShaderBloodSplatterProperty.hpp"

// GAME - 0x4DFE80
void BSShaderBloodSplatterProperty::SetTexture(uint32_t auiIndex, NiTexture* apTexture) {
	ThisCall(0x4DFE80, this, auiIndex, apTexture);
}

// GAME - 0xB81420
void BSShaderBloodSplatterProperty::SetFadeSourceRecurse(NiAVObject* apObject, float* apfFadeAlpha) {
	CdeclCall(0xB81420, apObject, apfFadeAlpha);
}