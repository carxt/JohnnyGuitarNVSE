#pragma once

#include "BSEnums.hpp"
#include "Gamebryo/NiRefObject.hpp"

class TESObjectANIO;
class TESIdleForm;
class Actor;
class Animation;

NiSmartPointer(KFModel)
NiSmartPointer(BSAnimGroupSequence)
NiSmartPointer(NiNode)

class AnimIdle : public NiRefObject {
public:
	ANIM_IDLE_STATE			eState;
	ANIM_IDLE_PLAY_TYPE		ePlayType;
	KFModelPtr				spKFModel;
	ANIM_GROUP_SECTION		eGroupSection;
	BSAnimGroupSequencePtr	spSequence;
	TESObjectANIO*			pAnimObjects[2];
	NiNodePtr				spAddOnObjects[2];
	TESIdleForm*			pIdleForm;
	Animation*				pAnimation;
	Actor*					pActor;

	ANIM_IDLE_PLAY_TYPE GetType() const;

	KFModel* GetKFModel() const;

	ANIM_GROUP_SECTION GetSection() const;

	BSAnimGroupSequence* GetSequence() const;

	TESObjectANIO* GetAnimObject(uint32_t auiIndex) const;

	TESIdleForm* GetIdleForm() const;
};

ASSERT_SIZE(AnimIdle, 0x38);