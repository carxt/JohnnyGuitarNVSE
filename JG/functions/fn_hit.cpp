#include "fn_hit.h"

#include "Bethesda/Animation.hpp"
#include "Bethesda/BSAudio.hpp"
#include "Bethesda/BSEnums.hpp"
#include "Bethesda/BSGameSound.hpp"
#include "Bethesda/BSUtilities.hpp"
#include "Bethesda/HighProcess.hpp"
#include "Bethesda/HitData.hpp"
#include "Bethesda/PlayerCharacter.hpp"
#include "Bethesda/TES.hpp"
#include "Bethesda/TESDataHandler.hpp"
#include "Gamebryo/NiNode.hpp"

#include <GameForms.h>
#include <netimmerse.h>
#include <decoding.h>

#include <JG/PlayerBodyOverlay.hpp>

#include <cstddef>
#include <cmath>
#include <cstring>
#include <limits>

namespace {

constexpr uintptr_t kAddrCreateTempEffectParticle = 0x6890B0;
constexpr uintptr_t kAddrDecalManagerSingleton = 0x11C57F8;
constexpr uintptr_t kAddrMergeScriptEvent = 0x5AC750;
constexpr uintptr_t kAddrSendAssaultAlarm = 0x8C0460;
constexpr uintptr_t kAddrGetMaterialFromCollidable = 0x62B150;
constexpr uintptr_t kAddrGetCollisionFilter = 0x931ED0;
constexpr uintptr_t kAddrPick = 0x458440;
constexpr uintptr_t kAddrCalcPickHitPoint = 0x5DBE60;
constexpr uintptr_t kAddrVisitHavokObjects = 0xC68900;
constexpr uintptr_t kAddrSetRigidBodyLinearVelocity = 0x561690;
constexpr uint32_t kShapeGetContainerVtableSlot = 4;
constexpr uint32_t kShapeGetChildVtableSlot = 5;
constexpr uint32_t kRigidBodyCenterVtableSlot = 0xF0 / 4;

static bool IsFinite3(float afX, float afY, float afZ) {
	return std::isfinite(afX) && std::isfinite(afY) && std::isfinite(afZ);
}

static NiPoint3 GetActorHitWorldPos(Actor* apActor, BODY_PART_TYPE aeLocation, NiAVObject** appRootOut) {
	// Get3DSimple, not Get3D. The player override returns the 1st person arms in 1st person.
	NiAVObject* pScene = apActor->Get3DSimple();
	if (appRootOut)
		*appRootOut = pScene;
	if (pScene) {
		NiAVObject* pBone = apActor->GetCurrentAIProcess()->GetDamageNode(aeLocation);
		if (pBone)
			return pBone->m_kWorld.m_kTranslate;

		return pScene->m_kWorld.m_kTranslate;
	}

	return NiPoint3::ZERO;
}

static NiPoint3 HitFXDirection(Actor* apAttacker, const NiPoint3& arPos) {
	if (!apAttacker)
		return NiPoint3::UNIT_Y;

	NiPoint3 kDir = apAttacker->GetPosition() - arPos;
	kDir.Unitize();
	if (kDir == NiPoint3::ZERO)
		return NiPoint3::UNIT_Y;
	return kDir;
}

static int32_t MaterialTypeToImpactData(uint32_t aeHavokMaterial) {
	return CdeclCall<int32_t>(0x58E8F0, aeHavokMaterial);
}

static IMPACT_MATERIAL_TYPE __fastcall GetActorBodyMaterial(Actor* apActor) {
	TESActorBase* pBase = apActor->GetActorBase();
	if (!pBase)
		return IMPACT_MATERIAL_TYPE::NONE;

	return pBase->GetBloodImpactMaterial();
}

static void PlayImpactSound(TESSound* apSound, const NiPoint3& arPos, NiAVObject* apNode) {
	if (!apSound || !apSound->uiFormID)
		return;
	
	BSSoundHandle kHandle = BSAudio::GetSingleton()->GetSoundHandleByFormID(apSound->uiFormID, BSGameSound::TypeFlags::IS_3D | BSGameSound::TypeFlags::ONE_SHOT);
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

	const char* pModelPath = apImpact->GetModel();
	if (!pModelPath || !pModelPath[0])
		return;

	CdeclCall(kAddrCreateTempEffectParticle, apCell, apImpact->GetEffectDuration(), pModelPath, arDir, arPos, 1.f, 7, nullptr);
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
	float			fWidth = 0.f;
	float			fHeight = 0.f;
	float			fDepth = 0.f;
	float			fRNG = 1.f;
	TESObjectCELL*	pParentCell = nullptr;
	float			fParallaxScale = 0.f;
	NiAVObject*		pSkinnedDecal = nullptr;
	float			fSpecular = 0.f;
	float			fEpsilon = 0.f;
	float			fPlacementRadius = 0.f;
	float			fColorR = 0.f;
	float			fColorG = 0.f;
	float			fColorB = 0.f;
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

static void AddActorBloodDecal(Actor* apTarget, NiAVObject* apNode, BGSImpactData* apImpact, int32_t aiLocation, const NiPoint3& arPos, const NiPoint3& arDir) {
	if (!apNode || !apImpact->GetDecalTextureSet() || !apTarget->GetParentCell())
		return;

	GeometryDecalCreateData kData;
	kData.kWorldPos = arPos;
	kData.kRotation = arDir;
	kData.kPoint18 = arDir;
	kData.pActor = apTarget;
	kData.pNode = apNode;
	kData.pTextureSet = apImpact->GetDecalTextureSet();
	kData.fWidth = apImpact->GetDecalMaxWidth();
	kData.fHeight = apImpact->GetDecalMaxHeight();
	kData.fDepth = apImpact->GetDecalDepth() > 0.f ? apImpact->GetDecalDepth() : 48.f;
	kData.fParallaxScale = apImpact->GetDecalParallaxScale();
	kData.fSpecular = apImpact->GetDecalShininess();
	kData.fEpsilon = apImpact->GetDecalAngleThreshold();
	kData.fPlacementRadius = apImpact->GetPlacementRadius();
	kData.fColorR = static_cast<float>(apImpact->GetDecalColor() & 0xFF) / 255.f;
	kData.fColorG = static_cast<float>((apImpact->GetDecalColor() >> 8) & 0xFF) / 255.f;
	kData.fColorB = static_cast<float>((apImpact->GetDecalColor() >> 16) & 0xFF) / 255.f;
	kData.uiHitLocationFlags = 1u << aiLocation;
	kData.ucParallax = apImpact->GetIsParallax();
	kData.ucAlphaBlend = apImpact->GetAlphaBlending();
	kData.ucAlphaTest = apImpact->GetAlphaTesting();
	kData.ucParallaxPasses = apImpact->GetDecalParallaxPasses();
	kData.ucModelSpace = 1;

	ThisCall(0x4A3FE0, apTarget->GetParentCell(), &kData, 2, false);
}

static void SpawnActorHitFX(Actor* apTarget, Actor* apAttacker, TESObjectWEAP* apWeapon, BODY_PART_TYPE aeBodyPart, IMPACT_MATERIAL_TYPE aeMaterial, bool abBlood, bool abSound) {
	if ((!abBlood && !abSound) || !apWeapon || !apWeapon->GetImpactDataSet() || !apTarget->GetParentCell())
		return;

	if (aeMaterial < 0 || aeMaterial >= ImpactSwap::FootstepMaterialType::COUNT)
		return;

	BGSImpactData* pImpact = apWeapon->GetImpactDataSet()->GetImpactData(aeMaterial);
	if (!pImpact)
		return;

	NiAVObject* pNode = nullptr;
	const NiPoint3 kPos = GetActorHitWorldPos(apTarget, aeBodyPart, &pNode);
	const NiPoint3 kDir = HitFXDirection(apAttacker, kPos);

	if (abBlood && apTarget->HasBlood()) {
		PlayImpactParticle(apTarget->GetParentCell(), pImpact, kPos, kDir);
		AddActorBloodDecal(apTarget, pNode, pImpact, aeBodyPart, kPos, kDir);
	}
	if (abSound) {
		PlayImpactSound(pImpact->GetSoundA(), kPos, pNode);
		PlayImpactSound(pImpact->GetSoundB(), kPos, pNode);
	}
}

static TESObjectWEAP* ResolveHitWeapon(TESForm* apForm) {
	if (apForm)
		return static_cast<TESObjectWEAP*>(apForm);

	return const_cast<TESObjectWEAP*>(pDefaultUnarmedWeapon.Get());
}

}

bool Cmd_ApplyHitData_Execute(COMMAND_ARGS) {
	*result = 0;

	if (!thisObj)
		return true;

	Actor* pTarget = static_cast<Actor*>(thisObj);
	if (!pTarget->IsActor() || !pTarget->GetCurrentAIProcess())
		return true;

	TESActorBase* pTargetBase = pTarget->GetActorBase();
	if (!pTargetBase)
		return true;

	Actor* pAttacker = nullptr;
	float fHealth = 10.f, fFatigue = 0.f, fLimb = 0.f;
	TESForm* pWeaponForm = nullptr;
	BODY_PART_TYPE eHitLocation = BODY_PART_TYPE::NONE;
	uint32_t uiFlags = 0, bFireOnHit = 1, bFireAlarm = 1, bFireBlood = 1, bFireSound = 1, bSkipClear = 0;

	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &pAttacker, &fHealth, &fFatigue, &fLimb, &pWeaponForm,
			&eHitLocation, &uiFlags, &bFireOnHit, &bFireAlarm, &bFireBlood, &bFireSound, &bSkipClear))
		return true;

	if (!IsFinite3(fHealth, fFatigue, fLimb) || fHealth < 0.f || fFatigue < 0.f || fLimb < 0.f)
		return true;

	if (eHitLocation < BODY_PART_TYPE::NONE || eHitLocation > BODY_PART_TYPE::BRAIN)
		eHitLocation = BODY_PART_TYPE::NONE;

	if (pAttacker && (!pAttacker->IsActor() || !pAttacker->GetCurrentAIProcess()))
		return true;

	if (pWeaponForm && !pWeaponForm->IsWeapon())
		return true;

	TESObjectWEAP* pWeapon = ResolveHitWeapon(pWeaponForm);

	HitData* pHitData = new HitData();
	pHitData->pSource = pAttacker;
	pHitData->pTarget = pTarget;
	pHitData->eWeaponSkill = pWeapon ? pWeapon->GetWeaponSkill() : ActorValue::Index::UNARMED;
	pHitData->eDamageLimb = eHitLocation;
	pHitData->fHealthDamage = fHealth;
	pHitData->fBaseWeaponDamage = fHealth;
	pHitData->fFatigueDamage = fFatigue;
	pHitData->fLimbDamage = fLimb;
	pHitData->pWeapon = pWeapon;
	pHitData->fHealthPercent = pWeapon ? 1.f : 0.f;
	pHitData->kImpactPos = GetActorHitWorldPos(pTarget, eHitLocation, nullptr);
	pHitData->kImpactAngle = pAttacker ? HitFXDirection(pTarget, pAttacker->GetPosition()) : NiPoint3::UNIT_Z;
	pHitData->uiFlags = uiFlags;
	pHitData->fDamageMult = 1.f;

	NiPointer<HitData> spHitData(pHitData);

	BaseProcess* pProc = pTarget->GetCurrentAIProcess();
	bool bCopiedHitData = false;
	pProc->SetLastHitData(spHitData);
	if (pAttacker)
		pProc->SetLastAttackHitData(spHitData);
	bCopiedHitData = true;

	BGSBodyPartData* pBodyPartData = pTargetBase->GetBodyPartData();

	if (fHealth > 0.f) {
		pTarget->DoDamage(fHealth, 0.f, pAttacker);
	}

	if (fLimb > 0.f && eHitLocation >= 0) {
		BGSBodyPart* pBodyPart = pBodyPartData->GetBodyPart(eHitLocation);
		if (pBodyPart)
			pTarget->DamageModActorValueF(static_cast<ActorValue::Index>(pBodyPart->GetActorValue()), -fLimb, pAttacker);

	}
	if (bFireOnHit) {
		ExtraDataList* pExtra = pTarget->GetExtra();
		if (pAttacker)
			Script::SetActionFlag(pAttacker, pExtra, 0x80);
		if (pWeapon)
			Script::SetActionFlag(pWeapon, pExtra, 0x100);
	}

	if (bFireAlarm && pAttacker == PlayerCharacter::GetSingleton())
		pTarget->AttackAlarm(pAttacker, false);

	if (fFatigue > 0.f)
		pTarget->DamageModActorValueF(ActorValue::Index::FATIGUE, -fFatigue, pAttacker);

	if (pWeaponForm && pWeapon && pWeapon->GetImpactDataSet() && (bFireBlood || bFireSound)) {
		BODY_PART_TYPE eBloodLoc = (eHitLocation >= 0) ? eHitLocation : BODY_PART_TYPE::TORSO;
		IMPACT_MATERIAL_TYPE eMaterial = GetActorBodyMaterial(pTarget);
		if (eMaterial >= 0) {
			SpawnActorHitFX(pTarget, pAttacker, pWeapon, eBloodLoc, eMaterial, bFireBlood != 0, bFireSound != 0);
		}
	}

	if (!bSkipClear) {
		pProc->ClearLastHitData();
		pProc->ClearLastAttackHitData();
		bCopiedHitData = false;
	}

	*result = 1;
	return true;
}

