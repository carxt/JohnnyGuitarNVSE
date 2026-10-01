#include "ImageSpaceModifierInstanceDOF.hpp"

float ImageSpaceModifierInstanceDOF::GetDistance() const { 
    return fDistance;
}

void ImageSpaceModifierInstanceDOF::SetDistance(float afDistance) {
    fDistance = afDistance;
}

float ImageSpaceModifierInstanceDOF::GetRange() const {
    return fRange;
}

void ImageSpaceModifierInstanceDOF::SetRange(float afRange) {
    fRange = afRange;
}

float ImageSpaceModifierInstanceDOF::GetMotionBlur() const {
    return fMotionBlur;
}

// GAME - 0x965250
void ImageSpaceModifierInstanceDOF::SetMotionBlur(float afMotionBlur) {
    fMotionBlur = afMotionBlur;
}

ImageSpaceModifierInstanceDOF::DOFMode ImageSpaceModifierInstanceDOF::GetMode() const {
    return eMode; 
}

void ImageSpaceModifierInstanceDOF::SetMode(DOFMode aeMode) {
    eMode = aeMode;
}