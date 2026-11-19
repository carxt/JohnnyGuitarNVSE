#include "ExternalEmittanceOnBases.hpp"
#include "Bethesda/TESObjectREFR.hpp"

#include "JohnnyExtraData.hpp"

#include "Shared/SafeWrite/SafeWrite.hpp"

namespace ExternalEmittanceOnBases {

	class BaseExternalEmittanceData : public FormExtraData {
	public:
		JG_FED_NAME("JGBEE");
		JG_FED_FUNCS(BaseExternalEmittanceData);

		TESForm* pSource = nullptr;

		TESForm* __fastcall GetExternalEmittanceSource() const { return pSource; }
		void __fastcall SetExternalEmittanceSource(TESForm* apSource) { pSource = apSource; };
	};

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
		const BaseExternalEmittanceData* pData = BaseExternalEmittanceData::Get(apObject);
		if (!pData)
			return nullptr;

		return pData->GetExternalEmittanceSource();
	}

	void __fastcall SetExternalEmittanceSource(TESBoundObject* apObject, TESForm* apSource) {
		if (apSource) {
			BaseExternalEmittanceData* pData = BaseExternalEmittanceData::GetOrCreate(apObject);
			if (pData)
				pData->SetExternalEmittanceSource(apSource);
		}
		else {
			BaseExternalEmittanceData::Remove(apObject);
		}
	}

}