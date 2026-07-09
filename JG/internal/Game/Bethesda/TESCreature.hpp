#pragma once

#include "TESActorBase.hpp"
#include "TESAttackDamageForm.hpp"
#include "TESModelList.hpp"
#include "CreatureSounds.hpp"

class BGSImpactDataSet;
class BGSListForm;

class TESCreature : public TESActorBase, public TESAttackDamageForm, public TESModelList {
public:
	TESCreature();
	~TESCreature();

	struct Data {
		int8_t	eType;
		uint8_t	ucCombatSkill;
		uint8_t	ucMagicSkill;
		uint8_t	ucStealthSkill;
	};

	union {
		TESCreature*	__restrict pSoundCreature;
		CreatureSounds* __restrict pCreatureSounds;
	};
	Data				kData;	
	uint8_t				ucHandReach;		
	float				fTurningSpeed;		
	float				fFootWeight;
	float				fBaseScale;			
	TESCombatStyle*		pCombatStyle;		
	BGSBodyPartData*	pBodyPartData;		
	uint32_t			eBloodMaterialType;		
	BGSImpactDataSet*	pImpactDataSet;		
	bool				bEmbeddedWeaponChecked;
	SOUND_LEVEL			eSoundLevel;			
	BGSListForm*		pWeapons;
	int8_t				cCanUseHandToHand;

	TESFORM_TYPE(TESCreature);

	TESCreature* GetSoundCreature() const;
	void SetSoundCreature(TESCreature* apCreature);

	CreatureSounds* GetCreatureSounds() const;
	
	int8_t GetCreatureType() const;
	
	bool IsHumanoidCreature() const;

	uint8_t GetHandReach() const;
	void SetHandReach(uint8_t aucReach);

	float GetTurnSpeed() const;
	void SetTurnSpeed(float afSpeed);

	float GetFootWeight() const;
	void SetFootWeight(float afWeight);

	float GetBaseScale() const;
	void SetBaseScale(float afScale);

	BGSImpactDataSet* GetImpactDataSet() const;
	void SetImpactDataSet(BGSImpactDataSet* apSet);

	SOUND_LEVEL GetSoundLevel() const;
	int32_t GetSoundLevelValue() const;

	BGSListForm* GetWeaponList() const;
	void SetWeaponList(BGSListForm* apList);

	bool CanWearItem(TESForm* apForm) const;

	bool InitDefaultWorn(Actor* apActor, bool abAwake, bool abWeapon, bool abAllowChanges);
};

ASSERT_SIZE(TESCreature, 0x160);