#include "fn_hit.h"

#include "Bethesda/BSEnums.hpp"
#include "Bethesda/BSUtilities.hpp"
#include "Bethesda/TESDataHandler.hpp"
#include "Gamebryo/NiFixedString.hpp"

#include <GameForms.h>
#include <GameObjects.h>
#include <GameProcess.h>
#include <GameSound.h>
#include <netimmerse.h>
#include <decoding.h>

#include <JG/PlayerBodyOverlay.hpp>

#include <cstddef>
#include <cmath>
#include <cstring>
#include <limits>

namespace {

using ImpactSwap = TESWorldSpace::ImpactSwap;

static_assert(BHK_MATERIAL_MASK_FIXED == 0x3F);

constexpr uintptr_t kAddrCreateTempEffectParticle = 0x6890B0;
constexpr uintptr_t kAddrDecalManagerSingleton = 0x11C57F8;
constexpr uintptr_t kAddrAddDecal = 0x4A10D0;
constexpr uintptr_t kAddrMergeScriptEvent = 0x5AC750;
constexpr uintptr_t kAddrSendAssaultAlarm = 0x8C0460;
constexpr uintptr_t kAddrGetMaterialFromCollidable = 0x62B150;
constexpr uintptr_t kAddrGetSubshapeMaterial = 0xC84F10;
constexpr uintptr_t kAddrGetCollisionFilter = 0x931ED0;
constexpr uintptr_t kAddrPick = 0x458440;
constexpr uintptr_t kAddrCalcPickHitPoint = 0x5DBE60;
constexpr uintptr_t kAddrVisitHavokObjects = 0xC68900;
constexpr uintptr_t kAddrClearAnimGroup = 0x496080;
constexpr uintptr_t kAddrSetAnimActionAndSequence = 0x8A73E0;
constexpr uintptr_t kAddrSetRigidBodyLinearVelocity = 0x561690;
constexpr uint32_t kActorDamageVtableSlot = 0xCE;
constexpr uint32_t kShapeGetContainerVtableSlot = 4;
constexpr uint32_t kShapeGetChildVtableSlot = 5;
constexpr uint32_t kRigidBodyCenterVtableSlot = 0xF0 / 4;

static_assert(sizeof(ActorHitData) == 0x64);
static_assert(offsetof(ActorHitData, source) == 0x00);
static_assert(offsetof(ActorHitData, target) == 0x04);
static_assert(offsetof(ActorHitData, unk0C) == 0x0C);
static_assert(offsetof(ActorHitData, hitLocation) == 0x10);
static_assert(offsetof(ActorHitData, healthDmg) == 0x14);
static_assert(offsetof(ActorHitData, wpnBaseDmg) == 0x18);
static_assert(offsetof(ActorHitData, fatigueDmg) == 0x1C);
static_assert(offsetof(ActorHitData, limbDmg) == 0x20);
static_assert(offsetof(ActorHitData, weapon) == 0x30);
static_assert(offsetof(ActorHitData, healthPerc) == 0x34);
static_assert(offsetof(ActorHitData, impactPos) == 0x38);
static_assert(offsetof(ActorHitData, impactAngle) == 0x44);
static_assert(offsetof(ActorHitData, flags) == 0x58);
static_assert(offsetof(ActorHitData, dmgMult) == 0x5C);
static_assert(sizeof(TESObjectWEAP) == 0x388);
static_assert(offsetof(TESObjectWEAP, weaponSkill) == 0x15C);
static_assert(offsetof(TESObjectWEAP, impactDataSet) == 0x24C);
static_assert(sizeof(BGSImpactData) == 0x78);
static_assert(offsetof(BGSImpactData, model) == 0x18);
static_assert(offsetof(BGSImpactData, effectDuration) == 0x30);
static_assert(offsetof(BGSImpactData, angleThreshold) == 0x38);
static_assert(offsetof(BGSImpactData, placementRadius) == 0x3C);
static_assert(offsetof(BGSImpactData, textureSet) == 0x48);
static_assert(offsetof(BGSImpactData, sound1) == 0x4C);
static_assert(offsetof(BGSImpactData, sound2) == 0x50);
static_assert(offsetof(BGSImpactData, decalMaxWidth) == 0x58);
static_assert(offsetof(BGSImpactData, decalMaxHeight) == 0x60);
static_assert(offsetof(BGSImpactData, decalDepth) == 0x64);
static_assert(offsetof(BGSImpactData, decalShininess) == 0x68);
static_assert(offsetof(BGSImpactData, parallaxScale) == 0x6C);
static_assert(offsetof(BGSImpactData, parallaxPasses) == 0x70);
static_assert(offsetof(BGSImpactData, decalFlags) == 0x71);
static_assert(offsetof(BGSImpactData, decalColor) == 0x74);
static_assert(sizeof(BGSImpactDataSet) == 0x4C);
static_assert(offsetof(BGSImpactDataSet, impactDatas) == 0x1C);
static_assert(sizeof(TESSound) == 0x68);
static_assert(offsetof(TESForm, uiFormID) == 0x0C);
static_assert(sizeof(BSSoundHandle) == 0x0C);
static_assert(offsetof(BSSoundHandle, uiSoundID) == 0x00);
static_assert(offsetof(TESNPC, impactMaterialType) == 0x1E4);
static_assert(offsetof(TESCreature, materialType) == 0x148);
static_assert(sizeof(Animation) == 0x12C);
static_assert(offsetof(Animation, unk0D8) == 0xD8);
static_assert(offsetof(Animation, animSequence) == 0xE0);
static_assert(offsetof(BaseProcess, processLevel) == 0x28);
static_assert(offsetof(HighProcess, animData) == 0x1C0);
static_assert(offsetof(HighProcess, currentAction) == 0x2EC);
static_assert(offsetof(TESObjectREFR, baseForm) == 0x20);
static_assert(offsetof(TESObjectREFR, pos) == 0x30);
static_assert(offsetof(TESObjectREFR, parentCell) == 0x40);
static_assert(offsetof(TESObjectREFR, extraDataList) == 0x44);
static_assert(offsetof(TESObjectREFR, renderState) == 0x64);
static_assert(offsetof(TESObjectREFR::RenderState, rootNode) == 0x14);
static_assert(offsetof(MobileObject, baseProcess) == 0x68);
static_assert(sizeof(NiAVObject) == 0x9C);
static_assert(offsetof(NiAVObject, m_spCollisionObject) == 0x1C);
static_assert(offsetof(NiAVObject, m_kWorld) == 0x68);

static bool IsFinite3(float afX, float afY, float afZ) {
	return std::isfinite(afX) && std::isfinite(afY) && std::isfinite(afZ);
}

static uint32_t BodyPartConditionAV(int32_t aiLocation) {
	switch (aiLocation) {
		case 1: case 2:				return kAVCode_PerceptionCondition;
		case 3: case 4:				return kAVCode_LeftAttackCondition;
		case 5: case 6:				return kAVCode_RightAttackCondition;
		case 7: case 8: case 9:		return kAVCode_LeftMobilityCondition;
		case 10: case 11: case 12:	return kAVCode_RightMobilityCondition;
		case 13:					return kAVCode_BrainCondition;
		default:					return kAVCode_EnduranceCondition;
	}
}

static const char* BodyPartNodeName(int32_t aiLocation) {
	switch (aiLocation) {
		case 1: case 2: case 13:	return "Bip01 Head";
		case 3:						return "Bip01 L UpperArm";
		case 4:						return "Bip01 L Forearm";
		case 5:						return "Bip01 R UpperArm";
		case 6:						return "Bip01 R Forearm";
		case 7:						return "Bip01 L Thigh";
		case 8:						return "Bip01 L Calf";
		case 9:						return "Bip01 L Foot";
		case 10:					return "Bip01 R Thigh";
		case 11:					return "Bip01 R Calf";
		case 12:					return "Bip01 R Foot";
		default:					return "Bip01 Spine2";
	}
}

static float BodyPartZOffset(int32_t aiLocation) {
	switch (aiLocation) {
		case 1: case 2: case 13:	return 120.0f;
		case 3: case 5:				return 100.0f;
		case 4: case 6:				return 85.0f;
		case 7: case 10:			return 50.0f;
		case 8: case 11:			return 25.0f;
		case 9: case 12:			return 5.0f;
		default:					return 80.0f;
	}
}

static NiPoint3 FallbackHitPos(Actor* apActor, int32_t aiLocation) {
	const NiPoint3& kPos = apActor->pos;
	return NiPoint3(kPos.x, kPos.y, kPos.z + BodyPartZOffset(aiLocation));
}

static NiPoint3 GetActorHitWorldPos(Actor* apActor, int32_t aiLocation, NiNode*& arRootOut) {
	// Get3DSimple, not Get3D. The player override returns the 1st person arms in 1st person.
	arRootOut = apActor->Get3DSimple();
	if (arRootOut) {
		if (NiAVObject* pBone = BSUtilities::GetObjectByName(arRootOut, BodyPartNodeName(aiLocation)))
			return pBone->m_kWorld.m_kTranslate;
	}
	return FallbackHitPos(apActor, aiLocation);
}

static NiPoint3 HitFXDirection(Actor* apAttacker, const NiPoint3& arPos) {
	if (!apAttacker)
		return NiPoint3(0.0f, 1.0f, 0.0f);
	NiPoint3 kDir = apAttacker->pos - arPos;
	if (!IsFinite3(kDir.x, kDir.y, kDir.z))
		return NiPoint3(0.0f, 1.0f, 0.0f);
	const double fLenSq =
		static_cast<double>(kDir.x) * kDir.x +
		static_cast<double>(kDir.y) * kDir.y +
		static_cast<double>(kDir.z) * kDir.z;
	if (!std::isfinite(fLenSq) || fLenSq <= 0.00000001)
		return NiPoint3(0.0f, 1.0f, 0.0f);
	const float fInvLen = static_cast<float>(1.0 / std::sqrt(fLenSq));
	kDir.x *= fInvLen;
	kDir.y *= fInvLen;
	kDir.z *= fInvLen;
	return kDir;
}

// Keep the 0x3F mask. The engine helper drops materials 32 through 35.
static int32_t ConvertHavokMaterial(uint32_t auiRaw) {
	switch (static_cast<HavokMaterialType>(auiRaw & BHK_MATERIAL_MASK_FIXED)) {
		case BHK_MATERIAL_STONE:
		case BHK_MATERIAL_HEAVYSTONE:
		case BHK_MATERIAL_BROKENCONCRETE:		return ImpactSwap::eMT_Stone;
		case BHK_MATERIAL_DIRT:
		case BHK_MATERIAL_SAND:					return ImpactSwap::eMT_Dirt;
		case BHK_MATERIAL_GRASS:				return ImpactSwap::eMT_Grass;
		case BHK_MATERIAL_GLASS:
		case BHK_MATERIAL_BOTTLE:				return ImpactSwap::eMT_Glass;
		case BHK_MATERIAL_METAL:
		case BHK_MATERIAL_HEAVYMETAL:
		case BHK_MATERIAL_CHAIN:
		case BHK_MATERIAL_SNOW:
		case BHK_MATERIAL_ELEVATOR:
		case BHK_MATERIAL_VEHICLEBODY:
		case BHK_MATERIAL_VEHICLEPARTSOLID:
		case BHK_MATERIAL_PISTOL:
		case BHK_MATERIAL_RIFLE:
		case BHK_MATERIAL_CHAINLINK:			return ImpactSwap::eMT_Metal;
		case BHK_MATERIAL_WOOD:
		case BHK_MATERIAL_HEAVYWOOD:
		case BHK_MATERIAL_BABYRATTLE:
		case BHK_MATERIAL_RUBBERBALL:			return ImpactSwap::eMT_Wood;
		case BHK_MATERIAL_ORGANIC:
		case BHK_MATERIAL_SKIN:					return ImpactSwap::eMT_Organic;
		case BHK_MATERIAL_CLOTH:
		case BHK_MATERIAL_CARPET:				return ImpactSwap::eMT_Cloth;
		case BHK_MATERIAL_WATER:				return ImpactSwap::eMT_Water;
		case BHK_MATERIAL_HOLLOWMETAL:
		case BHK_MATERIAL_SHEETMETAL:
		case BHK_MATERIAL_VEHICLEPARTHOLLOW:
		case BHK_MATERIAL_BARREL:
		case BHK_MATERIAL_SODACAN:
		case BHK_MATERIAL_SHOPPINGCART:
		case BHK_MATERIAL_LUNCHBOX:				return ImpactSwap::eMT_HollowMetal;
		case BHK_MATERIAL_TILE:					return ImpactSwap::eMT_Stone;
		case BHK_MATERIAL_TUMBLEWEED:			return ImpactSwap::eMT_Dirt;
		default:								return -1;
	}
}

static int32_t GetActorBodyMaterial(TESObjectREFR* apRef) {
	TESBoundObject* pBase = apRef->baseForm;
	if (!pBase)
		return -1;
	int32_t iMat = -1;
	if (pBase->eFormType == FORM_TYPE::TESNPC)
		iMat = static_cast<int32_t>(static_cast<TESNPC*>(pBase)->impactMaterialType);
	else if (pBase->eFormType == FORM_TYPE::TESCreature)
		iMat = static_cast<int32_t>(static_cast<TESCreature*>(pBase)->materialType);
	return (iMat >= 0 && iMat < ImpactSwap::eMT_Max) ? iMat : -1;
}

static void PlayImpactSound(TESSound* apSound, const NiPoint3& arPos, NiAVObject* apNode) {
	if (!apSound || !apSound->uiFormID)
		return;
	BSWin32Audio* pAudio = BSWin32Audio::GetSingleton();
	if (!pAudio)
		return;
	BSSoundHandle kHandle = pAudio->GetSoundHandleByFormID(
		apSound->uiFormID, BSAudioManager::kAudioFlags_3D | BSAudioManager::kAudioFlags_100);
	if (kHandle.uiSoundID == 0xFFFFFFFF)
		return;
	kHandle.SetPosition(arPos);
	if (apNode)
		kHandle.SetObjectToFollow(apNode);
	kHandle.Play(false);
}

static void PlayImpactParticle(TESObjectCELL* apCell, BGSImpactData* apImpact, const NiPoint3& arPos, const NiPoint3& arDir) {
	if (!apCell)
		return;
	const char* pModelPath = apImpact->model.GetModel();
	if (!pModelPath || !pModelPath[0])
		return;
	CdeclCall(kAddrCreateTempEffectParticle, apCell, apImpact->effectDuration,
		pModelPath, arDir, arPos, 1.0f, 7, nullptr);
}

struct GeometryDecalCreateData {
	NiPoint3		kWorldPos;
	NiPoint3		kRotation;
	NiPoint3		kPoint18;
	void*			pActor = nullptr;
	NiAVObject*		pNode = nullptr;
	uint32_t		uiUnk2C = 0;
	BGSTextureSet*	pTextureSet = nullptr;
	int32_t			iIndex = -1;
	float			fWidth = 0.0f;
	float			fHeight = 0.0f;
	float			fDepth = 0.0f;
	float			fRNG = 1.0f;
	TESObjectCELL*	pParentCell = nullptr;
	float			fParallaxScale = 0.0f;
	NiAVObject*		pSkinnedDecal = nullptr;
	float			fSpecular = 0.0f;
	float			fEpsilon = 0.0f;
	float			fPlacementRadius = 0.0f;
	float			fColorR = 0.0f;
	float			fColorG = 0.0f;
	float			fColorB = 0.0f;
	uint32_t		uiHitLocationFlags = 0;
	uint8_t			ucUVQuadrant = 0;
	uint8_t			ucByte71 = 0;
	uint8_t			ucByte72 = 0;
	uint8_t			ucParallax = 0;
	uint8_t			ucAlphaTest = 0;
	uint8_t			ucAlphaBlend = 0;
	uint8_t			ucParallaxPasses = 0;
	uint8_t			ucModelSpace = 0;
	uint8_t			ucForceFade = 0;
	uint8_t			ucTwoSided = 0;
	uint8_t			pad7A[2] = {};
};
static_assert(sizeof(GeometryDecalCreateData) == 0x7C);
static_assert(offsetof(GeometryDecalCreateData, pTextureSet) == 0x30);
static_assert(offsetof(GeometryDecalCreateData, pParentCell) == 0x48);
static_assert(offsetof(GeometryDecalCreateData, uiHitLocationFlags) == 0x6C);

static void AddActorBloodDecal(Actor* apTarget, NiAVObject* apNode, BGSImpactData* apImpact,
                               int32_t aiLocation, const NiPoint3& arPos, const NiPoint3& arDir) {
	void* pDecalManager = *reinterpret_cast<void**>(kAddrDecalManagerSingleton);
	if (!pDecalManager || !apNode || !apImpact->textureSet)
		return;

	GeometryDecalCreateData kData;
	kData.kWorldPos = arPos;
	kData.kRotation = arDir;
	kData.kPoint18 = arDir;
	kData.pActor = apTarget;
	kData.pNode = apNode;
	kData.pTextureSet = apImpact->textureSet;
	kData.fWidth = apImpact->decalMaxWidth;
	kData.fHeight = apImpact->decalMaxHeight;
	kData.fDepth = apImpact->decalDepth > 0.0f ? apImpact->decalDepth : 48.0f;
	kData.pParentCell = apTarget->parentCell;
	kData.fParallaxScale = apImpact->parallaxScale;
	kData.fSpecular = apImpact->decalShininess;
	kData.fEpsilon = apImpact->angleThreshold;
	kData.fPlacementRadius = apImpact->placementRadius;
	kData.fColorR = static_cast<float>(apImpact->decalColor & 0xFF) / 255.0f;
	kData.fColorG = static_cast<float>((apImpact->decalColor >> 8) & 0xFF) / 255.0f;
	kData.fColorB = static_cast<float>((apImpact->decalColor >> 16) & 0xFF) / 255.0f;
	kData.uiHitLocationFlags = 1u << aiLocation;
	kData.ucParallax = (apImpact->decalFlags & 1) ? 1 : 0;
	kData.ucAlphaBlend = (apImpact->decalFlags & 2) ? 1 : 0;
	kData.ucAlphaTest = (apImpact->decalFlags & 4) ? 1 : 0;
	kData.ucParallaxPasses = apImpact->parallaxPasses;
	kData.ucModelSpace = 1;

	ThisCall(kAddrAddDecal, pDecalManager, &kData, 2, false);
}

static void SpawnActorHitFX(Actor* apTarget, Actor* apAttacker, TESObjectWEAP* apWeapon,
                            int32_t aiLocation, int32_t aiMaterial, bool abBlood, bool abSound) {
	if ((!abBlood && !abSound) || !apWeapon || !apWeapon->impactDataSet || !apTarget->parentCell)
		return;
	if (aiMaterial < 0 || aiMaterial >= ImpactSwap::eMT_Max)
		return;
	BGSImpactData* pImpact = apWeapon->impactDataSet->impactDatas[aiMaterial];
	if (!pImpact)
		return;

	NiNode* pNode = nullptr;
	const NiPoint3 kPos = GetActorHitWorldPos(apTarget, aiLocation, pNode);
	const NiPoint3 kDir = HitFXDirection(apAttacker, kPos);

	if (abBlood) {
		PlayImpactParticle(apTarget->parentCell, pImpact, kPos, kDir);
		AddActorBloodDecal(apTarget, pNode, pImpact, aiLocation, kPos, kDir);
	}
	if (abSound) {
		PlayImpactSound(pImpact->sound1, kPos, pNode);
		PlayImpactSound(pImpact->sound2, kPos, pNode);
	}
}

static TESObjectWEAP* ResolveHitWeapon(TESForm* apForm) {
	if (apForm)
		return static_cast<TESObjectWEAP*>(apForm);
	TESObjectWEAP* pDefault = const_cast<TESObjectWEAP*>(pDefaultUnarmedWeapon.Get());
	return (pDefault && reinterpret_cast<TESForm*>(pDefault)->IsWeapon()) ? pDefault : nullptr;
}

}

