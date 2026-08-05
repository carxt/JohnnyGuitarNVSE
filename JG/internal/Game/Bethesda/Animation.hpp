#pragma once

#include "Gamebryo/NiNode.hpp"
#include "Gamebryo/NiTPointerMap.hpp"
#include "BSSimpleList.hpp"
#include "TESAnimGroup.hpp"
#include "BSAnimGroupSequence.hpp"

class Actor;
class AnimSequenceBase;
class TESIdleForm;
class KFModel;
class TESObjectREFR;

NiSmartPointer(AnimIdle);
NiSmartPointer(NiControllerManager);

struct ANIM_GROUP_INFO {
	const char*				pName;
	bool					bMultipleSequences;
	ANIM_GROUP_SECTION		eSectionLayer;
	ANIM_GROUP_ACTION_TYPE	eAction;
	ANIM_GROUP_ACTION		eActions[5];
};

struct IDLE_REPLAY_DELAY {
	TESIdleForm*	pIdleForm;
	float			fDelay;
};

class Animation {
public:
	enum Bones {
		PELVIS		= 0,
		BIP01COPY	= 1,
		LFOREARM	= 2,
		HEAD		= 3,
		WEAPON		= 4,
		UNUSED_5	= 5,
		UNUSED_6	= 6,
		NECK1		= 7,
		COUNT
	};

	struct ALIGN4 _Flags {
		enum Flags : uint32_t {
			MOVED					= 1u << 0,
			DELAY_SCENEGRAPH_UPDATE = 1u << 2,
		};

		bool bMoved					: 1;
		bool bDelayScenegraphUpdate : 1;
	};
	using Flags = _Flags::Flags;

	Bitfield<_Flags>							uiFlags;
	Actor*										pActor;
	NiNodePtr									spSceneRoot;
	NiNode*										pAccumRoot;
	NiPoint3									kMovementDelta;
	NiPoint3									kAccumRootTranslate;

	union {
		struct {
			NiNode* pPelvis;
			NiNode* pBip01Copy;
			NiNode* pLForearm;
			NiNode* pHead;
			NiNode* pWeapon;
			NiNode* pUNUSED_3C;
			NiNode* pUNUSED_40;
			NiNode* pNeck1;
		};

		NiNode* pSoundPriorityBones[Bones::COUNT];
	};

	float										fLooking;
	ANIM_GROUP_TYPE								usGroups[ANIM_GROUP_SECTION::COUNT];
	ANIM_GROUP_ACTION							iActions[ANIM_GROUP_SECTION::COUNT];
	int32_t										iLoopCounts[ANIM_GROUP_SECTION::COUNT];
	ANIM_GROUP_TYPE								usNextGroups[ANIM_GROUP_SECTION::COUNT];
	int32_t										iNextLoops[ANIM_GROUP_SECTION::COUNT];
	int8_t										cSkipUpdate;
	bool										bShutDown;
	float										fTime;
	float										fLipTime;
	NiControllerManagerPtr						spManager;
	NiTPointerMap<uint16_t, AnimSequenceBase*>*	pAnimSequences;
	BSAnimGroupSequence*						pCurrentSequences[ANIM_GROUP_SECTION::COUNT];
	BSAnimGroupSequence*						pLastMovementSequence;
	BSSimpleList<KFModel*>						kAnimationCloneList;
	float										fMoveSpeed;
	float										fAttackSpeed;
	float										fTurboSpeed;
	float										fWeaponReloadSpeed;
	float										fEquipSpeed;
	int8_t										cSkipNextBlend;
	uint16_t									usQueuedReloadGroup;
	AnimIdlePtr									spAnimIdle;
	AnimIdlePtr									spAnimIdleQueued;
	AnimIdlePtr									spAnimIdleFreeWhenInactive[2];
	BSSimpleList<IDLE_REPLAY_DELAY*>			kReplayDelayList;

	bool GetDelta(NiPoint3& arVector, const Actor* apActor, bool abRotation, bool abNoHeight) const;

	bool UpdateIfRequired();

	bool AddAnimation(KFModel* apModel, bool abClone);

	void LoadSpecialAnims(BSSimpleList<const char*>* apAnimations, const char* apPath);

	bool HasQueuedReload() const;

	TESIdleForm* GetIdleForm() const;
	
	BSAnimGroupSequence* GetIdleAnimSequence() const;

	BSAnimGroupSequence* GetCurrentSequence(ANIM_GROUP_SECTION aeSection) const;

	float GetTimePassed() const;

	bool SpecialIdleDonePlaying() const;

	bool SpecialIdleWorking() const;

	bool SpecialIdleWorking(TESIdleForm* apIdle) const;

	bool SpecialIdleWorking(BSAnimGroupSequence* apAnimSequence) const;

	void SpecialIdleQueue(TESIdleForm* apIdle, ANIM_GROUP_SECTION aeGroupSection);

	void SpecialIdleAuto(TESIdleForm* apIdle, Actor* apActor, ANIM_GROUP_SECTION aeGroupSection, ANIM_IDLE_PLAY_TYPE aePlayType);

	void SpecialIdleFree(bool abFreeQueued, bool abForceDelete);

	BSAnimGroupSequence* PlayGroup(uint16_t aeGroup, ANIM_ACTION_FLAGS aeFlags, uint32_t auiLoopCount, ANIM_GROUP_SECTION aeSection);

	void ClearGroup(ANIM_GROUP_SECTION aeSection, float afEaseOutTime);

	void BlendOut(ANIM_GROUP_SECTION aeSection, bool abIronSightsToggle);

	void ReloadTargets(bool abReload);

	float GetSmallestHavokBlendValue(NiNode* apNode);

	static const char* GetGroupSectionName(ANIM_GROUP_SECTION aeSection);

	static const ANIM_GROUP_INFO* GetGroupInfo(ANIM_GROUP_TYPE aeGroup);

	static const char* GetGroupName(ANIM_GROUP_TYPE aeGroup);
};

ASSERT_SIZE(Animation, 0x13C)