namespace {

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

	void CalcHitPoint(NiPoint3& arHitPoint) const {
		ThisCall(0x5DBE60, this, &arHitPoint);
	}
};
static_assert(sizeof(PickRayData) == 0xB0);
static_assert(offsetof(PickRayData, fHitFraction) == 0x40);
static_assert(offsetof(PickRayData, uiShapeKeys) == 0x50);
static_assert(offsetof(PickRayData, pRootCollidable) == 0x80);
static_assert(sizeof(hkCdBody) == 0x10);
static_assert(offsetof(hkpWorldObject, cdBody) == 0x10);
static_assert(offsetof(hkpWorldObject, collisionType) == 0x28);
static_assert(offsetof(hkpShape, shape) == 0x08);
static_assert(sizeof(bhkRefObject) == 0x0C);
static_assert(offsetof(bhkRefObject, refObject) == 0x08);
static_assert(sizeof(bhkNiCollisionObject) == 0x14);
static_assert(offsetof(bhkNiCollisionObject, worldObj) == 0x10);

struct CollisionFilter {
	uint32_t uiFilter = 0;
};
static_assert(sizeof(CollisionFilter) == 4);

static int32_t CollidableRootMaterial(const void* apCollidable, const NiPoint3& arPos) {
	return MaterialTypeToImpactData(CdeclCall<uint32_t>(kAddrGetMaterialFromCollidable, apCollidable, &arPos));
}