bool Cmd_ApplyHitData_Execute(COMMAND_ARGS) {
	*result = 0;

	Actor* pAttacker = nullptr;
	float fHealth = 10.0f, fFatigue = 0.0f, fLimb = 0.0f;
	TESForm* pWeaponForm = nullptr;
	int32_t iHitLocation = 0;
	uint32_t uiFlags = 0, bFireOnHit = 1, bFireAlarm = 1, bFireBlood = 1, bFireSound = 1, bSkipClear = 0;

	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &pAttacker, &fHealth, &fFatigue, &fLimb, &pWeaponForm,
			&iHitLocation, &uiFlags, &bFireOnHit, &bFireAlarm, &bFireBlood, &bFireSound, &bSkipClear))
		return true;
	if (!thisObj)
		return true;
	if (!IsFinite3(fHealth, fFatigue, fLimb) || fHealth < 0.0f || fFatigue < 0.0f || fLimb < 0.0f)
		return true;

	if (iHitLocation < -1 || iHitLocation > 13)
		iHitLocation = -1;

	Actor* pTarget = static_cast<Actor*>(thisObj);
	if (!pTarget->IsActor() || !pTarget->baseProcess)
		return true;
	if (pAttacker && (!pAttacker->IsActor() || !pAttacker->baseProcess))
		return true;
	if (pWeaponForm && !pWeaponForm->IsWeapon())
		return true;

	TESObjectWEAP* pWeapon = ResolveHitWeapon(pWeaponForm);

	ActorHitData kHit = {};
	kHit.source = pAttacker;
	kHit.target = pTarget;
	kHit.unk0C = pWeapon ? pWeapon->weaponSkill : kAVCode_Unarmed;
	kHit.hitLocation = iHitLocation;
	kHit.healthDmg = fHealth;
	kHit.wpnBaseDmg = fHealth;
	kHit.fatigueDmg = fFatigue;
	kHit.limbDmg = fLimb;
	kHit.weapon = pWeapon;
	kHit.healthPerc = pWeapon ? 1.0f : 0.0f;
	kHit.impactPos = FallbackHitPos(pTarget, iHitLocation);
	kHit.impactAngle = pAttacker
		? HitFXDirection(pTarget, pAttacker->pos)
		: NiPoint3(0.0f, 0.0f, 1.0f);
	kHit.flags = uiFlags;
	kHit.dmgMult = 1.0f;

	BaseProcess* pProc = pTarget->baseProcess;
	bool bCopiedHitData = false;
	__try {
		pProc->CopyHitData(&kHit);
		bCopiedHitData = true;

		if (fHealth > 0.0f) {
			void** pVtbl = *reinterpret_cast<void***>(pTarget);
			ThisCall(reinterpret_cast<uintptr_t>(pVtbl[kActorDamageVtableSlot]),
				pTarget, fHealth, 0.0f, pAttacker);
		}

		if (fLimb > 0.0f && iHitLocation >= 0)
			pTarget->DamageActorValue(BodyPartConditionAV(iHitLocation), -fLimb, pAttacker);

		if (bFireOnHit) {
			ExtraDataList* pExtra = &pTarget->extraDataList;
			if (pAttacker)
				CdeclCall(kAddrMergeScriptEvent, pAttacker, pExtra, 0x80);
			if (pWeapon)
				CdeclCall(kAddrMergeScriptEvent, pWeapon, pExtra, 0x100);
		}

		if (bFireAlarm && pAttacker &&
				pAttacker == reinterpret_cast<Actor*>(PlayerCharacter::GetSingleton()))
			ThisCall(kAddrSendAssaultAlarm, pTarget, pAttacker, 0, 0);

		if (fFatigue > 0.0f)
			pTarget->DamageActorValue(kAVCode_Fatigue, -fFatigue, pAttacker);

		if (pWeaponForm && pWeapon && pWeapon->impactDataSet && (bFireBlood || bFireSound)) {
			int32_t iBloodLoc = (iHitLocation >= 0) ? iHitLocation : 0;
			int32_t iMaterial = GetActorBodyMaterial(pTarget);
			if (iMaterial < 0)
				iMaterial = ImpactSwap::eMT_Organic;
			SpawnActorHitFX(pTarget, pAttacker, pWeapon, iBloodLoc, iMaterial, bFireBlood != 0, bFireSound != 0);
		}

		if (!bSkipClear) {
			pProc->ResetHitData();
			bCopiedHitData = false;
		}

		*result = 1;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		if (bCopiedHitData) {
			__try {
				pProc->ResetHitData();
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {
			}
		}
	}
	return true;
}

