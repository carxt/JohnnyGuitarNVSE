#pragma once

#include "BSStringT.hpp"
#include "SkyObject.hpp"

class NiTriShape;

class Moon : public SkyObject {
public:
	struct _UpdateStatus {
		enum Status {
			NOT_REQUIRED	= 0,
			WHEN_CULLED		= 1,
			INITIALIZE		= 2,
		};
	};
	using UpdateStatus = _UpdateStatus::Status;

	struct _Phase {
		enum Phase : uint32_t {
			FULL				= 0,
			THIRD_QUARTER_WAN	= 1,
			HALF_WAN			= 2,
			FIRST_QUARTER_WAN	= 3,
			NEW					= 4,
			FIRST_QUARTER_WAX	= 5,
			HALF_WAX			= 6,
			THIRD_QUARTER_WAX	= 7,
			COUNT,
		};
	};
	using Phase = _Phase::Phase;

	NiPointer<NiNode>		spMoonNode;
	NiPointer<NiNode>		spShadowNode;
	NiPointer<NiTriShape>	spMoonMesh;
	NiPointer<NiTriShape>	spShadowMesh;
	BSString				strTextures[Phase::COUNT];
	float					fAngleFadeStart;
	float					fAngleFadeEnd;
	float					fAngleShadowEarlyFade;
	float					fSpeed;
	float					fZOffset;
	uint32_t				uiSize;
	UpdateStatus			eUpdateMoonTexture;
	float					fAngle;
	float					fLastUpdateHour;

#ifdef GAME
	static constexpr AddressPtr<uint32_t, 0x11CCA80> eCurrentPhase;
#endif
};

ASSERT_SIZE(Moon, 0x7C)