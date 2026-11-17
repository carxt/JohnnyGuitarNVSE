#include "RefPositionUpdateFix.hpp"

#include "Bethesda/Actor.hpp"
#include "Bethesda/AILinearTaskThreadManager.hpp"
#include "Bethesda/BGSPlaceableWater.hpp"
#include "Bethesda/BSFadeNode.hpp"
#include "Bethesda/BSMultiBoundNode.hpp"
#include "Bethesda/BSShaderManager.hpp"
#include "Bethesda/TES.hpp"
#include "Bethesda/TESBoundObject.hpp"
#include "Bethesda/TESObjectCELL.hpp"
#include "Bethesda/TESWaterSystem.hpp"
#include "Bethesda/WaterZone.hpp"

#include <netimmerse.h>
#include <havok.h>

#include "JG/TaskQueue.hpp"
#include "JG/JohnnyExtraData.hpp"
#include "Shared/SafeWrite/SafeWrite.hpp"

namespace RefPositionUpdateFix {

	// Game doesn't update sound and water data when moving references
	// Fixed in CE, which this is loosely based on (our water code is shittier and more convoluted, yay)

	static BSMultiBoundNode* __fastcall GetWaterMultibound(NiAVObject* apObject) {
		if (apObject->IsNode()) [[likely]] {
			const NiNode* pNode = static_cast<NiNode*>(apObject);
			const NiAVObject* pChild = pNode->GetAtChecked(0);
			if (pChild) [[likely]]
				return pChild->IsMultiBoundNode();
		}
		return nullptr;
	}

	static void __fastcall UpdateWaterMultibound(NiAVObject* apObject, float afHeight) {
		BSMultiBoundNode* pNode = GetWaterMultibound(apObject);
		if (pNode->spMultiBound && pNode->spMultiBound->spShape) [[likely]] {
			BSMultiBoundShape* pShape = pNode->spMultiBound->spShape;
			NiBound kBound;
			pShape->GetNiBound(kBound);
			kBound.m_kCenter.z = afHeight;
			pShape->SetCenter(kBound.m_kCenter);
			apObject->UpdateWorldBound();
		}
	}

	static void __fastcall UpdateWaterZone(TESObjectREFR* apWaterRef, float afHeight) {
		WaterZone* pZone = CdeclCall<WaterZone*>(0x62FE80, apWaterRef); // TESWaterListener::FindWater
		if (pZone) [[likely]]
			pZone->fWaterHeight = afHeight;
	}

	static void __fastcall UpdateDepthReferences(PlaceableWaterGroup* apGroup, TESObjectREFR* apRef) {
		ExtraDataList* pExtra = apRef->GetExtra();
		if (!pExtra->GetReflectedRefs())
			return;

		const TESObjectCELL* pCell = apRef->GetParentCell();
		if (!pCell) [[unlikely]]
			return;

		const BSMultiBoundNode* pMultiBound = GetWaterMultibound(apRef->Get3DVerySimple());
		if (!pMultiBound) [[unlikely]]
			return;

		apGroup->kStaticDepthObjects.RemoveAll();
		apGroup->kStaticReflectiveObjects.RemoveAll();

		auto pIter = pCell->GetRefList();
		while (pIter && !pIter->IsEmpty()) {
			TESObjectREFR* pRef = pIter->GetItem();
			pIter = pIter->GetNext();

			if (pRef == apRef) [[unlikely]]
				continue;

			if (pRef && !pRef->GetDisabledOrDeleted() && !pRef->IsMobileObject()) [[likely]] {
				const NiAVObject* p3D = pRef->Get3DVerySimple();
				if (p3D && p3D->IsVisualObject()) [[likely]] {
					const bool bAdd = pMultiBound->CheckNiBound(*p3D->m_pWorldBound);
					pExtra->SetRefractsRef(pRef, bAdd);
				}
			}
		}
	}

	static void __fastcall UpdateSubmergedRefs(PlaceableWaterGroup* apGroup, float afHeight) {
		auto pFunc = [&](TESObjectREFR* apRef, int32_t) {
			if (apRef && apRef->pLoadedData) [[likely]] {
				apRef->pLoadedData->fRelevantWaterHeight = afHeight;
				if (apRef->IsMobileObject()) {
					bhkCharacterController* pCtrl = static_cast<MobileObject*>(apRef)->GetCharController();
					if (pCtrl) [[likely]]
						pCtrl->SetWaterHeight(afHeight);
				}
			}
		};

		apGroup->kActorsInWater.ForEach(pFunc);
		apGroup->kObjecstInWater.ForEach(pFunc);
	}

