#include "AmmoEffectListNullChecks.hpp"
#include "Obsidian/TESAmmoEffect.hpp"

namespace AmmoEffectListNullChecks {

	template<uint32_t uiAddress>
	class NullCheckHook {
		static inline HookUtils::CallDetour kDetour;

		static BSSimpleList<TESAmmoEffect*>* __fastcall GetAmmoEffectsCheckType(TESForm* apForm) {
			if (IS_ID(apForm, TESAmmo))
				return ThisCall<BSSimpleList<TESAmmoEffect*>*>(kDetour, apForm);
			return nullptr;
		}

	public:
		NullCheckHook() {
			kDetour.ReplaceCall(uiAddress, GetAmmoEffectsCheckType);
		}
	};


	void Install() {
		NullCheckHook<0x523AD8>();
		NullCheckHook<0x64529D>();
		NullCheckHook<0x64553B>();
		NullCheckHook<0x6462C5>();
		NullCheckHook<0x9B5AFA>();
		NullCheckHook<0x9B5BDA>();
		NullCheckHook<0x9B5D2B>();
		NullCheckHook<0x9B6267>();
	}

}
