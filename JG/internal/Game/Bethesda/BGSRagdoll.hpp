#pragma once

#include "TESForm.hpp"
#include "TESModel.hpp"
#include "BSSimpleArray.hpp"

class BGSBodyPartData;
class TESActorBase;

struct FootIK_DATA {
	struct FootIK_Leg_DATA {
		int16_t sHipIndex;
		int16_t sKneeIndex;
		int16_t sAnkleIndex;
		bool	bAlignFootToTerrain;
		float	fMinAnkleHeightMS;
		float	fMaxAnkleHeightMS;
		float	fFootPlantedAnkleHeightMS;
		float	fFootRaisedAnkleHeightMS;
		float	fCosMaxKneeAngle;
		float	fCosMinKneeAngle;
		float	fKneeAxis[3];
		float	fFootEndLocLS[3];
	};

	struct FootIKSystem_DATA {
		float fOnOffGain;
		float fGroundAscendingGain;
		float fGroundDescendingGain;
		float fFootRaisedGain;
		float fFootPlantedGain;
		float fRaycastDistUp;
		float fRaycastDistDown;
	};

	bool											bEnabled;
	FootIKSystem_DATA								kSystemData;
	BSSimpleArray<const char*>						kLegSystemNames;
	BSSimpleArray<FootIK_DATA::FootIK_Leg_DATA>		kLegSystems;
};

struct LookIK_DATA {
	struct LookIK_Head_DATA {
		int16_t sNeckIndex;
		int16_t sHeadIndex;
		float	fForwardHeadLS[3];
		float	fForwardNeckMS[3];
		float	fLimitConeAngle;
		float	fLookAtTargetGain;
		float	fLookAtGain;
	};

	bool							bEnabled;
	BSSimpleArray<const char*>		kHeadSystemNames;
	BSSimpleArray<LookIK_Head_DATA>	kHeadSystems;
};

struct GrabIK_DATA {
	struct GrabIK_Arm_DATA {
		int16_t sShoulderIndex;
		int16_t sElbowIndex;
		int16_t sHandIndex;
	};

	bool							bEnabled;
	BSSimpleArray<const char*>		kArmSystemNames;
	BSSimpleArray<GrabIK_Arm_DATA>	kArmSystems;
};

struct PoseMatching_DATA {
	struct PoseMatching_System_DATA {
		uint16_t	kBones[3];
		bool		bDisableOnMove;
		float		fMotorsStrength;
		float		fPoseActivationDelayTime;
		float		fMatchErrorAllowance;
		float		fDisplacementToDisable;
	};

	bool						bEnabled;
	BSString					strDeathPose;
	PoseMatching_System_DATA	kData;
};

struct RagdollSaveData {
	uint16_t	usFeedbackDynamicBoneCount;
	uint16_t	usLegCount;
	uint16_t	usHeadCount;
	uint16_t	usArmCount;
	bool		bFeedbackEnabled;
	bool		bFootIKEnabled;
	bool		bLookIKEnabled;
	bool		bGrabIKEnabled;
	bool		bPoseMatchEnabled;
};

struct RagdollFeedbackData {
	struct SystemData {
		float		fBlendAmount;
		float		fHierarchyGain;
		float		fPositionGain;
		float		fVelocityGain;
		float		fAccelerationGain;
		float		fSnapGain;
		float		fVelocityDampening;
		float		fSnapMaxLinearVelocity;
		float		fSnapMaxAngularVelocity;
		float		fSnapMaxLinearDistance;
		float		fSnapMaxAngularDistance;
		float		fPositionMaxLinearVelocity;
		float		fPositionMaxAngularVelocity;
		uint32_t	uiProjectileImpulse;
		uint32_t	uiMeleeImpulse;
	};

	bool					bEnabled;
	SystemData				kSystemData;
	BSSimpleArray<uint16_t>	kFeedbackDynamicBones;
};

class BGSRagdoll : public TESForm, public TESModel {
public:
	BGSRagdoll();
	~BGSRagdoll();

	RagdollSaveData		kSaveData;
	RagdollFeedbackData	kFeedback;
	FootIK_DATA			kFootIK;
	LookIK_DATA			kLookIK;
	GrabIK_DATA			kGrabIK;
	PoseMatching_DATA	kPoseMatching;
	int32_t				iSkeletonID;
	BGSBodyPartData*	pBodyPartData;
	TESActorBase*		pPreviewActor;

	TESFORM_TYPE(BGSRagdoll);
};

ASSERT_SIZE(BGSRagdoll, 0x148);