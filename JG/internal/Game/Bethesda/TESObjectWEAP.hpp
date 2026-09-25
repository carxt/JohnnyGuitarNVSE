#pragma once

#include "ActorValue.hpp"
#include "BGSAmmoForm.hpp"
#include "BGSBipedModelList.hpp"
#include "BGSClipRoundsForm.hpp"
#include "BGSDestructibleObjectForm.hpp"
#include "BGSEquipType.hpp"
#include "BGSMessageIcon.hpp"
#include "BGSPickupPutdownSounds.hpp"
#include "BGSPreloadable.hpp"
#include "BGSRepairItemList.hpp"
#include "TESAttackDamageForm.hpp"
#include "TESBoundObject.hpp"
#include "TESEnchantableForm.hpp"
#include "TESFullName.hpp"
#include "TESHealthForm.hpp"
#include "TESIcon.hpp"
#include "TESModelTextureSwap.hpp"
#include "TESScriptableForm.hpp"
#include "TESValueForm.hpp"
#include "TESWeightForm.hpp"

class Actor;
class TESAmmo;
class BGSProjectile;
class SpellItem;
class BGSImpactDataSet;
class TESObjectSTAT;
class TESObjectIMOD;
class TESEffectShader;

class TESObjectWEAP : public TESBoundObject, public TESFullName, public TESModelTextureSwap, public TESIcon, public TESScriptableForm, public TESEnchantableForm,
						public TESValueForm, public TESWeightForm, public TESHealthForm, public TESAttackDamageForm, public BGSAmmoForm, public BGSClipRoundsForm, 
							public BGSDestructibleObjectForm, public BGSRepairItemList, public BGSEquipType, public BGSPreloadable, public BGSMessageIcon, public BGSBipedModelList, 
								public BGSPickupPutdownSounds {
public:
	TESObjectWEAP();
	~TESObjectWEAP();

	struct ALIGN1 _WeaponFlags {
		enum Flags : uint8_t {
			IGNORE_WEAP_RESIST		= 0x1,
			IS_AUTOMATIC			= 0x2,
			HAS_SCOPE				= 0x4,
			CANT_DROP				= 0x8,
			HIDE_BACKPACK			= 0x10,
			EMBEDDED_WEAPON			= 0x20,
			NO_1STPERSON_IS_ANIMS	= 0x40,
			NON_PLAYABLE			= 0x80
		};

		bool bIgnoreWeapResist		: 1;
		bool bIsAutomatic			: 1;
		bool bHasScope				: 1;
		bool bCantDrop				: 1;
		bool bHideBackpack			: 1;
		bool bEmbeddedWeapon		: 1;
		bool bNo1stPersonISAnims	: 1;
		bool bNonPlayable			: 1;
	};
	using WeaponFlags = _WeaponFlags::Flags;

	struct ALIGN4 _WeaponFlagsEx {
		enum Flags : uint32_t {
			PLAYER_ONLY					= 0x1,
			NPCS_USE_AMMO				= 0x2,
			NO_JAM_AFTER_RELOAD			= 0x4,
			OVERRIDE_ACTION_POINTS		= 0x8,
			MINOR_CRIME					= 0x10,
			FIXED_RANGE					= 0x20,
			NOT_USED_NORMAL_COMBAT		= 0x40,
			OVERRIDE_DAMAGE_TO_WEAPON	= 0x80,
			NO_3RDPERSON_IS_ANIMS		= 0x100,
			BURST_SHOT					= 0x200,
			ALTERNATE_RUMBLE			= 0x400,
			LONG_VATS_BURST				= 0x800,
			HAS_NIGHT_SCOPE				= 0x1000,
			HAS_MOD_SCOPE				= 0x2000,
		};

		bool bPlayerOnly				: 1;
		bool bNPCsUseAmmo				: 1;
		bool bNoJamAfterReload			: 1;
		bool bOverrideActionPoints		: 1;
		bool bMinorCrime				: 1;
		bool bFixedRange				: 1;
		bool bNotUsedNormalCombat		: 1;
		bool bOverrideDamageToWeapon	: 1;
		bool bNo3rdPersonISAnims		: 1;
		bool bBurstShot					: 1;
		bool bAlternateRumble			: 1;
		bool bLongVATSBurst				: 1;
		bool bHasNightScope				: 1;
		bool bHasModScope				: 1;
	};
	using WeaponFlagsEx = _WeaponFlagsEx::Flags;

	struct _ModSlot {
		enum Slot {
			MOD_1 = 1u << 0,
			MOD_2 = 1u << 1,
			MOD_3 = 1u << 2,
		};
	};
	using ModSlot = _ModSlot::Slot;

	struct Data {
		uint8_t						eWeaponType;
		float						fSpeed;
		float						fReach;
		Bitfield<_WeaponFlags>		ucFlags;
		uint8_t						eHandGripAnim;
		uint8_t						ucAmmoPerShot;
		uint8_t						ucReloadAnim;
		float						fMinSpread;
		float						fSpread;
		float						fDrift;
		float						fSightFOV;
		uint8_t						ucConditionLevel;
		BGSProjectile*				pProjectile;
		uint8_t						ucBaseVATSChance;
		uint8_t						eAttackAnim;
		uint8_t						ucNumProjectiles;
		uint8_t						ucEmbeddedConditionValue;
		float						fMinRange;
		float						fMaxRange;
		WEAPON_HIT_BEHAVIOR			eHitBehavior;
		Bitfield<_WeaponFlagsEx>	uiFlagsEx;
		float						fAttackMult;
		float						fShotsPerSec;
		float						fActionPoints;
		float						fRumbleLeftMotor;
		float						fRumbleRightMotor;
		float						fRumbleDuration;
		float						fDamageToWeaponMult;
		float						fAnimShotsPerSec;
		float						fAnimReloadTime;
		float						fAnimJamTime;
		float						fAimArc;
		ActorValue::Index			eWeaponSkill;
		WEAPON_RUMBLE_PATTERN		eRumblePattern;
		float						fRumbleWavelength;
		float						fLimbDamageMult;
		uint32_t					uiResistType;
		float						fSightUsage;
		float						fSemiAutoFireDelayMin;
		float						fSemiAutoFireDelayMax;
		float						fCookTimer;
		WEAPON_MOD_EFFECT_TYPE		eEffectMods[3];
		float						fValue1Mod[3];
		uint8_t						ePowerAttackOverrideAnim;
		uint32_t					uiRequiredStrength;
		uint8_t						eModFireAnimation;
		uint8_t						ucModReloadAnim;
		float						fAmmoRegenRate;
		float						fKillImpulse;
		float						fValue2Mod[3];
		float						fImpulseDist;
		uint32_t					uiSkillRequirement;
	};

	struct CriticalData {
		uint16_t	usCriticalDamage;
		float		fCriticalChanceMult;
		bool		bEffectOnDeath;
		SpellItem*	pEffect;
	};

	struct VATSData {
		SpellItem*	pEffect;
		float		fSkillReq;
		float		fDamageMult;
		float		fActionPoints;
		bool		bIsSilent;
		bool		bModRequired;
		Bitfield8	ucFlags;
	};

	Data				kData;
	CriticalData		kCriticalData;
	TESModel			kShellCasingModel;
	TESModel			kScopeModel;
	TESModel			kWorldModel;
	TESEffectShader*	pScopeEffect;
	union {
		TESSound*		pSounds[WEAPON_SOUND::COUNT];
		struct {
			TESSound*	pAttackSound;
			TESSound*	pAttackSoundDistant;
			TESSound*	pAttackSound2D;
			TESSound*	pAttackLoop;
			TESSound*	pAttackFailSound;
			TESSound*	pMeleeBlockSound;
			TESSound*	pIdleSound;
			TESSound*	pEquipSound;
			TESSound*	pUnequipSound;
			TESSound*	pAttackSoundMod;
			TESSound*	pAttackSoundDistantMod;
			TESSound*	pAttackSound2DMod;
		};
	};
	BGSImpactDataSet*	pImpactDataSet;
	TESObjectSTAT*		p1stPersonObject;
	union {
		TESObjectSTAT*	p1stPersonModObjects[7];
		struct {
			TESObjectSTAT* p1stPersonMod1Object;
			TESObjectSTAT* p1stPersonMod2Object;
			TESObjectSTAT* p1stPersonMod3Object;
			TESObjectSTAT* p1stPersonMod12Object;
			TESObjectSTAT* p1stPersonMod23Object;
			TESObjectSTAT* p1stPersonMod13Object;
			TESObjectSTAT* p1stPersonMod123Object;
		};
	};
	union {
		TESModelTextureSwap kWorldModModels[7];
		struct {
			TESModelTextureSwap kWorldModelMod1;
			TESModelTextureSwap kWorldModelMod2;
			TESModelTextureSwap kWorldModelMod3;
			TESModelTextureSwap kWorldModelMod12;
			TESModelTextureSwap kWorldModelMod13;
			TESModelTextureSwap kWorldModelMod23;
			TESModelTextureSwap kWorldModelMod123;
		};
	};
	union {
		TESObjectIMOD*	pModObjects[3];
		struct {
			TESObjectIMOD* pModObject1;
			TESObjectIMOD* pModObject2;
			TESObjectIMOD* pModObject3;
		};
	};
	BSString			strEmbeddedWeaponNode;
	SOUND_LEVEL			eSoundLevel;
	BSString			strVATSAttackName;
	VATSData			kVATSData;
	bool				bIsLoopingReload;

	TESFORM_TYPE(TESObjectWEAP);

	WEAPON_TYPE GetWeaponType() const;
	void SetWeaponType(WEAPON_TYPE aeType);

	uint8_t GetAmmoPerShot() const;
	void SetAmmoPerShot(uint8_t aucVal);

	ActorValue::Index GetWeaponSkill() const;
	void SetWeaponSkill(ActorValue::Index aeIndex);

	bool IsMeleeWeapon() const;
	bool IsRangedWeapon() const;
	bool IsGunWeapon() const;
	bool IsThrownWeapon() const;

	bool GetIgnoreResist() const;
	void SetIgnoreResist(bool abVal);

	bool GetIsAutomaticWeapon() const;
	void SetIsAutomaticWeapon(bool abVal);

	bool GetHasScope() const;
	void SetHasScope(bool abVal);

	bool GetCantDrop() const;
	void SetCantDrop(bool abVal);

	bool GetHideBackpack() const;
	void SetHideBackpack(bool abVal);

	bool GetIsEmbeddedWeapon() const;
	void SetIsEmbeddedWeapon(bool abVal);

	bool GetUse1stPersonISAnims() const;
	void SetUse1stPersonISAnims(bool abVal);

	bool GetIsPlayable() const;
	void SetIsPlayable(bool abVal);

	bool GetIsPlayerOnly() const;
	void SetIsPlayerOnly(bool abVal);

	bool GetNPCsUseAmmo() const;
	void SetNPCsUseAmmo(bool abVal);

	bool GetNoJamAfterReload() const;
	void SetNoJamAfterReload(bool abVal);

	bool GetOverrideAP() const;
	void SetOverrideAP(bool abVal);

	bool GetIsMinorCrime() const;
	void SetIsMinorCrime(bool abVal);

	bool GetIsRangeFixed() const;
	void SetIsRangeFixed(bool abVal);

	bool GetPreventUseInNormalCombat() const;
	void SetPreventUseInNormalCombat(bool abVal);

	bool GetOverrideDamageToWeaponMult() const;
	void SetOverrideDamageToWeaponMult(bool abVal);

	bool GetUse3rdPersonISAnims() const;
	void SetUse3rdPersonISAnims(bool abVal);

	bool GetBurstShot() const;
	void SetBurstShot(bool abVal);

	bool GetAlternateRumble() const;
	void SetAlternateRumble(bool abVal);

	bool GetLongVATSBurst() const;
	void SetLongVATSBurst(bool abVal);

	bool GetHasNightScope() const;
	void SetHasNightScope(bool abVal);

	bool GetHasModScope() const;
	void SetHasModScope(bool abVal);

	uint16_t GetCriticalDamage() const;
	void SetCriticalDamage(uint16_t ausVal);

	float GetCriticalChanceMult() const;
	void SetCriticalChanceMult(float afVal);

	bool GetCriticalEffectOnDeath() const;
	void SetCriticalEffectOnDeath(bool abVal);

	SpellItem* GetCriticalEffect() const;
	void SetCriticalEffect(SpellItem* apEffect);

	TESModel* GetWorldTESModel() const;
	TESModel* GetModTESModel(uint8_t aucSlots, bool abAllowMeleeMods) const;

	const TESModel* GetShellCasingModel() const;
	TESModel* GetShellCasingModel();

	const TESModel* GetScopeModel() const;
	TESModel* GetScopeModel();

	TESEffectShader* GetScopeEffect() const;
	void SetScopeEffect(TESEffectShader* apEffect);

	TESSound* GetAttackSound(bool abModded) const;
	void SetAttackSound(TESSound* apSound);

	TESSound* GetDistantAttackSound(bool abModded) const;
	void SetDistantAttackSound(TESSound* apSound);

	TESSound* GetAttackSound2D(bool abModded) const;
	void SetAttackSound2D(TESSound* apSound);

	TESSound* GetAttackFailSound() const;
	void SetAttackFailSound(TESSound* apSound);

	TESSound* GetMeleeBlockSound() const;
	void SetMeleeBlockSound(TESSound* apSound);

	TESSound* GetIdleSound() const;
	void SetIdleSound(TESSound* apSound);

	TESSound* GetEquipSound() const;
	void SetEquipSound(TESSound* apSound);

	TESSound* GetUnequipSound() const;
	void SetUnequipSound(TESSound* apSound);

	TESSound* GetModAttackSound() const;
	void SetModAttackSound(TESSound* apSound);

	TESSound* GetModDistantAttackSound() const;
	void SetModDistantAttackSound(TESSound* apSound);

	TESSound* GetModAttackSound2D() const;
	void SetModAttackSound2D(TESSound* apSound);

	ANIM_GROUP_TYPE GetHandGripAnim() const;
	void SetHandGripAnim(ANIM_GROUP_TYPE aeAnim);

	ANIM_GROUP_TYPE GetAttackAnim() const;
	void SetAttackAnim(ANIM_GROUP_TYPE aeAnim);

	ANIM_GROUP_TYPE GetReloadAnim(bool abModValue) const;
	void SetReloadAnim(ANIM_GROUP_TYPE aeAnim);
	void SetModReloadAnim(ANIM_GROUP_TYPE aeAnim);
	
	BGSImpactDataSet* GetImpactDataSet() const;
	void SetImpactDataSet(BGSImpactDataSet* apSet);

	TESObjectSTAT* Get1stPersonObject() const;
	void Set1stPersonObject(TESObjectSTAT* apObject);

	TESObjectSTAT* Get1stPersonModObject(uint8_t aucSlots) const;
	void Set1stPersonModObject(uint8_t aucSlots, TESObjectSTAT* apObject);
	
	TESObjectIMOD* GetModItem(ModSlot aeSlot) const;
	void SetModItem(ModSlot aeSlot, TESObjectIMOD* apMod);

	const char* GetEmbeddedWeaponNode() const;
	void SetEmbeddedWeaponNode(const char* apNodeName);

	SOUND_LEVEL GetSoundLevel(bool abModded) const;
	void SetSoundLevel(SOUND_LEVEL aeLevel);
#ifdef GAME
	int32_t GetSoundLevelValue(bool abSilent, bool abSilencer) const;
#endif

	SpellItem* GetVATSSpecialAttackEffect() const;
	void SetVATSSpecialAttackEffect(SpellItem* apEffect);

	float GetVATSSpecialAttackSkillRequirement() const;
	void SetVATSSpecialAttackSkillRequirement(float afVal);

	float GetVATSSpecialAttackAPCost() const;
	void SetVATSSpecialAttackAPCost(float afVal);

	float GetVATSSpecialAttackDamageMultiplier() const;
	void SetVATSSpecialAttackDamageMultiplier(float afVal);

	bool GetVATSSpecialAttackSilent() const;
	void SetVATSSpecialAttackSilent(bool abVal);

	bool GetVATSSpecialAttackModRequirement() const;
	void SetVATSSpecialAttackModRequirement(bool abVal);

#ifdef GAME
	BGSProjectile* GetProjectile(ActorValueOwner* apActorValueOwner) const;
#endif
	BGSProjectile* GetProjectile(Actor* apActor) const;

	TESAmmo* GetCurrentAmmo(Actor* apActor) const;

	COMBAT_WEAPON_TYPE GetCombatWeaponType() const;

	float GetModValue(ModSlot aeSlot, uint8_t aucValue) const;

	float GetModEffectValue(WEAPON_MOD_EFFECT_TYPE aeEffect, uint8_t aucValue) const;

	float GetWeight(bool abModded);

#ifdef GAME
	void EjectShellCasing(TESObjectREFR* apReference);
#endif
};

#ifdef GAME
ASSERT_SIZE(TESObjectWEAP, 0x388);
#else
ASSERT_SIZE(TESObjectWEAP, 0x470);
#endif