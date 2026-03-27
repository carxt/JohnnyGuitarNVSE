#pragma once

#include "BaseFormComponent.hpp"
#include "BSSimpleList.hpp"

class BGSVoiceType;
class TESFaction;
class TESForm;
class TESLevItem;
class FactionRank;

class TESActorBaseData : public BaseFormComponent {
public:
	TESActorBaseData();
	~TESActorBaseData();

	virtual void			CopyFromTemplateForm(TESForm* apForm);
	virtual bool			GetNoVATSmelee() const;
	virtual bool			GetAllowPCDialogue() const; 
	virtual bool			GetAllowPickpocket() const; 
	virtual bool			GetIsGhost() const;
	virtual bool			GetInvulnerable() const;
	virtual bool			GetCantOpenDoors() const;
	virtual bool			GetCanBeAllRaces() const;
	virtual bool			GetAutoCalcServiceFlags() const;
	virtual bool			GetNoPersuasion() const;
	virtual bool			GetNoLeftArm() const;
	virtual bool			GetNoRightArn() const;
	virtual bool			GetNoHead() const;
	virtual bool			GetNoShadow() const;
	virtual bool			GetNoBloodSpray() const;
	virtual void			SetNoBloodSpray(bool abVal);
	virtual bool			GetNoBloodDecal() const;
	virtual void			SetNoBloodDecal(bool abVal);
	virtual uint32_t		GetMaterialType() const;
	virtual void			SetMaterialType(uint32_t aeType);
	virtual uint32_t		GetFatigue() const;
	virtual float			GetKarma() const;
	virtual BGSVoiceType*	GetVoiceType() const;

	struct ALIGN4 _ActorBaseFlags {
		enum Flags : uint32_t {
			FEMALE						= 1u << 0,
			CREATURE_BIPED				= FEMALE,
			ESSENTIAL					= 1u << 1,
			HAS_CHARGEN_FACE			= 1u << 2,
			CREATURE_WEAPON_AND_SHIELD	= HAS_CHARGEN_FACE,
			RESPAWN						= 1u << 3,
			AUTOCALC_STATS				= 1u << 4,
			CREATURE_SWIMS				= AUTOCALC_STATS,
			CREATURE_FLIES				= 1u << 5,
			CREATURE_WALKS				= 1u << 6,
			PC_LEVEL_MULT				= 1u << 7,
			USE_TEMPLATE				= 1u << 8,
			NO_LOWLEVEL_PROCESSING		= 1u << 9,
			//							  1u << 10,
			NO_BLOOD_SPRAY				= 1u << 11,
			NO_BLOOD_DECAL				= 1u << 12,
			//							  1u << 13,
			//							  1u << 14,
			CREATURE_NO_HEAD			= 1u << 15,
			CREATURE_NO_RIGHT_ARM		= 1u << 16,
			CREATURE_NO_LEFT_ARM		= 1u << 17,
			CREATURE_NO_COMBAT_IN_WATER	= 1u << 18,
			CREATURE_NO_SHADOW			= 1u << 19,
			NO_VATS_MELEE				= 1u << 20,
			CREATURE_ALLOW_PC_DIALOGUE	= 1u << 21,
			CAN_BE_ALL_RACES			= 1u << 22,
			CREATURE_CANT_OPEN_DOOR		= CAN_BE_ALL_RACES,
			CREATURE_IMMOBILE			= 1u << 23,
			CREATURE_TILT_FRON_TBACK	= 1u << 24,
			CREATURE_TILT_LEFT_RIGHT	= 1u << 25,
			NO_KNOCKDOWNS				= 1u << 26,
			NOT_PUSHABLE				= 1u << 27,
			CREATURE_ALLOW_PICKPOCKET	= 1u << 28,
			CREATURE_IS_GHOST			= 1u << 29,
			NO_ROTATE_TO_HEADTRACK		= 1u << 30,
			CREATURE_INVULNERABLE		= 1u << 31,
		};

		struct ALIGN4 CreatureFlags {
			bool bBiped					: 1;
			bool bEssential				: 1;
			bool bHasWeaponAndShield	: 1;
			bool bRespawn				: 1;
			bool bSwims					: 1;
			bool bFlies					: 1;
			bool bWalks					: 1;
			bool bPCLevelMult			: 1;
			bool bUseTemplate			: 1;
			bool bNoLowLevelProcessing	: 1;
			bool 						: 1;
			bool bNoBloodSpray			: 1;
			bool bNoBloodDecal			: 1;
			bool 						: 1;
			bool 						: 1;
			bool bNoHead				: 1;
			bool bNoRightArm			: 1;
			bool bNoLeftArm				: 1;
			bool bNoCombatInWater		: 1;
			bool bNoShadow				: 1;
			bool bNoVATSMelee			: 1;
			bool bAllowPCDialogue		: 1;
			bool bCantOpenDoors			: 1;
			bool bImmobile				: 1;
			bool bTiltFrontBack			: 1;
			bool bTiltLeftRight			: 1;
			bool bNoKnockdowns			: 1;
			bool bNotPushable			: 1;
			bool bAllowPickpocket		: 1;
			bool bIsGhost				: 1;
			bool bNoRotateToHeadtrack	: 1;
			bool bInvulnerable			: 1;
		};

