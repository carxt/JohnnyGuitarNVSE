#pragma once

#include "MiddleLowProcess.hpp"
#include "BSCloneReserver.hpp"
#include "Gamebryo/NiPoint3.hpp"
#include "FurnitureMark.hpp"

class QueuedFile;
class QueuedItem;
class NiNode;
class MagicItem;
class BSFaceGenAnimationData;
class MagicTarget;
class Animation;
class BSAnimGroupSequence;
class BSBound;
class BSFaceGenNiNode;
class NiTriShape;
class LipSynchAnim;
class PatrolActorPackageData;

NiSmartPointer(BSShaderPPLightingProperty);

class MiddleHighProcess : public MiddleLowProcess {
public:
	MiddleHighProcess();
	~MiddleHighProcess();

	virtual void	SetAnimation(Animation* apAnimation);
	virtual bool	SetupPathFinding(Actor* apActor, NiPoint3 akTargetPos, TESObjectCELL* apTargetCell, TESWorldSpace* apTargetWorld);
	virtual void	SetAnimationActiveFlag(bool abActivate);
	virtual void	ResetTarget();
	virtual void	ProcessBuyObject(Actor* apActor);
	virtual void	ProcessSteal(Actor* apActor);
	virtual void	ProcessPickpocket(Actor* apActor);
	virtual void	ProcessDialogue(Actor* apActor);
	virtual void	ProcessDialogueActivate(Actor* apActor);
	virtual bool	ProcessUseFurniture(Actor* apActor, TESObjectREFR* apFurniture);
	virtual void	ProcessRemoveWornAlt(Actor* apActor, bool abIterateIndex, bool);
	virtual void	ProcessWander(Actor* apActor, NiPoint3* apPos, float afRadius = -1.f);
	virtual bool	ProcessSandboxDialogue(Actor* apActor, TESObjectREFR* apTarget);
	virtual void	ProcessPatrolInit(Actor* apActor, PatrolActorPackageData* apData);
	virtual void	ProcessPatrolStartTravelToNextRef(Actor* apActor, PatrolActorPackageData* apData);
	virtual void	ProcessPatrolTravelingToNextRef(Actor* apActor, PatrolActorPackageData* apData);
	virtual void	ProcessPatrolStartAtRefBehavior(Actor* apActor, PatrolActorPackageData* apData);
	virtual void	ProcessPatrolAtRef(Actor* apActor, PatrolActorPackageData* apData);
	virtual void	ProcessUseIdleMarker(Actor* apActor, TESObjectREFR* apTarget);
	virtual bool	ProcessAccompanyOneHour(Actor* apActor);

	BSSimpleList<TESObjectREFR*>		kDetectedDead;
	BSSimpleList<TESObjectREFR*>		kChairAndBeds;
	float								fPursueTimer;
	float								fEquippedWeight;
	bool								bDoneOnce;
	bool								bAimingTarget;
	bool								bNeedReparentWeapon;
	bool								bDrawn;
	ActorPackage						kRunOncePackage;
	NiPoint3							kLastSeenTargetPosition;
	uint32_t							eUseItem;
	TESIdleForm*						pLastPlayedIdle;
	bool								bPickPackIdle;
	ItemChange*							pCurrentWeapon;
	ItemChange*							pCurrentAmmo;
	NiPointer<QueuedFile>				spWeaponPreload;
	BSCloneReserverPtr					spReserveProjectileClones;
	bool								bWeaponGrenade;
	bool								bWeaponMine;
	bool								bWeaponThrown;
	bool								bHeavyArmorWorn;
	bool								bPowerArmorWorn;
	bool								bPowerArmorHelmet;
	bool								bHasBackPackWorn;
	NiNode*								pWeaponNode;
	NiAVObject*							pFireNode;
	bool								bWantWeaponDrawn;
	bool								bWeaponDrawn;
	NiPointer<bhkCharacterController>	spCharController;
	int8_t								eKnockedState;
	uint8_t								eSitSleepState;
	TESObjectREFR*						pCurrentFurniture;
	uint8_t								ucCurrentFurnitureIndex;
	FurnitureMark						kFurnitureMarker;
	Actor*								pCommandingActor;
	TESObjectWEAP*						pLastBoundWeapon;
	MagicItem*							pCurrentSpell;
	MagicItem*							pCurrentPackageSpell;
	bool								bCheckMagicNode;
	TESEffectShader*					pCurrentWeaponEffect;
	float								fAlphaMult;
	float								fScriptRefractPower;
	BSFaceGenAnimationData*				pFaceAnimationData;
	bool								bRefreshMagicShaderEffects;
	bool								bRefreshMagicShaderEffectBody;
	bool								bRefreshMagicShaderEffectWeapon;
	bool								bRefreshMagicShaderEffectLoading;
	bool								bRefreshFlareFlags;
	Bitfield32							uiFlareFlags;
	bool								bPickPocketed;
	bool								bDoneClothesChange;
	bool								bDetectLifeDetected;
	bool								bSummonedCreature;
	Bitfield<_Update3DFlags>			uc3DUpdateFlags;
	bool								bForceNextUpdate;
	int32_t								iPackageIdleNumber;
	TESIdleForm*						pCurrentIdle;
	float								fPackageIdleTimer;
	bool								bPlayedBeginIdles;
	bool								bPlayedEndIdles;
	LipSynchAnim*						pCreatureLipsynchAnim;
	uint32_t							uiCreatureLipsynchStartTime;
	int32_t								iReservationSlot;
	BSSimpleList<ArrowProjectile*>*		pAttachedArrows;
	BSSimpleList<void*>					kDeferredLimbHideList;
	BSSimpleList<ActiveEffect*>*		pActiveEffects;
	MagicTarget*						pDesiredTarget;
	Animation*							pAnimation;
	BSAnimGroupSequence*				pAimSequence[3];
	float								fAimLooking;
	float								fAutomaticShotDelay;
	uint8_t								ucShotsToFire;
	bool								bSustainedFire;
	bool								bBeenAttacked;
	NiNode*								pDamageRootNodes[15];
	NiAVObject*							pHeadNode;
	NiAVObject*							pTorsoNode;
	BSShaderPPLightingPropertyPtr		spLightingProperty;
	BSBound*							pBoundingBox;
	bool								bIronSights;
	int16_t								sAnimActionSuccess;
	int32_t								iMovementAnimations;
	BSSimpleList<QueuedItem*>*			pItemsToEquipUnequip;
	float								fRadiationDelta;
	float								fRadiationMagicDelta;
	float								fRadiationWaterDelta;
	HitData*							pLastHitData;
	int32_t								iWeaponConditionStage;
	BSFaceGenNiNode*					pFaceNode;
	BSFaceGenNiNode*					pFaceNodeSkinned;
	NiAVObject*							pAnimFace;
	HitData*							pLastAttackHitData;
	uint32_t							uiFurnitureListTimer;
};

ASSERT_SIZE(MiddleHighProcess, 0x25C);