static int32_t BhkShapeSubMaterial(bhkShape* apBhkShape, uint32_t auiShapeKey) {
	return MaterialTypeToImpactData(apBhkShape->GetSubshapeMaterial(auiShapeKey));
}

static void* HkpShapeContainer(void* apShape) {
	if (!apShape)
		return nullptr;
	void** pVtbl = *reinterpret_cast<void***>(apShape);
	return ThisCall<void*>(reinterpret_cast<uintptr_t>(pVtbl[kShapeGetContainerVtableSlot]), apShape);
}

static void* HkpContainerChild(void* apContainer, uint32_t auiKey, void* apBuffer) {
	if (!apContainer)
		return nullptr;
	void** pVtbl = *reinterpret_cast<void***>(apContainer);
	return ThisCall<void*>(reinterpret_cast<uintptr_t>(pVtbl[kShapeGetChildVtableSlot]), apContainer, auiKey, apBuffer);
}

static int32_t ChildShapeMaterial(void* apContainer, uint32_t auiKey, void* apBuffer) {
	hkpShape* pChildShape = static_cast<hkpShape*>(HkpContainerChild(apContainer, auiKey, apBuffer));
	bhkShape* pChildBhk = bhkShape::Getbhk(pChildShape);
	return pChildBhk ? MaterialTypeToImpactData(pChildBhk->GetMaterial()) : -1;
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

static void ProbeShapeKey(void* apContainer, bhkShape* apBhkShape, uint32_t auiKey, void* apChildBuffer, MaterialCandidates& arCandidates) {
	if (auiKey == 0xFFFFFFFF)
		return;

	if (apContainer) {
		NoteMaterialCandidate(ChildShapeMaterial(apContainer, auiKey, apChildBuffer), arCandidates.iChildBest, arCandidates.iChildFallback);
		if (arCandidates.iChildBest > 0)
			return;
	}

	NoteMaterialCandidate(BhkShapeSubMaterial(apBhkShape, auiKey), arCandidates.iSubBest, arCandidates.iSubFallback);
}

static uint32_t PlayerCollisionGroup() {
	PlayerCharacter* pPlayer = PlayerCharacter::GetSingleton();
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
	kPick.fFrom[0] = afCamX * fNI2HK;
	kPick.fFrom[1] = afCamY * fNI2HK;
	kPick.fFrom[2] = afCamZ * fNI2HK;
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
	kPick.fTo[0] = fEndX * fNI2HK;
	kPick.fTo[1] = fEndY * fNI2HK;
	kPick.fTo[2] = fEndZ * fNI2HK;
	if (!IsFinite3(kPick.fFrom[0], kPick.fFrom[1], kPick.fFrom[2]) ||
			!IsFinite3(kPick.fTo[0], kPick.fTo[1], kPick.fTo[2]))
		return -1;
	kPick.fHitFraction = 1.f;
	kPick.uiExtraInfo = 0xFFFFFFFF;
	kPick.uiShapeKeys[0] = 0xFFFFFFFF;

	kPick.uiFilterInfo = static_cast<uint32_t>(aiLayer) | PlayerCollisionGroup();

	TES* pTES = TES::GetSingleton();
	if (!pTES)
		return -1;

	if (!ThisCall<NiAVObject*>(kAddrPick, pTES, &kPick, 1))
		return -1;

	void* pRoot = kPick.pRootCollidable;
	if (!pRoot)
		return -1;

	float fFrac = kPick.fHitFraction;
	if (fFrac < 0.f || fFrac > 1.f)
		fFrac = 1.f;

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
	kPick.CalcHitPoint(kHitPos);
	if (!IsFinite3(kHitPos.x, kHitPos.y, kHitPos.z))
		return -1;

	const int32_t iHitMat = CollidableRootMaterial(pRoot, kHitPos);

	hkpShape* pRootShape = *reinterpret_cast<hkpShape**>(pRoot);
	bhkShape* pBhkShape = bhkShape::Getbhk(pRootShape);
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
		const int32_t iScriptMat = CollidableRootMaterial(pRoot, kScriptHitPos);
		if (iScriptMat >= 0)
			iChosen = iScriptMat;
	}
	return iChosen;
}

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

	return MaterialTypeToImpactData(pShape->shape->GetMaterial());
}

