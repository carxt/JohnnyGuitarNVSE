#include "BSFogProperty.hpp"

void BSFogProperty::GetDistance(float& arStart, float& arEnd, float& arPower) const {
	arStart = fStartDistance;
	arEnd = fEndDistance;
	arPower = fPower;
}

// GAME - 0x5BF9A0
void BSFogProperty::SetDistance(float afStart, float afEnd) {
	fStartDistance = afStart;
	fEndDistance = afEnd;
}

void BSFogProperty::GetWaterDistance(float& arStart, float& arEnd) const {
	arStart = fStartWaterDistance;
	arEnd = fEndWaterDistance;
}

// GAME - 0x633C20
void BSFogProperty::SetWaterDistance(float afStart, float afEnd) {
	fStartWaterDistance = afStart;
	fEndWaterDistance = afEnd;
}

float BSFogProperty::GetFogHeight() const {
	return fHeight;
}

// GAME - 0x633C40
void BSFogProperty::SetFogHeight(float afHeight) {
	fHeight = afHeight;
}

const NiColor& BSFogProperty::GetWaterColor() const {
	return kWaterColor;
}

// GAME - 0x633C60
void BSFogProperty::SetWaterColor(const NiColor& arColor) {
	kWaterColor = arColor;
}

float BSFogProperty::GetPower() const {
	return fPower;
}

// GAME - 0x5BFBD0
void BSFogProperty::SetPower(float afPower) {
	fPower = afPower;
}

// GAME - 0xBB8140
void BSFogProperty::SetDepth(float afDepth) {
	ThisCall(0xBB8140, this, afDepth);
}
