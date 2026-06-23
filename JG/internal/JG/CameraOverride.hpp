#pragma once

class NiPoint3;
class TESObjectREFR;

namespace CameraOverride {

	struct _CameraRotationType {
		enum Type {
			ROTATE_TO_TARGET = -2,
			ROTATE_RESET	 = -1,
			ROTATE_NONE		 = 0,
			ROTATE_X		 = 1,
			ROTATE_Y		 = 2,
			ROTATE_Z		 = 3,
		};
	};
	using CameraRotationType = _CameraRotationType::Type;

	void Reset();

	void Install();

	void OverridePos(bool abOverride, const NiPoint3& arNewPos);

	void OverrideRot(bool abOverride, CameraRotationType aeRotType, float afAngle, const TESObjectREFR* apRef);


} 