namespace {

static const float kGameToHavok = 0.142875f;

struct __declspec(align(16)) PickRayData {
	float		fFrom[4];
	float		fTo[4];
	uint8_t		ucEnableShapeCollectionFilter;
	uint8_t		pad21[3];
	uint32_t	uiFilterInfo;
	uint32_t	pad28[6];
	float		fHitFraction;
	uint32_t	uiExtraInfo;
	uint32_t	pad48[2];
	uint32_t	uiShapeKeys[8];
	int32_t		iShapeKeyIndex;
	uint32_t	pad74[3];
	void*		pRootCollidable;
	uint32_t	pad84[3];
	float		fLength[4];
	char*		pCache;
	void*		pClosestCollector;
	void*		pAllCollector;
	uint8_t		ucFailed;
	uint8_t		padAD[3];
};
static_assert(sizeof(PickRayData) == 0xB0);
static_assert(offsetof(PickRayData, fHitFraction) == 0x40);
static_assert(offsetof(PickRayData, uiShapeKeys) == 0x50);
static_assert(offsetof(PickRayData, pRootCollidable) == 0x80);
static_assert(sizeof(hkCdBody) == 0x10);
static_assert(offsetof(hkpWorldObject, cdBody) == 0x10);
static_assert(offsetof(hkpWorldObject, collisionType) == 0x28);
static_assert(offsetof(hkpShape, shape) == 0x08);
static_assert(offsetof(bhkShape, unk10) == 0x10);
static_assert(sizeof(bhkRefObject) == 0x0C);
static_assert(offsetof(bhkRefObject, refObject) == 0x08);
static_assert(sizeof(bhkNiCollisionObject) == 0x14);
static_assert(offsetof(bhkNiCollisionObject, worldObj) == 0x10);

struct CollisionFilter {
	uint32_t uiFilter = 0;
};
static_assert(sizeof(CollisionFilter) == 4);

static int32_t CollidableRootMaterial(const void* apCollidable, const NiPoint3* apPos) {
	return ConvertHavokMaterial(CdeclCall<uint32_t>(
		kAddrGetMaterialFromCollidable, apCollidable, apPos));
}

static bhkShape* ShapeGetBhk(const hkpShape* apHkpShape) {
	return apHkpShape ? apHkpShape->shape : nullptr;
}

static int32_t BhkShapeMaterial(const bhkShape* apBhkShape) {
	return apBhkShape ? ConvertHavokMaterial(apBhkShape->unk10) : -1;
}

static int32_t BhkShapeSubMaterial(bhkShape* apBhkShape, uint32_t auiShapeKey) {
	return ConvertHavokMaterial(ThisCall<uint32_t>(
		kAddrGetSubshapeMaterial, apBhkShape, auiShapeKey));
}

static void* HkpShapeContainer(void* apShape) {
	if (!apShape)
		return nullptr;
	void** pVtbl = *reinterpret_cast<void***>(apShape);
	return ThisCall<void*>(reinterpret_cast<uintptr_t>(
		pVtbl[kShapeGetContainerVtableSlot]), apShape);
}

static void* HkpContainerChild(void* apContainer, uint32_t auiKey, void* apBuffer) {
	if (!apContainer)
		return nullptr;
	void** pVtbl = *reinterpret_cast<void***>(apContainer);
	return ThisCall<void*>(reinterpret_cast<uintptr_t>(
		pVtbl[kShapeGetChildVtableSlot]), apContainer, auiKey, apBuffer);
}

static int32_t ChildShapeMaterial(void* apContainer, uint32_t auiKey, void* apBuffer) {
	hkpShape* pChildShape = static_cast<hkpShape*>(HkpContainerChild(apContainer, auiKey, apBuffer));
	bhkShape* pChildBhk = ShapeGetBhk(pChildShape);
	return pChildBhk ? BhkShapeMaterial(pChildBhk) : -1;
}

struct MaterialCandidates {
	int32_t iChildBest = -1;
	int32_t iChildFallback = -1;
	int32_t iSubBest = -1;
	int32_t iSubFallback = -1;
};

static void NoteMaterialCandidate(int32_t aiMat, int32_t& arBest, int32_t& arFallback) {
	if (aiMat > 0 && arBest < 0)
		arBest = aiMat;
	if (aiMat >= 0 && arFallback < 0)
		arFallback = aiMat;
}

static void ProbeShapeKey(void* apContainer, bhkShape* apBhkShape, uint32_t auiKey,
                          void* apChildBuffer, MaterialCandidates& arCandidates) {
	if (auiKey == 0xFFFFFFFF)
		return;
	if (apContainer) {
		NoteMaterialCandidate(ChildShapeMaterial(apContainer, auiKey, apChildBuffer),
			arCandidates.iChildBest, arCandidates.iChildFallback);
		if (arCandidates.iChildBest > 0)
			return;
	}
	NoteMaterialCandidate(BhkShapeSubMaterial(apBhkShape, auiKey),
		arCandidates.iSubBest, arCandidates.iSubFallback);
}

static uint32_t PlayerCollisionGroup() {
	PlayerCharacter* pPlayer = PlayerCharacter::GetSingleton();
	if (!pPlayer)
		return 0;
	CollisionFilter kFilter;
	ThisCall(kAddrGetCollisionFilter, pPlayer, &kFilter);
	return kFilter.uiFilter & 0xFFFF0000;
}

static int32_t ChooseMaterial(int32_t aiHitMat, const MaterialCandidates& arCandidates) {
	if (arCandidates.iChildBest > 0)		return arCandidates.iChildBest;
	if (arCandidates.iSubBest > 0)			return arCandidates.iSubBest;
	if (aiHitMat > 0)						return aiHitMat;
	if (arCandidates.iChildFallback >= 0)	return arCandidates.iChildFallback;
	if (arCandidates.iSubFallback >= 0)		return arCandidates.iSubFallback;
	return (aiHitMat >= 0) ? aiHitMat : -1;
}

static int32_t RaycastSubshapeMaterial(float afCamX, float afCamY, float afCamZ,
                                       float afHitX, float afHitY, float afHitZ, int32_t aiLayer) {
	PickRayData kPick = {};
	kPick.fFrom[0] = afCamX * kGameToHavok;
	kPick.fFrom[1] = afCamY * kGameToHavok;
	kPick.fFrom[2] = afCamZ * kGameToHavok;
	const double fEndX64 = afCamX + (static_cast<double>(afHitX) - afCamX) * 1.05;
	const double fEndY64 = afCamY + (static_cast<double>(afHitY) - afCamY) * 1.05;
	const double fEndZ64 = afCamZ + (static_cast<double>(afHitZ) - afCamZ) * 1.05;
	if (!std::isfinite(fEndX64) || !std::isfinite(fEndY64) || !std::isfinite(fEndZ64) ||
			std::fabs(fEndX64) > std::numeric_limits<float>::max() ||
			std::fabs(fEndY64) > std::numeric_limits<float>::max() ||
			std::fabs(fEndZ64) > std::numeric_limits<float>::max())
		return -1;
	const float fEndX = static_cast<float>(fEndX64);
	const float fEndY = static_cast<float>(fEndY64);
	const float fEndZ = static_cast<float>(fEndZ64);
	kPick.fTo[0] = fEndX * kGameToHavok;
	kPick.fTo[1] = fEndY * kGameToHavok;
	kPick.fTo[2] = fEndZ * kGameToHavok;
	if (!IsFinite3(kPick.fFrom[0], kPick.fFrom[1], kPick.fFrom[2]) ||
			!IsFinite3(kPick.fTo[0], kPick.fTo[1], kPick.fTo[2]))
		return -1;
	kPick.fHitFraction = 1.0f;
	kPick.uiExtraInfo = 0xFFFFFFFF;
	kPick.uiShapeKeys[0] = 0xFFFFFFFF;

	__try {
		kPick.uiFilterInfo = static_cast<uint32_t>(aiLayer) | PlayerCollisionGroup();

		TES* pTES = TES::GetSingleton();
		if (!pTES)
			return -1;
		if (!ThisCall<void*>(kAddrPick, pTES, &kPick, 1))
			return -1;

		void* pRoot = kPick.pRootCollidable;
		if (!pRoot)
			return -1;

		float fFrac = kPick.fHitFraction;
		if (fFrac < 0.0f || fFrac > 1.0f)
			fFrac = 1.0f;

		const double fPickX = afCamX + (fEndX64 - afCamX) * fFrac;
		const double fPickY = afCamY + (fEndY64 - afCamY) * fFrac;
		const double fPickZ = afCamZ + (fEndZ64 - afCamZ) * fFrac;
		if (!std::isfinite(fPickX) || !std::isfinite(fPickY) || !std::isfinite(fPickZ) ||
				std::fabs(fPickX) > std::numeric_limits<float>::max() ||
				std::fabs(fPickY) > std::numeric_limits<float>::max() ||
				std::fabs(fPickZ) > std::numeric_limits<float>::max())
			return -1;
		NiPoint3 kHitPos(
			static_cast<float>(fPickX),
			static_cast<float>(fPickY),
			static_cast<float>(fPickZ));
		ThisCall(kAddrCalcPickHitPoint, &kPick, &kHitPos);
		if (!IsFinite3(kHitPos.x, kHitPos.y, kHitPos.z))
			return -1;

		const int32_t iHitMat = CollidableRootMaterial(pRoot, &kHitPos);

		hkpShape* pRootShape = *reinterpret_cast<hkpShape**>(pRoot);
		bhkShape* pBhkShape = ShapeGetBhk(pRootShape);
		MaterialCandidates kCandidates;
		if (pBhkShape) {
			void* pContainer = HkpShapeContainer(pRootShape);
			__declspec(align(16)) uint8_t kChildBuffer[512];
			void* pChildBuffer = nullptr;
			if (pContainer) {
				std::memset(kChildBuffer, 0, sizeof(kChildBuffer));
				pChildBuffer = kChildBuffer;
			}
			for (int32_t i = 1; i <= 7; ++i) {
				ProbeShapeKey(pContainer, pBhkShape, kPick.uiShapeKeys[i], pChildBuffer, kCandidates);
				if (kCandidates.iChildBest > 0)
					break;
			}
			if (kCandidates.iChildBest <= 0)
				ProbeShapeKey(pContainer, pBhkShape, kPick.uiShapeKeys[0], pChildBuffer, kCandidates);
		}

		int32_t iChosen = ChooseMaterial(iHitMat, kCandidates);
		if (iChosen < 0) {
			NiPoint3 kScriptHitPos(afHitX, afHitY, afHitZ);
			const int32_t iScriptMat = CollidableRootMaterial(pRoot, &kScriptHitPos);
			if (iScriptMat >= 0)
				iChosen = iScriptMat;
		}
		return iChosen;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return -1;
	}
}

struct HavokRecData {
	void*		pWorld = nullptr;
	uint8_t		ucRecurse = 0;
	uint8_t		pad05[3] = {};
	uint32_t	uiAction = 0;
	uint32_t	uiData0 = 0;
	uint32_t	uiData1 = 0;
	int32_t		iOutMaterial = -1;
	uint32_t	uiData3 = 0;
};
static_assert(sizeof(HavokRecData) == 0x1C);
static_assert(offsetof(HavokRecData, uiAction) == 0x08);
static_assert(offsetof(HavokRecData, iOutMaterial) == 0x14);

static int32_t CollisionObjectMaterial(void* apCollisionObject) {
	if (!apCollisionObject)
		return -1;
	bhkNiCollisionObject* pCollision = static_cast<bhkNiCollisionObject*>(apCollisionObject);
	if (!pCollision->worldObj || !pCollision->worldObj->refObject)
		return -1;
	hkpWorldObject* pBody = static_cast<hkpWorldObject*>(pCollision->worldObj->refObject);
	hkpShape* pShape = static_cast<hkpShape*>(pBody->cdBody.shape);
	if (!pShape || !pShape->shape)
		return -1;
	return ConvertHavokMaterial(pShape->shape->unk10); // unk10 = havok material
}

static void __cdecl FirstMaterialCallback(void* apCollisionObject, HavokRecData* apData) {
	if (!apData || apData->iOutMaterial >= 0)
		return;
	const int32_t iMat = CollisionObjectMaterial(apCollisionObject);
	if (iMat >= 0)
		apData->iOutMaterial = iMat;
}

static int32_t GetObjectImpactMaterial(TESObjectREFR* apRef) {
	if (apRef->IsActor())
		return GetActorBodyMaterial(apRef);

	NiAVObject* pRoot = apRef->Get3D();
	if (!pRoot)
		return -1;
	HavokRecData kData;
	kData.ucRecurse = 1;
	kData.uiAction = 8;
	__try {
		CdeclCall(kAddrVisitHavokObjects, pRoot, &kData, FirstMaterialCallback);
		if (kData.iOutMaterial < 0)
			kData.iOutMaterial = CollisionObjectMaterial(pRoot->m_spCollisionObject);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return -1;
	}
	return kData.iOutMaterial;
}

}

