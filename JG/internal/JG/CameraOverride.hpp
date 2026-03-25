#pragma once
#include <GameObjects.h>
#include <NiTypes.h>
namespace CameraOverride {

	void Reset();
	void Install();
	void OverridePos(bool override, const NiPoint3& kNewPos);
	void OverrideRot(bool override, int eAxis, float fAngle, TESObjectREFR* pRef);

} 