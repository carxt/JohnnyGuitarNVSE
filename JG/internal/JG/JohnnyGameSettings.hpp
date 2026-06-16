#pragma once
#include <GameSettings.h>

namespace JohnnyGameSettings {

	extern CustomGameSetting fCombatLocationTargetRadiusMaxBase;
	extern CustomGameSetting fCombatRangedWeaponRangeBaseMult;
	extern CustomGameSetting iOverrideDialogueEmotionValues;
	extern CustomGameSetting iFixAudioMarkerLookupAlgo;
	extern CustomGameSetting sNewline;


	template <uintptr_t a_addr>
	class CombatLocationHook {
	private:
		static inline uintptr_t hookCall = a_addr;
	public:
		static  float __cdecl Hook(float m_a1, float m_a2) {
			auto res = CdeclCall<float>(hookCall, m_a1, m_a2);
			return fmax(res, fCombatLocationTargetRadiusMaxBase.Float());
		}

		CombatLocationHook() {
			uintptr_t hk_hookPoint = hookCall;
			hookCall = GetRelJumpAddr(hookCall);
			WriteRelCall(hk_hookPoint, (uintptr_t)Hook);
		}
	};

	template <uintptr_t a_addr>
	class CombatRangedWeaponRangeHook {
	private:
		static inline uintptr_t hookCall = a_addr;
	public:
		static  float __fastcall Hook(TESObjectWEAP* r_weap) {
			auto res = ThisCall<float>(hookCall, r_weap);
			if (!ThisCall<bool>(0x0647790, r_weap) && ThisCall<bool>(0x04C0C30, r_weap)) {
				res *= fCombatRangedWeaponRangeBaseMult.Float();
			}
			return res;
		}

		CombatRangedWeaponRangeHook() {
			uintptr_t hk_hookPoint = hookCall;
			hookCall = GetRelJumpAddr(hookCall);
			WriteRelCall(hk_hookPoint, (uintptr_t)Hook);
		}
	};


	template <uintptr_t a_addr>
	class OverrideEmotionValuesHook
	{
		static void* __fastcall Hook(void** ptr)
		{
			auto retVal = ThisCall<void*>(hookCall, ptr);
			if (iOverrideDialogueEmotionValues.Int() <= 0)
			{
				retVal = nullptr;
			}
			return retVal;
		}
		static inline uintptr_t hookCall = a_addr;
	public:
		OverrideEmotionValuesHook() {
			uintptr_t hk_hookPoint = hookCall;
			hookCall = GetRelJumpAddr(hookCall);
			WriteRelCall(hk_hookPoint, (uintptr_t)(Hook));
		}
	};

	SPEC_NOINLINE void Init();
	
};