bool Cmd_GetObjectMaterial_Execute(COMMAND_ARGS) {
	*result = -1;
	float fCamX = 3.0e38f, fCamY = 0.0f, fCamZ = 0.0f, fHitX = 0.0f, fHitY = 0.0f, fHitZ = 0.0f;
	int32_t iLayer = 6;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &fCamX, &fCamY, &fCamZ, &fHitX, &fHitY, &fHitZ, &iLayer))
		return true;
	if (!thisObj)
		return true;

	if (!std::isfinite(fCamX))
		return true;
	if (fCamX < 1.0e38f) {
		if (!IsFinite3(fCamX, fCamY, fCamZ) || !IsFinite3(fHitX, fHitY, fHitZ) ||
				iLayer < 0 || iLayer > 0x7F)
			return true;
		*result = RaycastSubshapeMaterial(fCamX, fCamY, fCamZ, fHitX, fHitY, fHitZ, iLayer);
	} else {
		*result = GetObjectImpactMaterial(thisObj);
	}
	return true;
}

bool Cmd_ApplyObjectImpact_Execute(COMMAND_ARGS) {
	*result = -1;

	int32_t iMaterial = -1;
	TESForm* pWeaponForm = nullptr;
	uint32_t bSound = 1, bParticle = 1;
	float fPosX = 3.0e38f, fPosY = 3.0e38f, fPosZ = 3.0e38f;

	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &iMaterial, &pWeaponForm, &bSound, &bParticle, &fPosX, &fPosY, &fPosZ))
		return true;
	if (!thisObj)
		return true;
	if (pWeaponForm && !pWeaponForm->IsWeapon())
		return true;
	if (!IsFinite3(fPosX, fPosY, fPosZ))
		return true;

	__try {
		TESObjectWEAP* pWeapon = ResolveHitWeapon(pWeaponForm);
		if (!pWeapon || !pWeapon->impactDataSet)
			return true;

		if (iMaterial < 0)
			iMaterial = GetObjectImpactMaterial(thisObj);
		if (iMaterial < 0 || iMaterial >= ImpactSwap::eMT_Max)
			return true;

		BGSImpactData* pImpact = pWeapon->impactDataSet->impactDatas[iMaterial];
		if (!pImpact)
			return true;

		NiPoint3 kPos = (fPosX > 1.0e38f || fPosY > 1.0e38f || fPosZ > 1.0e38f)
			? thisObj->pos
			: NiPoint3(fPosX, fPosY, fPosZ);
		const NiPoint3 kDir = HitFXDirection(
			reinterpret_cast<Actor*>(PlayerCharacter::GetSingleton()), kPos);

		if (bParticle)
			PlayImpactParticle(thisObj->parentCell, pImpact, kPos, kDir);
		if (bSound) {
			PlayImpactSound(pImpact->sound1, kPos, nullptr);
			PlayImpactSound(pImpact->sound2, kPos, nullptr);
		}
		*result = iMaterial;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
	}
	return true;
}