static void __cdecl FirstMaterialCallback(bhkNiCollisionObject* apCollisionObject, bhkWorld::ObjectRecData& arData) {
	const int32_t iMat = CollisionObjectMaterial(apCollisionObject);
	if (iMat >= 0) {
		arData.uData[0].i = iMat;
		arData.bRecurse = false;
	}
}

static IMPACT_MATERIAL_TYPE GetObjectImpactMaterial(TESObjectREFR* apRef) {
	if (apRef->IsActor())
		return GetActorBodyMaterial(static_cast<Actor*>(apRef));

	NiAVObject* pRoot = apRef->Get3D();
	if (!pRoot)
		return IMPACT_MATERIAL_TYPE::NONE;
	bhkWorld::ObjectRecData kData;
	kData.bRecurse = true;
	kData.eAction = 0;
	kData.uData[0].i = -1;
	bhkWorld::DoObjectRec(pRoot, kData, FirstMaterialCallback);
	if (kData.uData[0].i < 0)
		kData.uData[0].i = CollisionObjectMaterial(pRoot->m_spCollisionObject);
	return static_cast<IMPACT_MATERIAL_TYPE>(kData.uData[0].i);
}

}

bool Cmd_GetObjectMaterial_Execute(COMMAND_ARGS) {
	*result = -1;

	if (!thisObj)
		return true;

	float fCamX = 3.0e38f, fCamY = 0.f, fCamZ = 0.f, fHitX = 0.f, fHitY = 0.f, fHitZ = 0.f;
	int32_t iLayer = 6;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &fCamX, &fCamY, &fCamZ, &fHitX, &fHitY, &fHitZ, &iLayer))
		return true;

	if (!std::isfinite(fCamX))
		return true;

	if (fCamX < 1.0e38f) {
		if (!IsFinite3(fCamX, fCamY, fCamZ) || !IsFinite3(fHitX, fHitY, fHitZ) || iLayer < 0 || iLayer > 0x7F)
			return true;
		*result = RaycastSubshapeMaterial(fCamX, fCamY, fCamZ, fHitX, fHitY, fHitZ, iLayer);
	} else {
		*result = GetObjectImpactMaterial(thisObj);
	}
	return true;
}