	static void __fastcall UpdateWaterGroup(TESObjectREFR* apWaterRef, NiAVObject* apObject) {
		const TES* pTES = TES::GetSingleton();
		TESWaterSystem* pWS = pTES->GetWaterSystem();
		if (!pWS) [[unlikely]]
			return;

		PlaceableWaterGroup* pWaterGroup = nullptr;
		NiTListIterator kRefListPos = nullptr;
		{
			NiTListIterator kIter = pWS->kPlaceableWaterGroups.GetHeadPos();
			while (kIter) {
				PlaceableWaterGroup* pGroup = pWS->kPlaceableWaterGroups.GetNext(kIter);
				if (!pGroup) [[unlikely]]
					continue;

				kRefListPos = pGroup->kPlaceableWaters.FindPos(apWaterRef);
				if (kRefListPos) {
					pWaterGroup = pGroup;
					break;
				}
			}
		}

		if (!pWaterGroup)
			return;

		const bool bMultiple = pWaterGroup->kPlaceableWaters.GetSize() > 1;
		if (bMultiple) [[unlikely]] {
			pWaterGroup->kPlaceableWaters.RemovePos(kRefListPos);
			pWS->AddPlaceableWater(apWaterRef);
		}
		else [[likely]] {
			const NiPoint3 kPosition = apObject->GetWorldTranslate();
			const NiMatrix3 kRotation = apObject->GetWorldRotate();
			const float fHeight = kPosition.z;

			NiPoint3 kNormalDir = { 0.f, 0.f, 1.f };
			NiPoint3 kNormalInvDir = { 0.f, 0.f, -1.f };

			kNormalDir = kRotation * kNormalDir;
			kNormalDir.Unitize();

			kNormalInvDir = kRotation * kNormalInvDir;
			kNormalInvDir.Unitize();

			pWaterGroup->kReflectWaterPlane = { kNormalDir, kPosition };
			pWaterGroup->kRefractWaterPlane = { kNormalInvDir, kPosition };

			if (pWaterGroup->spWadingWaterGeometry)
				pWaterGroup->spWadingWaterGeometry->m_kLocal.m_kTranslate.z = fHeight;

			UpdateSubmergedRefs(pWaterGroup, fHeight);

			if (pWaterGroup->bRenderDepth)
				UpdateDepthReferences(pWaterGroup, apWaterRef);
		}
	}

	static SPEC_NOINLINE void __fastcall MoveWater(TESObjectREFR* apWaterRef, NiAVObject* ap3D) {
		const float fHeight = ap3D->GetWorldTranslate().z;

		UpdateWaterMultibound(ap3D, fHeight);

		TESObjectCELL* pCell = apWaterRef->GetParentCell();
		if (!pCell) [[unlikely]]
			return;

		pCell->CellRefLockEnter();

		if (pCell->fWaterHeight < fHeight) {
			pCell->SetWaterHeight(fHeight);
			if (!pCell->GetInterior())
				CdeclCall(0x62F460); // TESWaterListener::RefreshExteriorWaterHeights
		}

		UpdateWaterZone(apWaterRef, fHeight);

		UpdateWaterGroup(apWaterRef, ap3D);

		pCell->CellRefLockLeave();
	}

	static void __fastcall QueueMoveWater(TESObjectREFR* apWaterRef, NiAVObject* ap3D) {
		if (AILinearTaskThreadManager::ShouldQueue3DTask()) {
			JohnnyExtraData* pData = JohnnyExtraData::GetOrCreate(apWaterRef);
			if (!pData) [[unlikely]]
				return;

			pData->IncRefCount();

			QueuedTask kTask;
			kTask.kItems[0].p = pData;
			kTask.pFunction = QUEUED_TASK{
				JohnnyExtraData * pData = static_cast<JohnnyExtraData*>(arTask.kItems[0].p);
				if (pData && pData->pOwner) [[likely]] {
					TESObjectREFR* pWaterRef = static_cast<TESObjectREFR*>(pData->pOwner);
					NiAVObject* p3D = pWaterRef->Get3D();
					if (p3D) [[likely]]
						MoveWater(pWaterRef, p3D);
				}
				pData->DecRefCount();
			};

			TaskQueue::QueueTask(kTask);
		}
		else {
			MoveWater(apWaterRef, ap3D);
		}
	}

	static HookUtils::CallDetour kUpdateDetour;
	struct Hook {
		void UpdateRefPosition(NiUpdateData& arData) {
			NiAVObject* pThis = reinterpret_cast<NiAVObject*>(this);
			ThisCall(kUpdateDetour, pThis, &arData);
			if (!pThis->IsFadeNode())
				return;

			BSFadeNode* pFadeNode = reinterpret_cast<BSFadeNode*>(this);
			if (pFadeNode->GetReference()) {
				TESObjectREFR* pRef = pFadeNode->GetReference();

				const TESBoundObject* pBase = pRef->GetObjectReference();
				if (pBase && pBase->GetFormType() == FORM_TYPE::BGSPlaceableWater) {
					const BGSPlaceableWater* pWater = static_cast<const BGSPlaceableWater*>(pBase);
					if (!pWater->GetAutomaticWater()) // Not bothering. Just don't do that
						QueueMoveWater(pRef, pThis);
				}

				if (pRef->CanHaveSound()) {
					BSSoundHandle hSound;
					pRef->GetExtra()->GetSound(hSound);
					if (hSound.IsValid())
						hSound.SetPosition(pRef->GetPosition());
				}
			}
		}
	};

	void Install() {
		kUpdateDetour.ReplaceCall(0x5620C8, &Hook::UpdateRefPosition);
	}

}