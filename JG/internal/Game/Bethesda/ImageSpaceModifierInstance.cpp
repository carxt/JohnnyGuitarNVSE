#include "ImageSpaceModifierInstance.hpp"

// GAME - 0x84D050
bool ImageSpaceModifierInstance::GetPermanent() const {
	return uiFlags.IsSet(PERMANENT);
}

// GAME - 0x5BBD60
void ImageSpaceModifierInstance::SetPermanent(bool abPermanent) { 
	uiFlags.Set(PERMANENT, abPermanent); 
}

// GAME - 0x84D030
float ImageSpaceModifierInstance::GetStrength() const {
	return fStrength;
}

// GAME - 0x63F790
void ImageSpaceModifierInstance::SetStrength(float afStrength) {
	fStrength = afStrength;
}

// GAME - 0x47C860
float ImageSpaceModifierInstance::GetStartTime() const {
	return fStartTime;
}

// GAME - 0x6694C0
void ImageSpaceModifierInstance::SetStartTime(float afTime) {
	fStartTime = afTime;
}