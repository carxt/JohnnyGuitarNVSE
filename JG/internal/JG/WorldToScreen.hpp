#pragma once

#include <GameForms.h>

namespace WorldToScreen {

	static constexpr float ZERO_TOLERANCE = 0.0000099999997f;

	struct CameraParams {
		NiPoint3		kWorld;
		NiPoint3		kLocal;
		float			m_aafWorldToCam[4][4];
		NiViewport		m_kPort;
	};

	extern CameraParams kCameraData;

	void Install();

	bool __fastcall WorldToScreenPoint3(const CameraParams& arCamera, const NiPoint3& arPos, NiPoint3& arOut, float afZeroTolerance, int aeOffscreenHandleType);

	bool __fastcall WorldToScreen(const NiPoint3& arPos, NiPoint3& arOut, int aeOffscreenHandleType, float afZeroTolerance = ZERO_TOLERANCE);

}