		struct ALIGN4 CharacterFlags {
			bool bFemale				: 1;
			bool bEssential				: 1;
			bool bChargenFace			: 1;
			bool bRespawn				: 1;
			bool bAutocalcStats			: 1;
			bool 						: 1;
			bool 						: 1;
			bool bPCLevelMult			: 1;
			bool bUseTemplate			: 1;
			bool bNoLowLevelProcessing	: 1;
			bool 						: 1;
			bool bNoBloodSpray			: 1;
			bool bNoBloodDecal			: 1;
			bool 						: 1;
			bool 						: 1;
			bool 						: 1;
			bool 						: 1;
			bool 						: 1;
			bool 						: 1;
			bool 						: 1;
			bool bNoVATSMelee			: 1;
			bool 						: 1;
			bool bCanBeAllRaces			: 1;
			bool 						: 1;
			bool 						: 1;
			bool 						: 1;
			bool bNoKnockdowns			: 1;
			bool bNotPushable			: 1;
			bool 						: 1;
			bool 						: 1;
			bool bNoRotateToHeadtrack	: 1;
			bool 						: 1;
		};

		union {
			CreatureFlags	uiCreature;
			CharacterFlags	uiCharacter;
		};

		const CreatureFlags& AsCreature() const { return uiCreature; }
		CreatureFlags&	AsCreature() { return uiCreature; }

		const CharacterFlags& AsCharacter() const { return uiCharacter; }
		CharacterFlags& AsCharacter() { return uiCharacter; }
	};
	using ActorBaseFlags = _ActorBaseFlags::Flags;
	using CreatureBaseFlags = _ActorBaseFlags::CreatureFlags;
	using CharacterBaseFlags = _ActorBaseFlags::CharacterFlags;

	struct ALIGN2 _TemplateUseFlags {
		enum Flags : uint16_t {
			TRAITS					= 1u << 0,
			STATS					= 1u << 1,
			FACTIONS				= 1u << 2,
			ACTOR_EFFECTS_LIST		= 1u << 3,
			AI_DATA					= 1u << 4,
			AI_PACKAGES				= 1u << 5,
			MODEL_ANIMATION			= 1u << 6,
			BASE_DATA				= 1u << 7,
			INVENTORY				= 1u << 8,
			SCRIPT					= 1u << 9,
			COPIED					= 1u << 15,
		};

		bool bTraits			: 1;
		bool bStats				: 1;
		bool bFactions			: 1;
		bool bActorEffectList	: 1;
		bool bAIData			: 1;
		bool bAIPackages		: 1;
		bool bModelAnimation	: 1;
		bool bBaseData			: 1;
		bool bInventory			: 1;
		bool bScript			: 1;
		bool 					: 1;
		bool 					: 1;
		bool 					: 1;
		bool 					: 1;
		bool 					: 1;
		bool bCopied			: 1;
	};
	using TemplateUseFlags = _TemplateUseFlags::Flags;

	struct ActorBaseData {
		Bitfield<_ActorBaseFlags>	uiFlags;
		uint16_t					usFatigue;
		uint16_t					usBarterGold;
		uint16_t					usLevel;
		uint16_t					usCalcLevelMin;
		uint16_t					usCalcLevelMax;
		uint16_t					usSpeedMultiplier;
		float						fKarma;
		uint16_t					usDispositionBase;
		Bitfield<_TemplateUseFlags>	usTemplateFlags;
	};

	ActorBaseData					kActorData;
	TESLevItem*						pDeathItem;
	BGSVoiceType*					pVoiceType;
	TESForm*						pTemplateForm;
	uint32_t						uiChangedFlags;
	BSSimpleList<FactionRank*>		kFactions;

	int8_t GetFactionRank(const TESFaction* apFaction, bool abCheckIfExpelled) const;

	const Bitfield<_ActorBaseFlags>& GetFlags() const { return kActorData.uiFlags; }
	Bitfield<_ActorBaseFlags>& GetFlags() { return kActorData.uiFlags; }

	const CharacterBaseFlags& GetBaseCharacterFlags() const { return kActorData.uiFlags.AsCharacter(); }
	CharacterBaseFlags& GetBaseCharacterFlags() { return kActorData.uiFlags.AsCharacter(); }

	const CreatureBaseFlags& GetBaseCreatureFlags() const { return kActorData.uiFlags.AsCreature(); }
	CreatureBaseFlags& GetBaseCreatureFlags() { return kActorData.uiFlags.AsCreature(); }

	bool GetFlag(ActorBaseFlags aeFlag) const { return kActorData.uiFlags.Get(aeFlag); }
	void SetFlag(ActorBaseFlags aeFlag, bool abVal) { kActorData.uiFlags.Set(aeFlag, abVal); }

	bool IsFemale() const { return GetBaseCharacterFlags().bFemale; }

	const BSSimpleList<FactionRank*>* GetFactionList() const;
	BSSimpleList<FactionRank*>* GetFactionList();

	bool GetUsesLeveledTemplate() const;

	static uint32_t GetAlignmentForKarma(float afKarma);
};

ASSERT_SIZE(TESActorBaseData, 0x34);