#include "AnimActivationHeight.hpp"
#include <GameObjects.h>

namespace AnimActivationHeight {

	float fActivationHeight = 0.f;

	// WARNING
	// Amazingly, #pragma optimize does not apply to functions in templates
	// So never ever enable "Omit frame pointers", otherwise this will break :)
	template<uint32_t uiAddress, int32_t iOffset>
	class Set_Hook {
		static inline HookUtils::CallDetour kDetour;

		float GetEyeLevelHook() {
			uint8_t* pEBP = GetParentBasePtr(_AddressOfReturnAddress());
			TESObjectREFR* pRef = *reinterpret_cast<TESObjectREFR**>(pEBP + iOffset);
			Actor* pThis = reinterpret_cast<Actor*>(this);

			fActivationHeight = pRef->GetPos().z - pThis->GetPos().z;

			return ThisCall<float>(kDetour, this);
		}

	public:
		Set_Hook() {
			kDetour.ReplaceCall(uiAddress, &Set_Hook::GetEyeLevelHook);
		}
	};

	template<uint32_t uiAddress>
	class Reset_Hook {
		static inline HookUtils::CallDetour kDetour;

		static void SetUsedItemLevelHook(int32_t aiLevel) {
			fActivationHeight = 0.f;
			CdeclCall(kDetour, aiLevel);
		}

	public:
		Reset_Hook() {
			kDetour.ReplaceCall(uiAddress, &Reset_Hook::SetUsedItemLevelHook);
		}
	};

	void Init() {
		Set_Hook<0x4FCA4D, 0x8>(); // BGSPlaceableWater::Activate
		Reset_Hook<0x4FCB22>();

		Set_Hook<0x51146C, 0x8>(); // TESObjectACTI::Activate
		Reset_Hook<0x511550>();

		Set_Hook<0x8930BC, 0x10>(); // Actor::PutItemInReference
		Reset_Hook<0x893178>();

		Set_Hook<0x8FF0DF, 0x10>(); // LowProcess::FindSpecialIdletoPlay
		Reset_Hook<0x8FF199>();
	}

	float GetHeight() {
		return fActivationHeight;
	}
}