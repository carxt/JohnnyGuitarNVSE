#include "ImageSpaceModifierInstanceDRB.hpp"

float ImageSpaceModifierInstanceDRB::GetRampup() const {
    return fRampup;
}

void ImageSpaceModifierInstanceDRB::SetRampup(float afVal) {
    fRampup = afVal;
}

float ImageSpaceModifierInstanceDRB::GetStart() const {
    return fStart;
}

void ImageSpaceModifierInstanceDRB::SetStart(float afVal) {
    fStart = afVal;
}

float ImageSpaceModifierInstanceDRB::GetRampdown() const {
    return fRampdown;
}

void ImageSpaceModifierInstanceDRB::SetRampdown(float afVal) {
    fRampdown = afVal;
}

float ImageSpaceModifierInstanceDRB::GetDownStart() const {
    return fDownStart;
}

void ImageSpaceModifierInstanceDRB::SetDownStart(float afVal) {
    fDownStart = afVal;
}

void ImageSpaceModifierInstanceDRB::SetCenter(const NiPoint2& arCenter) {
    kCenter = arCenter;
}

NiPoint2 ImageSpaceModifierInstanceDRB::GetCenter() const {
    return kCenter;
}

float ImageSpaceModifierInstanceDRB::GetDistance() const {
    return fDistance;
}

void ImageSpaceModifierInstanceDRB::SetDistance(float afDistance) {
    fDistance = afDistance;
}

float ImageSpaceModifierInstanceDRB::GetRange() const {
    return fRange;
}

void ImageSpaceModifierInstanceDRB::SetRange(float afRange) {
    fRange = afRange;
}

ImageSpaceModifierInstanceDRB::DOFMode ImageSpaceModifierInstanceDRB::GetMode() const {
    return eMode;
}

void ImageSpaceModifierInstanceDRB::SetMode(DOFMode aeMode) {
    eMode = aeMode;
}