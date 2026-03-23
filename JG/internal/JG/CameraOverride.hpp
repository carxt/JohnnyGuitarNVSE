#pragma once
#include "misc/WorldToScreen.h"
namespace CameraOverride {
	extern NiVector3 kCameraPos;
	extern NiMatrix3 kCameraRot;
	extern uint32_t uiReferenceToTrack;
	extern int eAxis;

	void Reset();
	void Install();
	void OverridePos(bool override);
	void OverrideRot(bool override);

}