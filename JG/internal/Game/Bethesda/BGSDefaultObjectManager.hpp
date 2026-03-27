#pragma once

#include "TESForm.hpp"

struct DefaultObjectData {
	const char* pName;
	uint8_t		eType;
};

class BGSDefaultObjectManager : public TESForm {
public:
	BGSDefaultObjectManager();
	~BGSDefaultObjectManager();

	enum DefaultObjects {
		STIMPAK						= 0,
		SUPER_STIMPAK				= 1,
		RADX						= 2,
		RADAWAY						= 3,
		MORPHINE					= 4,
		PERK_PARALYSIS				= 5,
		PLAYER_FACTION				= 6,
		MYSTERIOUS_STRANGER_NPC		= 7,
		MYSTERIOUS_STRANGER_FACTION	= 8,
		DEFAULT_MUSIC				= 9,
		BATTLE_MUSIC				= 10,
		DEATH_MUSIC					= 11,
		SUCCESS_MUSIC				= 12,
		LEVEL_UP_MUSIC				= 13,
		PLAYER_VOICE_MALE			= 14,
		PLAYER_VOICE_MALE_CHILD		= 15,
		PLAYER_VOICE_FEMALE			= 16,
		PLAYER_VOICE_FEMALE_CHILD	= 17,
		EAT_PACKAGE_DEFAULT_FOOD	= 18,
		EVERY_ACTOR_ABILITY			= 19,
		DRUG_WEARS_OFF_IMAGESPACE	= 20,
		DOCTORS_BAG					= 21,
		MISS_FORTUNE_NPC			= 22,
		MISS_FORTUNE_FACTION		= 23,
		MELTDOWN_EXPLOSION			= 24,
		UNARMED_FORWARD_PA			= 25,
		UNARMED_BACKWARD_PA			= 26,
		UNARMED_LEFT_PA				= 27,
		UNARMED_RIGHT_PA			= 28,
		UNARMED_CROUCH_PA			= 29,
		UNARMED_COUNTER_PA			= 30,
		SPOTTER_EFFECT				= 31,
		ITEM_DETECTED_EFFECT		= 32,
		CATEYE_MOBILE_EFFECT_NYI	= 33,
		MAX							= 34,
	};

	union {
		struct {
			TESForm* pStimpak;
			TESForm* pSuperStimpak;
			TESForm* pRadX;
			TESForm* pRadAway;
			TESForm* pMorphine;
			TESForm* pPerkParalysis;
			TESForm* pPlayerFaction;
			TESForm* pMysteriousStranger;
			TESForm* pMysteriousStrangerFaction;
			TESForm* pDefaultMusic;
			TESForm* pBattleMusic;
			TESForm* pDefaultDeath;
			TESForm* pSuccessMusic;
			TESForm* pLevelUpMusic;
			TESForm* pPlayerVoiceMale;
			TESForm* pPlayerVoiceMaleChild;
			TESForm* pPlayerVoiceFemale;
			TESForm* pPlayerVoiceFemaleChild;
			TESForm* pEatPackageDefaultFood;
			TESForm* pEveryActorAbility;
			TESForm* pDrugWearOffImageSpace;
			// FNV
			TESForm* pDoctorsBag;
			TESForm* pMissFortuneNPC;
			TESForm* pMissFortuneFaction;
			TESForm* pMeltdownExplosion;
			TESForm* pUnarmedForwardPA;
			TESForm* pUnarmedBackwardPA;
			TESForm* pUnarmedLeftPA;
			TESForm* pUnarmedRightPA;
			TESForm* pUnarmedCrouchPA;
			TESForm* pUnarmedCounterPA;
			TESForm* pSpotterEffect;
			TESForm* pItemDetectedEffect;
			TESForm* pCateyeMobileEffectNYI;
		};
		TESForm* pForms[MAX];
	};

	TESFORM_TYPE(BGSDefaultObjectManager);
	
	static BGSDefaultObjectManager* GetSingleton();

	static TESForm* GetItem(DefaultObjects aeObject);
};

ASSERT_SIZE(BGSDefaultObjectManager, 0xA0);