bool Cmd_InterruptWeaponAnim_Execute(COMMAND_ARGS) {
	*result = -2;
	if (!thisObj)
		return true;
	Actor* pActor = static_cast<Actor*>(thisObj);
	if (!pActor->IsActor() || !pActor->baseProcess)
		return true;
	if (pActor->baseProcess->processLevel != 0)
		return true;
	HighProcess* pProc = static_cast<HighProcess*>(pActor->baseProcess);

	Animation* pAnimation = pProc->animData;
	if (!pAnimation)
		return true;

	const int16_t sOldAction = pProc->currentAction;
	// Never clear an attack sequence. The queued melee task does not null-check it.
	if (sOldAction >= HighProcess::kAnimAction_Attack && sOldAction <= HighProcess::kAnimAction_Attack_Throw_Release) {
		*result = -3;
		return true;
	}

	__try {
		for (int32_t iSeq = 4; iSeq <= 6; ++iSeq) {
			if (BSAnimGroupSequence* pSequence = pAnimation->animSequence[iSeq])
				if (pAnimation->unk0D8)
					pAnimation->unk0D8->DeactivateSequence(pSequence, 0.0f);
			ThisCall(kAddrClearAnimGroup, pAnimation, iSeq, 0.0f);
		}
		ThisCall(kAddrSetAnimActionAndSequence, pActor, -1, nullptr);
		*result = sOldAction;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
	}
	return true;
}