bool Cmd_ApplyObjectImpact_Execute(COMMAND_ARGS) {
	*result = -1;

	if (!thisObj)
		return true;

	IMPACT_MATERIAL_TYPE iMaterial = IMPACT_MATERIAL_TYPE::NONE;
	TESForm* pWeaponForm = nullptr;
	uint32_t bSound = 1, bParticle = 1;
	float fPosX = 3.0e38f, fPosY = 3.0e38f, fPosZ = 3.0e38f;

	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &iMaterial, &pWeaponForm, &bSound, &bParticle, &fPosX, &fPosY, &fPosZ))
		return true;

	if (pWeaponForm && !pWeaponForm->IsWeapon())
		return true;

	if (!IsFinite3(fPosX, fPosY, fPosZ))
		return true;

	TESObjectWEAP* pWeapon = ResolveHitWeapon(pWeaponForm);
	if (!pWeapon || !pWeapon->GetImpactDataSet())
		return true;

	if (iMaterial < 0)
		iMaterial = GetObjectImpactMaterial(thisObj);

	if (iMaterial < 0 || iMaterial >= IMPACT_MATERIAL_TYPE::COUNT)
		return true;

	BGSImpactData* pImpact = pWeapon->GetImpactDataSet()->GetImpactData(iMaterial);
	if (!pImpact)
		return true;

	NiPoint3 kPos = (fPosX > 1.0e38f || fPosY > 1.0e38f || fPosZ > 1.0e38f)
		? thisObj->GetPosition()
		: NiPoint3(fPosX, fPosY, fPosZ);
	const NiPoint3 kDir = HitFXDirection(
		reinterpret_cast<Actor*>(PlayerCharacter::GetSingleton()), kPos);

	if (bParticle)
		PlayImpactParticle(thisObj->GetParentCell(), pImpact, kPos, kDir);
	if (bSound) {
		PlayImpactSound(pImpact->GetSoundA(), kPos, nullptr);
		PlayImpactSound(pImpact->GetSoundB(), kPos, nullptr);
	}
	*result = iMaterial;
	return true;
}

