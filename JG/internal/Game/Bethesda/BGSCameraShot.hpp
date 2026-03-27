#pragma once

#include "TESForm.hpp"
#include "TESModel.hpp"
#include "TESImageSpaceModifiableForm.hpp"
#include "Gamebryo/NiSmartPointer.hpp"

class TESImageSpaceModifier;
class NiNode;
class NiAVObject;
class TESObjectREFR;

class BGSCameraShot : public TESForm, public TESModel, public TESImageSpaceModifiableForm {
public:
	BGSCameraShot();
	~BGSCameraShot();

	enum Action {
		SHOOT	= 0,
		FLY		= 1,
		HIT		= 2,
		ZOOM	= 3,
		COUNT,
	};

	enum Object : int32_t {
		ATTACKER	= 0,
		PROJECTILE	= 1,
		TARGET		= 2,
	};

	struct ALIGN4 _CameraShotFlags {
		enum Flags : uint32_t {
			POSITION_FOLLOWS_LOCATION	= 1u << 0,
			POSITION_FOLLOWS_TARGET		= 1u << 1,
			DONT_FOLLOW_BONE			= 1u << 2,
			FIRST_PERSON_CAMERA			= 1u << 3,
			NO_TRACER					= 1u << 4,
			START_AT_TIME_ZERO			= 1u << 5,
		};

		bool bPositionFollowsLocation	: 1;
		bool bPositionFollowsTarget		: 1;
		bool bDontFollowBone			: 1;
		bool bFirstPersonCamera			: 1;
		bool bNoTracer					: 1;
		bool bStartAtTimeZero			: 1;
	};
	using CameraShotFlags = _CameraShotFlags::Flags;

	struct Data {
		Action							eAction;
		Object							eLocation;
		Object							eTarget;
		Bitfield<_CameraShotFlags>		uiFlags;
		float							fPlayerTimeMult;
		float							fTargetTimeMult;
		float							fGlobalTimeMult;
		float							fMaxTime;
		float							fMinTime;
		float							fTargetPercentBetweenActors;
	};

	Data					kData;
	NiPointer<NiNode>		spLocationNode;
	NiPointer<NiNode>		spTargetNode;
	TESObjectREFR*			pReference;
	NiPointer<NiNode>		spCameraNode;
	NiPointer<NiAVObject>	spImagespaceTarget;
	int8_t					cCameraHasRotation;
	bool					bCameraTooClose;
	bool					bCameraIsKillCam;

	TESFORM_TYPE(BGSCameraShot);
};

ASSERT_SIZE(BGSCameraShot, 0x78);