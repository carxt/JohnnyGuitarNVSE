#include "ScriptUtils.hpp"
#include "PluginAPI.h"
#include "CommandTable.h"
#include "CommandOpcodes.h"

#include "Bethesda/Animation.hpp"
#include "Bethesda/BGSLoadGameSubBuffer.hpp"
#include "Bethesda/BGSSaveFormBuffer.hpp"
#include "Bethesda/BGSSaveLoadGame.hpp"
#include "Bethesda/PlayerCharacter.hpp"
#include "Bethesda/ProcessLists.hpp"
#include "Bethesda/Interface.hpp"
#include "Bethesda/TES.hpp"
#include "Gamebryo/NiControllerManager.hpp"

#include "shared/Utils/StackObject.hpp"

extern NVSECommandTableInterface* g_cmdTableInterface;

namespace ScriptUtils {

	static Cmd_Execute Cmd_Update3D = nullptr;

	AutoSaveFormChanges::AutoSaveFormChanges(bool abAllow) noexcept {
		bOrgVal = BGSSaveLoadGame::GetSingleton()->SetThreadAllowChanges(abAllow);
	}

	AutoSaveFormChanges::~AutoSaveFormChanges() noexcept {
		std::ignore = BGSSaveLoadGame::GetSingleton()->SetThreadAllowChanges(bOrgVal);
	}

	NiAVObject* __fastcall GetReferenceScene(TESObjectREFR* apRef, bool abFirstPerson) {
		if (apRef == PlayerCharacter::GetSingleton())
			return static_cast<PlayerCharacter*>(apRef)->Get3D(abFirstPerson);
		else
			return apRef->Get3D();
	}

	void RecurseAndAddObjectsToPalette(NiAVObject* apObject, NiDefaultAVObjectPalette* apPalette) {
		CdeclCall(0xA6E870, apObject, apPalette);
	}

	void RecurseAndRemoveObjectsFromPalette(NiAVObject* apObject, NiDefaultAVObjectPalette* apPalette) {
		CdeclCall(0xA6E8E0, apObject, apPalette);
	}

	NiDefaultAVObjectPalette* __fastcall GetObjectPalette(const NiAVObject* apRoot) {
		if (!apRoot) [[unlikely]]
			return nullptr;

		NiControllerManager* pControllerManager = apRoot->GetController<NiControllerManager>();
		return pControllerManager ? pControllerManager->m_spObjectPalette.m_pObject : nullptr;
	}

	SPEC_NOINLINE void __fastcall RecurseAddObjectsToPalette(NiAVObject* apRoot, NiAVObject* apObject) {
		RecurseAndAddObjectsToPalette(apObject, GetObjectPalette(apRoot));
	}

	SPEC_NOINLINE void __fastcall RecurseRemoveObjectsFromPalette(NiAVObject* apRoot, NiAVObject* apObject) {
		RecurseAndRemoveObjectsFromPalette(apObject, GetObjectPalette(apRoot));
	}

	SPEC_NOINLINE void __fastcall AddObjectToPalette(NiAVObject* apRoot, NiAVObject* apObject) {
		if (!apObject || !apObject->GetName()) [[unlikely]]
			return;

		NiDefaultAVObjectPalette* pPalette = GetObjectPalette(apRoot);
		if (pPalette)
			pPalette->SetAVObject(apObject->GetName(), apObject);
	}

	SPEC_NOINLINE void __fastcall RemoveObjectFromPalette(NiAVObject* apRoot, NiAVObject* apObject) {
		if (!apObject || !apObject->GetName()) [[unlikely]]
			return;

		NiDefaultAVObjectPalette* pPalette = GetObjectPalette(apRoot);
		if (pPalette)
			pPalette->SetAVObject(apObject->GetName(), nullptr);
	}

	SPEC_NOINLINE void __fastcall SaveAnimation(BGSLoadGameSubBuffer& arBuffer, TESObjectREFR* apReference, Animation* apAnimation) {
		StackObject<BGSSaveFormBuffer, 0x8659C0, 0x847DD0> kSaveBuffer;
		kSaveBuffer->SetHeader(apReference->GetFormID(), 0, apReference->GetFormType(), 27);
		kSaveBuffer->SetForm(apReference);
		if (apReference->IsActor()) {
			if (apAnimation)
				apAnimation->Save(kSaveBuffer.GetPtr());
		}
		else
			apReference->SaveAnimation(kSaveBuffer.GetPtr());
		arBuffer.CopyBuffer(kSaveBuffer.GetPtr());
	}

	SPEC_NOINLINE void __fastcall LoadAnimation(BGSLoadGameSubBuffer& arBuffer, TESObjectREFR* apReference, Animation* apAnimation) {
		BGSLoadFormBuffer* pLoadBuffer = arBuffer.CreateLoadFormBuffer(apReference);
		if (pLoadBuffer) {
			if (apReference->IsActor()) {
				if (apAnimation)
					apAnimation->Load(pLoadBuffer);
			}
			else
				apReference->LoadAnimation(pLoadBuffer);
			ThisCall(0x81DB60, pLoadBuffer, true); // BGSLoadFormBuffer destructor
		}
	}

