#include "MediaLocationControllerTweaks.hpp"
#include <GameForms.h>

class PlayerCharacter;

namespace MediaLocationControllerTweaks {

	// Allows overriding current MediaLocationController through scripts
	namespace ControllerOverride {

		bool bOverrideActive = false;
		MediaLocationController* pOverrideController = nullptr;

		template<uint32_t uiAddress>
		class GetOverridenControllerHook {
			static inline HookUtils::CallDetour kDetour;

			MediaLocationController* Hook() {
				if (bOverrideActive)
					return pOverrideController;
				return ThisCall<MediaLocationController*>(kDetour, this);
			}

		public:
			GetOverridenControllerHook() {
				kDetour.ReplaceCall(uiAddress, &GetOverridenControllerHook::Hook);
			}
		};

		void Reset() {
			bOverrideActive = false;
			pOverrideController = nullptr;
		}

		void Set(MediaLocationController* apController) {
			bOverrideActive = true;
			pOverrideController = apController;
		}

		void InitHooks() {
			GetOverridenControllerHook<0x82FC95>();
			GetOverridenControllerHook<0x82FCA9>();
		}
	}

	// Normally, a MLC requires detected faction actors to use reaction-based mediasets
	// We make use of the 8th flag bit to bypass this check, so a full MLC featureset is available, regardless of detected actor count
	// (In vanilla, if no actors are detected, MLC uses the "Dead Reputation" value to pick the mediaset, overriding the actual faction relation)
	// 
	// That said, we don't prevent the actual counting code, so it can freely count hostile actors and trigger combat-relevant code paths
	namespace ActorCountCheckOverride {

		bool __fastcall ShouldOverrideCount(MediaLocationController* apController) {
			const bool bIgnoreActorCount = apController->uiFlags.bIgnoreActorCount;
			if (bIgnoreActorCount)
				apController->uiFoundFactionActors = 1;
			return bIgnoreActorCount;
		}

		SPEC_NAKED void FactionCheck_Asm() {
			static constexpr uint32_t uiReturnAddr = 0x595785;
			__asm {
				mov     ecx, [ebp - 0x50]
				call	ShouldOverrideCount
				mov     byte ptr[ebp - 0x42], al
				mov     byte ptr[ebp - 0x43], 0
				jmp		uiReturnAddr
			}
		}

		void InitHooks() {
			HookUtils::WriteRelJump(0x59577D, FactionCheck_Asm);
		}
	}

	void ResetOverride() {
		ControllerOverride::Reset();
	}

	void SetOverride(MediaLocationController* apController) {
		ControllerOverride::Set(apController);
	}

	void Install() {
		ControllerOverride::InitHooks();
		ActorCountCheckOverride::InitHooks();
	}

}