#pragma once

#include "Gamebryo/NiRefObject.hpp"
#include "Gamebryo/NiPoint3.hpp"
#include "BSEnums.hpp"
#include "AnimGroup_View.hpp"

class TESSound;

class TESAnimGroup : public NiRefObject {
public:
	TESAnimGroup();
	virtual ~TESAnimGroup();

	struct AnimGroupSound {
		float		fTime;
		union {
			uint8_t		ucVolume;
			uint8_t		eType;
		};
		union {
			float		fPitch;
			uint32_t	uiEnumData;
		};
		TESSound*	pSound;
	};

	uint8_t			ucPriorities[8];
	uint16_t		usType;
	uint32_t		uiNumKeys;
	float*			pTimes;
	NiPoint3		kSpeed;
	int8_t			cMorphKey;
	uint8_t			ucBlendFrames;
	uint8_t			ucBlendInFrames;
	uint8_t			ucBlendOutFrames;
	uint8_t			ucDecal;
	const char*		pParentNodeName;
	uint32_t		uiSoundCount;
	AnimGroupSound* pSounds;

	ANIM_GROUP_TYPE GetType() const;

	ANIM_GROUP_MOVE GetMove() const;

	ANIM_GROUP_WEAPON GetWeapon() const;

	bool IsAimAction() const;

	bool IsIronSightsAction() const;

	bool IsAttackAction() const;

	bool IsAttackSpinAction() const;

	bool IsPowerAttack() const;

	bool IsReloadAction() const;

	bool IsIdleAnim() const;

	bool IsJumpingLandAnim() const;

	bool IsJumpingLoopAnim() const;

	float GetSpeed() const;

	bool IsMovementSequence() const;

	static uint16_t AnimGroup(ANIM_GROUP_MOVE aeMove, ANIM_GROUP_WEAPON aeWeapon, ANIM_GROUP_TYPE aeGroup, bool abPowerArmor);

	static ANIM_GROUP_TYPE GetType(uint16_t ausGroup);

	static ANIM_GROUP_MOVE GetMove(uint16_t ausGroup);

	static ANIM_GROUP_WEAPON GetWeapon(uint16_t ausGroup);

	static bool IsAimAction(uint16_t ausGroup);

	static bool IsIronSightsAction(uint16_t ausGroup);

	static bool IsIronSightsAction(ANIM_GROUP_TYPE aeGroup);

	static bool IsAttackAction(uint16_t ausGroup);

	static bool IsAttackAction(ANIM_GROUP_ACTION_TYPE aeType);

	static bool IsAttackSpinAction(uint16_t ausGroup);

	static bool IsAttackSpinAction(ANIM_GROUP_ACTION_TYPE aeType);

	static bool IsPowerAttackAction(uint16_t ausGroup);

	static bool IsPowerAttackAction(ANIM_GROUP_ACTION_TYPE aeType);

	static bool IsReloadAction(uint16_t ausGroup);

	static bool IsReloadAction(ANIM_GROUP_TYPE aeGroup);

	static bool IsIdleAnim(uint16_t ausGroup);
};

ASSERT_SIZE(TESAnimGroup, 0x3C);
ASSERT_SIZE(TESAnimGroup::AnimGroupSound, 0x10);