#pragma once

#include "ImageSpaceModifierInstance.hpp"

class TESImageSpaceModifier;
class NiAVObject;

class ImageSpaceModifierInstanceForm : public ImageSpaceModifierInstance {
public:
	TESImageSpaceModifier*	pImageSpaceMod;
	TESImageSpaceModifier*	pLastImageSpaceMod;
	float					fLastStrength;
	NiObjectPtr				spLastTarget;
	float					fTransitionTime;

	static ImageSpaceModifierInstanceForm* Trigger(TESImageSpaceModifier* apMod, float afStrength, NiAVObject* apTarget);
	static void Stop(TESImageSpaceModifier* apMod);
};

ASSERT_SIZE(ImageSpaceModifierInstanceForm, 0x30);