namespace {

static const float kHavokToGame = 6.99903965f;
static_assert(sizeof(hkpWorldObject) == 0x8C);
static_assert(sizeof(hkpMotion) == 0x140);
static_assert(offsetof(hkpMotion, linVelocity) == 0xD0);
static_assert(sizeof(hkpRigidBody) == 0x220);
static_assert(offsetof(hkpRigidBody, motion) == 0xE0);
static_assert(sizeof(bhkWorldObject) == 0x14);
static_assert(offsetof(bhkWorldObject, refObject) == 0x08);
static_assert(sizeof(bhkRigidBody) == 0x1C);

static float* GetRigidBodyCenterOfMass(bhkWorldObject* apWorldObject, float* apOut) {
	void** pVtbl = *reinterpret_cast<void***>(apWorldObject);
	return ThisCall<float*>(reinterpret_cast<uintptr_t>(
		pVtbl[kRigidBodyCenterVtableSlot]), apWorldObject, apOut);
}

static void PushNodeBodies(NiAVObject* apObject, uint32_t auiDepth,
                           float afOriginX, float afOriginY, float afOriginZ,
                           float afForce, uint32_t& arCount) {
	if (!apObject || auiDepth > 64)
		return;
	NiNode* pNode = apObject->IsNode();
	if (!pNode)
		return;

	bhkNiCollisionObject* pCollision = pNode->m_spCollisionObject;
	bhkWorldObject* pWorldObj = pCollision ? pCollision->worldObj : nullptr;
	hkpRigidBody* pRigid = pWorldObj ? static_cast<hkpRigidBody*>(pWorldObj->refObject) : nullptr;
	if (pRigid && pRigid->collisionType == 1) {
		__declspec(align(16)) float kBodyPos[4];
		float* pPos = GetRigidBodyCenterOfMass(pWorldObj, kBodyPos);
		if (pPos && IsFinite3(pPos[0], pPos[1], pPos[2])) {
			double fDX = static_cast<double>(pPos[0]) * kHavokToGame - afOriginX;
			double fDY = static_cast<double>(pPos[1]) * kHavokToGame - afOriginY;
			double fDZ = static_cast<double>(pPos[2]) * kHavokToGame - afOriginZ;
			if (fDZ > 0.0)
				fDZ = 0.0;
			const double fLen = std::sqrt(fDX * fDX + fDY * fDY + fDZ * fDZ);
			if (std::isfinite(fLen) && fLen > 0.0001) {
				const double fScale = static_cast<double>(afForce) * kGameToHavok / fLen;
				NiPoint4 kVelocity = pRigid->motion.linVelocity;
				const float fNewX = static_cast<float>(kVelocity.x + fDX * fScale);
				const float fNewY = static_cast<float>(kVelocity.y + fDY * fScale);
				const float fNewZ = static_cast<float>(kVelocity.z + fDZ * fScale);
				if (IsFinite3(kVelocity.x, kVelocity.y, kVelocity.z) &&
						std::isfinite(kVelocity.w) && IsFinite3(fNewX, fNewY, fNewZ)) {
					kVelocity.x = fNewX;
					kVelocity.y = fNewY;
					kVelocity.z = fNewZ;
					ThisCall(kAddrSetRigidBodyLinearVelocity, pWorldObj, &kVelocity);
					++arCount;
				}
			}
		}
	}

	const uint32_t uiChildCount = pNode->GetArrayCount();
	if (uiChildCount > 1024)
		return;
	for (uint32_t i = 0; i < uiChildCount; ++i)
		if (NiAVObject* pChild = pNode->GetAt(i))
			PushNodeBodies(pChild, auiDepth + 1, afOriginX, afOriginY, afOriginZ, afForce, arCount);
}

}

