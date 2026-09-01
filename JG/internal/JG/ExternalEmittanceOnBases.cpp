#include "ExternalEmittanceOnBases.hpp"
#include "JohnnyExtraData.hpp"

#include <GameObjects.h>

namespace ExternalEmittanceOnBases {

	HookUtils::CallDetour kGetBaseformDetour;
	TESBoundObject* __fastcall AddEmittanceSourceHook(TESObjectREFR* apReference) {
		TESBoundObject* pBase = ThisCall<TESBoundObject*>(kGetBaseformDetour, apReference);
		TESForm* pSource = GetExternalEmittanceSource(pBase);
		if (pSource)
			apReference->SetEmittanceSource(pSource);

		return pBase;
	}

	void Install() {
		kGetBaseformDetour.ReplaceCall(0x5694E0, AddEmittanceSourceHook);
	}

	TESForm* __fastcall GetExternalEmittanceSource(const TESBoundObject* apObject) {
		JohnnyExtraData* pData = JohnnyExtraData::Find(apObject);
		if (!pData)
			return nullptr;

		return pData->GetExternalEmittanceSource();
	}

	void __fastcall SetExternalEmittanceSource(TESBoundObject* apObject, TESForm* apSource) {
		JohnnyExtraData* pData = nullptr;
		if (apSource)
			pData = JohnnyExtraData::GetOrCreate(apObject);
		else
			pData = JohnnyExtraData::Find(apObject);

		if (!pData)
			return;

		pData->SetExternalEmittanceSource(apSource);
	}

}