	// Based on MoveTo + CE's SetPos (which is just tweaked MoveTo)
	// Aka cooler MoveTo
	SPEC_NOINLINE void __fastcall MoveRefTo(TESObjectREFR* apRef, const NiPoint3& arPos, const NiPoint3& arRot, TESObjectREFR* apTarget, TESObjectCELL* apCell, TESWorldSpace* apWorld) {
		Actor* pActor = apRef->IsActor() ? static_cast<Actor*>(apRef) : nullptr;
		const bool bPlayer = pActor == PlayerCharacter::GetSingleton();

		const TESWorldSpace* pCurrentWorld = apRef->GetWorldSpace();
		const TESObjectCELL* pCurrentCell = apRef->GetParentCell();

		const TESObjectREFR* pLocationRef = apTarget ? apTarget : apRef;

		TESWorldSpace* pTargetWorld = apWorld ? apWorld : pLocationRef->GetWorldSpace();
		TESObjectCELL* pParentCell = apCell ? apCell : pLocationRef->GetParentCell();

		TESObjectCELL* pTargetCell = nullptr;
		if (pTargetWorld)
			pTargetCell = TES::GetSingleton()->GetCellForPoint(arPos);
		else if (pParentCell && pParentCell->GetInterior())
			pTargetCell = pParentCell;

		const bool bNewWorld = pCurrentWorld && pTargetWorld && pCurrentWorld != pTargetWorld;
		const bool bNewCell = pCurrentCell && pTargetCell && pCurrentCell != pTargetCell;
		const bool bNewSpace = bNewWorld || bNewCell;

		if (pActor) {
			if (bNewSpace)
				ProcessLists::GetSingleton()->StopCombatAndAlarmOnActor(pActor, false);

			BaseProcess* pAIProc = pActor->GetCurrentAIProcess();
			if (pAIProc && pAIProc->GetSitSleepState() != SIT_SLEEP_STATE::NORMAL)
				pActor->GetOutofFurnitureQuick();
		}

		if (bPlayer && !pTargetCell) {
			PlayerCharacter::PositionRequest* pPosRequest = new PlayerCharacter::PositionRequest();

			if (pTargetWorld)
				pPosRequest->pWorld = pTargetWorld;
			else if (pTargetCell && pTargetCell->GetInterior())
				pPosRequest->pInterior = pTargetCell;

			pPosRequest->bResetWeather = true;
			pPosRequest->kPos = arPos;
			pPosRequest->kRot = arRot;
			pPosRequest->pFastTravelMarker = apTarget;
			PlayerCharacter::GetSingleton()->RequestPositionPlayer(pPosRequest);
			Interface::CloseConsole();
		}
		else if (pActor && !apRef->IsDead(false)) {
			pActor->MoveActorAndFollowers(arPos, arRot.z, pTargetCell, pTargetWorld, true, bNewSpace);
		}
		else {
			apRef->SetLocationOnReference(arPos);
			apRef->SetAngleOnReference(arRot);

			if (pTargetCell && TES::GetSingleton()->IsCellLoaded(pTargetCell, false))
				apRef->Update3DPosition();

			TESObjectREFR::MoveRefToNewSpace(apRef, pTargetCell, pTargetWorld);

			const TESObjectCELL* pCurrParentCell = apRef->GetParentCell();
			if (pCurrParentCell) [[likely]] {
				if (TES::GetSingleton()->IsCellLoaded(pCurrParentCell, false))
					apRef->InitHavok();
			}

			if (pActor) [[unlikely]] {
				pActor->FadeIn();
				pActor->UpdateAlpha();
			}
		}

		PlayerCharacter::GetSingleton()->CheckForQuestTargetUpdate(apRef);
	}

	void __fastcall UpdateReference3D(TESObjectREFR* apReference) {
		double dResult;
		uint32_t uiOffset = 0;
		Cmd_Update3D(nullptr, nullptr, apReference, nullptr, nullptr, nullptr, &dResult, &uiOffset);
	}

	TESObject* __fastcall GetTESObject(const TESForm* apForm) {
		if (!apForm)
			return nullptr;

		if (apForm->IsReference()) {
			const TESObjectREFR* refr = static_cast<const TESObjectREFR*>(apForm);
			TESBoundObject* pObject = refr->GetObjectReference();
			if (pObject)
				return pObject;
		}

		if (apForm->IsObject())
			return static_cast<TESObject*>(const_cast<TESForm*>(apForm));

		return nullptr;
	}

}

namespace ScriptUtils {

	void InitData() {
		const CommandInfo* pUpdate3D = g_cmdTableInterface->GetByOpcode(CommandOpcodes::kUpdate3D);
		if (pUpdate3D)
			Cmd_Update3D = pUpdate3D->execute;
	}

}