bool Cmd_ApplyRagdollForce_Execute(COMMAND_ARGS) {
	*result = 0;
	float fForce = 0.0f, fOriginX = 0.0f, fOriginY = 0.0f, fOriginZ = 0.0f;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &fForce, &fOriginX, &fOriginY, &fOriginZ))
		return true;
	if (!thisObj)
		return true;
	if (!std::isfinite(fForce) || !IsFinite3(fOriginX, fOriginY, fOriginZ) || fForce == 0.0f)
		return true;
	Actor* pActor = static_cast<Actor*>(thisObj);
	if (!pActor->IsActor() || !pActor->baseProcess)
		return true;
	// Get3DSimple, not Get3D. The player override returns the 1st person arms in 1st person.
	NiAVObject* pRoot = pActor->Get3DSimple();
	if (!pRoot)
		return true;
	uint32_t uiCount = 0;
	__try {
		PushNodeBodies(pRoot, 0, fOriginX, fOriginY, fOriginZ, fForce, uiCount);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return true;
	}
	*result = uiCount;
	return true;
}

bool Cmd_Set3rdPersonOverlay_Execute(COMMAND_ARGS) {
	*result = PlayerBodyOverlay::IsEnabled() ? 1 : 0;
	uint32_t bEnable = 0;
	int32_t iDisableSuppressFrames = -1;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &bEnable, &iDisableSuppressFrames))
		return true;
	*result = PlayerBodyOverlay::SetEnabled(bEnable != 0, iDisableSuppressFrames);
	return true;
}

bool Cmd_Set3rdPersonOverlayCullParts_Execute(COMMAND_ARGS) {
	*result = PlayerBodyOverlay::GetCullPartBits();
	int32_t iMode = 0;
	int32_t kParts[16];
	for (int32_t i = 0; i < 16; ++i)
		kParts[i] = -1;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &iMode,
			&kParts[0], &kParts[1], &kParts[2], &kParts[3],
			&kParts[4], &kParts[5], &kParts[6], &kParts[7],
			&kParts[8], &kParts[9], &kParts[10], &kParts[11],
			&kParts[12], &kParts[13], &kParts[14], &kParts[15]))
		return true;

	const uint32_t uiBits = (iMode >= 1 && iMode <= 2) ? PlayerBodyOverlay::BuildPartBits(kParts, 16) : 0;
	PlayerBodyOverlay::SetCullParts(iMode, uiBits);
	*result = PlayerBodyOverlay::GetCullPartBits();
	return true;
}
