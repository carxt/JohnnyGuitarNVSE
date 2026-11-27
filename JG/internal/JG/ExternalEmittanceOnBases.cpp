#include "ExternalEmittanceOnBases.hpp"
#include "JohnnyExtraData.hpp"

#include "Bethesda/TESObjectREFR.hpp"

#include "Shared/SafeWrite/SafeWrite.hpp"

namespace ExternalEmittanceOnBases {

	namespace Hooks {

		static HookUtils::CallDetour kGetBaseformDetour;
		static TESBoundObject* __fastcall AddEmittanceSourceHook(TESObjectREFR* apReference) {
			TESBoundObject* pBase = ThisCall<TESBoundObject*>(kGetBaseformDetour, apReference);
			TESForm* pSource = GetExternalEmittanceSource(pBase);
			if (pSource)
				apReference->SetEmittanceSource(pSource);

			return pBase;
		}

		static void Init() {
			kGetBaseformDetour.ReplaceCall(0x5694E0, AddEmittanceSourceHook);
		}

	}

	void Install() {
		Hooks::Init();
	}

	TESForm* __fastcall GetExternalEmittanceSource(const TESBoundObject* apObject) {
		const JGExtraEmittanceSource* pData = JGExtraEmittanceSource::Get(apObject);
		if (!pData)
			return nullptr;

		return pData->GetExternalEmittanceSource();
	}

	void __fastcall SetExternalEmittanceSource(TESBoundObject* apObject, TESForm* apSource) {
		if (apSource) {
			JGExtraEmittanceSource* pData = JGExtraEmittanceSource::GetOrCreate(apObject);
			if (pData)
				pData->SetExternalEmittanceSource(apSource);
		}
		else {
			std::ignore = JGExtraEmittanceSource::Remove(apObject);
		}
	}

}