#include "ScriptUtils.hpp"
#include "GameObjects.h"
#include "netimmerse.h"

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

}