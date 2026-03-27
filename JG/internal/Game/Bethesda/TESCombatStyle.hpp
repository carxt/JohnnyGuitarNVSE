#pragma once

#include "TESForm.hpp"

class TESCombatStyle : public TESForm {
public:
	TESCombatStyle();
	~TESCombatStyle();

	struct ALIGN4 _CombatStyleFlags {
		enum Flags : uint32_t {
			CHOOSE_ATTACK_USING_CHANCE		= 1u << 0,
			MELEE_ALERT_OK					= 1u << 1,
			FLEE_BASED_ON_PERSONAL_SURVIVAL	= 1u << 2,
			USE_CLUSTERS					= 1u << 3,
			IGNORE_THREATS					= 1u << 4,
			IGNORE_DAMAGING_SELF			= 1u << 5,
			IGNORE_DAMAGING_GROUP			= 1u << 6,
			IGNORE_DAMAGING_SPECTATORS		= 1u << 7,
			CANT_USE_STEALTHBOY				= 1u << 8,
		};
	
		bool bChooseAttackUsingChance		: 1;
		bool bMeleeAlertOK					: 1;
		bool bFleeBasedOnPersonalSurvival	: 1;
		bool bUseClusters					: 1;
		bool bIgnoreThreats					: 1;
		bool bIgnoreDamagingSelf			: 1;
		bool bIgnoreDamagingGroup			: 1;
		bool bIgnoreDamagingSpectators		: 1;
		bool bCantUseStealthBoy				: 1;
	};
	using CombatStyleFlags = _CombatStyleFlags::Flags;

	enum WeaponRestrictions {
		NONE	= 0,
		MELEE	= 1,
		RANGED	= 2,
	};

	struct SimpleData {
		float	fCoverSearchRadius;
		float	fCoverChance;
		float	fCoverWaitTimerMin;
		float	fCoverWaitTimerMax;
		float	fCoverWaitToFireTimerMin;
		float	fCoverWaitToFireTimerMax;
		float	fCoverFireTimerMin;
		float	fCoverFireTimerMax;
		float	fWeaponMinRangeMult;
		float	fClusterDistance;
		uint8_t	ucWeaponRestrictions;
		float	fWeaponMaxRangeMult;
		float	fTargetingFOV;
		float	fCombatRadius;
		float	fSemiAutoFiringDelayMultMin;
		float	fSemiAutoFiringDelayMultMax;
	};

	struct StandardData {
		int8_t						cDodgeChance;
		int8_t						cDodgeLeftRightChance;
		float						fDodgeLeftRightMinTime;
		float						fDodgeLeftRightMaxTime;
		float						fDodgeForwardMinTime;
		float						fDodgeForwardMaxTime;
		float						fDodgeBackwardMinTime;
		float						fDodgeBackwardMaxTime;
		float						fIdleTimeMin;
		float						fIdleTimeMax;
		int8_t						cBlockChance;
		int8_t						cAttackChance;
		float						fAttackDuringRecoilStaggerBonus;
		float						fAttackDuringUnconsciousBonus;
		float						fAttackHandBonus;
		int8_t						cPowerAttackChance;
		float						fPowerAttackRecoilStaggerBonus;
		float						fPowerAttackUnconsciousBonus;
		int8_t						cPowerAttackNormalChance;
		int8_t						cPowerAttackForwardChance;
		int8_t						cPowerAttackBackwardChance;
		int8_t						cPowerAttackLeftChance;
		int8_t						cPowerAttackRightChance;
		float						fHoldTimerMin;
		float						fHoldTimerMax;
		Bitfield<_CombatStyleFlags>	uiFlags;
		int8_t						cAcrobaticDodgeChance;
		int8_t						cRushAttackChance;
		float						fRushAttackDistMult;
	};

	struct AdvancedData {
		float	fDodgeFatigueMult;
		float	fDodgeFatigueBase;
		float	fDodgeSpeedBase;
		float	fDodgeSpeedMult;
		float	fDodgeUnderAttackMult;
		float	fDodgeNotUnderAttackMult;
		float	fDodgeBackDuringAttackMult;
		float	fDodgeBackNotUnderAttackMult;
		float	fDodgeForwardWhileAttackingMult;
		float	fDodgeForwardNotAttackingMult;
		float	fBlockSkillMult;
		float	fBlockSkillBase;
		float	fBlockUnderAttackMult;
		float	fBlockNotUnderAttackMult;
		float	fAttackSkillMult;
		float	fAttackSkillBase;
		float	fAttackUnderAttackMult;
		float	fAttackNotUnderAttackMult;
		float	fAttackDuringBlockMult;
		float	fPowerAttackFatigueBase;
		float	fPowerAttackFatigueMult;
	};

	SimpleData		kSimple;
	StandardData	kStandard;
	AdvancedData	kAdvanced;

	TESFORM_TYPE(TESCombatStyle);

	inline void SetFlag(uint32_t auiFlag, bool abSet) {
		kStandard.uiFlags.Set(auiFlag, abSet);
	}

	inline bool GetFlag(uint32_t auiFlag) const {
		return kStandard.uiFlags.Get(auiFlag);
	}
};

ASSERT_SIZE(TESCombatStyle, 0x108);