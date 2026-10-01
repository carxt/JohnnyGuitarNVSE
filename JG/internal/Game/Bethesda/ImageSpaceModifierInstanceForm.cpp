#include "ImageSpaceModifierInstanceForm.hpp"

// GAME - 0x5299A0
ImageSpaceModifierInstanceForm* ImageSpaceModifierInstanceForm::Trigger(TESImageSpaceModifier* apMod, float afStrength, NiAVObject* apTarget) {
	return CdeclCall<ImageSpaceModifierInstanceForm*>(0x5299A0, apMod, afStrength, apTarget);
}

// GAME - 0x529C90
void ImageSpaceModifierInstanceForm::Stop(TESImageSpaceModifier* apMod) {
	CdeclCall<void>(0x529C90, apMod);
}
