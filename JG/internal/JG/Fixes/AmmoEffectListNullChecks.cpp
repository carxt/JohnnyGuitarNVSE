#include "AmmoEffectListNullChecks.hpp"
#include "Obsidian/TESAmmoEffect.hpp"

#include "Shared/SafeWrite/SafeWrite.hpp"

namespace AmmoEffectListNullChecks {

	STACK_FRAME_OPT_ENABLE

	static SPEC_NOINLINE BSSimpleList<TESAmmoEffect*>* __fastcall GetAmmoEffectsCheckType(TESForm* apForm, uintptr_t auiAddress) {
		if (IS_ID(apForm, TESAmmo))
			return ThisCall<BSSimpleList<TESAmmoEffect*>*>(auiAddress, apForm);
		return nullptr;
	}

	template<uint32_t uiAddress>
	class NullCheckHook {
		static inline HookUtils::CallDetour kDetour;

		BSSimpleList<TESAmmoEffect*>* Hook() {
			return GetAmmoEffectsCheckType(reinterpret_cast<TESForm*>(this), kDetour);
		}

	public:
		NullCheckHook() {
			kDetour.ReplaceCall(uiAddress, &NullCheckHook::Hook);
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

	STACK_FRAME_OPT_RESET

}