bool Cmd_InterruptWeaponAnim_Execute(COMMAND_ARGS) {
	*result = -2;
	if (!thisObj)
		return true;

	Actor* pActor = static_cast<Actor*>(thisObj);
	if (!pActor->IsActor() || !pActor->GetCurrentAIProcess())
		return true;

	HighProcess* pProc = static_cast<HighProcess*>(pActor->GetCurrentAIProcess());

	if (pProc->GetProcessLevel() != PROCESS_LEVEL::HIGH)
		return true;

	Animation* pAnimation = pProc->GetAnimation();
	if (!pAnimation)
		return true;

	const ANIMATION_ACTION sOldAction = pProc->GetAnimAction();
	// Never clear an attack sequence. The queued melee task does not null-check it.
	if (pActor->IsAttacking()) {
		*result = -3;
		return true;
	}

	pAnimation->ClearGroup(ANIM_GROUP_SECTION::WEAPON, 0.f);
	pActor->SetAnimAction(ANIMATION_ACTION::NONE, nullptr);
	*result = sOldAction;
	return true;
}

namespace {

static_assert(sizeof(hkpWorldObject) == 0x8C);
static_assert(sizeof(hkpMotion) == 0x140);
static_assert(offsetof(hkpMotion, linVelocity) == 0xD0);
static_assert(sizeof(hkpRigidBody) == 0x220);
static_assert(offsetof(hkpRigidBody, motion) == 0xE0);
static_assert(sizeof(bhkWorldObject) == 0x14);
static_assert(offsetof(bhkWorldObject, refObject) == 0x08);
static_assert(sizeof(bhkRigidBody) == 0x1C);

static float* __fastcall GetRigidBodyCenterOfMass(bhkWorldObject* apWorldObject, float* apOut) {
	void** pVtbl = *reinterpret_cast<void***>(apWorldObject);
	return ThisCall<float*>(reinterpret_cast<uintptr_t>(pVtbl[kRigidBodyCenterVtableSlot]), apWorldObject, apOut);
}

static void __fastcall PushNodeBodies(NiAVObject* apObject, uint32_t auiDepth, const NiPoint3& arOrigin, float afForce, uint32_t& arCount) {
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
			double fDX = static_cast<double>(pPos[0]) * fHK2NI - arOrigin.x;
			double fDY = static_cast<double>(pPos[1]) * fHK2NI - arOrigin.y;
			double fDZ = static_cast<double>(pPos[2]) * fHK2NI - arOrigin.z;
			if (fDZ > 0.0)
				fDZ = 0.0;
			const double fLen = std::sqrt(fDX * fDX + fDY * fDY + fDZ * fDZ);
			if (std::isfinite(fLen) && fLen > 0.0001) {
				const double fScale = static_cast<double>(afForce) * fNI2HK / fLen;
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
			PushNodeBodies(pChild, auiDepth + 1, arOrigin, afForce, arCount);
}

}

bool Cmd_ApplyRagdollForce_Execute(COMMAND_ARGS) {
	*result = 0;
	float fForce = 0.f;
	NiPoint3 kOrigin;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &fForce, &kOrigin.x, &kOrigin.y, &kOrigin.z))
		return true;

	if (!thisObj)
		return true;

	if (!std::isfinite(fForce) || !IsFinite3(kOrigin.x, kOrigin.y, kOrigin.z) || fForce == 0.f)
		return true;

	Actor* pActor = static_cast<Actor*>(thisObj);
	if (!pActor->IsActor() || !pActor->GetCurrentAIProcess())
		return true;

	// Get3DSimple, not Get3D. The player override returns the 1st person arms in 1st person.
	NiAVObject* pRoot = pActor->Get3DSimple();
	if (!pRoot)
		return true;

	uint32_t uiCount = 0;
	PushNodeBodies(pRoot, 0, kOrigin, fForce, uiCount);
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
	int32_t iMode = 0;
	int32_t kParts[16];
	for (int32_t i = 0; i < 16; ++i)
		kParts[i] = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &iMode,
		&kParts[0], &kParts[1], &kParts[2], &kParts[3],
		&kParts[4], &kParts[5], &kParts[6], &kParts[7],
		&kParts[8], &kParts[9], &kParts[10], &kParts[11],
		&kParts[12], &kParts[13], &kParts[14], &kParts[15])) {

		const uint32_t uiBits = (iMode >= 1 && iMode <= 2) ? PlayerBodyOverlay::BuildPartBits(kParts, ARRAYSIZE(kParts)) : 0;
		PlayerBodyOverlay::SetCullParts(iMode, uiBits);
	}
	*result = PlayerBodyOverlay::GetCullPartBits();
	return true;
}
