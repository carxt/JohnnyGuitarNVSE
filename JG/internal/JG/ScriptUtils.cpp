#include "ScriptUtils.hpp"
#include "GameObjects.h"
#include "GameProcess.h"
#include "netimmerse.h"

#include "Bethesda/BGSSaveFormBuffer.hpp"
#include "Bethesda/BGSLoadGameSubBuffer.hpp"

#include "shared/Utils/StackObject.hpp"

namespace ScriptUtils {

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

}