#include "JohnnyGameSettings.hpp"

namespace JohnnyGameSettings {
	CustomGameSetting fCombatLocationTargetRadiusMaxBase;
	CustomGameSetting fCombatRangedWeaponRangeBaseMult;

	CustomGameSetting iOverrideDialogueEmotionValues;

	CustomGameSetting fCombatPlanChangeTimer;
	CustomGameSetting fCombatDynamicCoverLostTimer;
	CustomGameSetting fCombatTargetUnreachableTimer;
	CustomGameSetting fCombatSuppressiveFireTimer;
	CustomGameSetting fCombatCoverReevaluateCoverTimer;
	CustomGameSetting fCombatCoverHoldingGroundTimer;
	CustomGameSetting fCombatCoverTargetBlockedTimer;

	CustomGameSetting iFixAudioMarkerLookupAlgo;

	CustomGameSetting sNewline;

	CustomGameSetting fSandboxDurationMultSitting;
	CustomGameSetting fSandboxDurationMultSleeping;
	CustomGameSetting fSandboxDurationMultDialogue;

	CustomGameSetting fSandboxEnergyMultSitting;
	CustomGameSetting fSandboxEnergyMultSleeping;
	CustomGameSetting fSandboxEnergyMultDialogue;

	CustomGameSetting fPreferredTriangleCostMultiplier;
	CustomGameSetting fMinimalUsePathingCost;

	CustomGameSetting fAIDialogueDistance;

	CustomGameSetting fHavokCalculatePitchTimeOut;
	CustomGameSetting fHavokMaxSlopeDefault;

	CustomGameSetting fNPCMaxGunWobbleAngleVATS;

	template <uintptr_t uiAddress>
	class CombatLocationHook {
	private:
		static inline HookUtils::CallDetour kDetour;

		static float __cdecl Hook(float afLeft, float afRight) {
			float fValue = CdeclCall<float>(kDetour, afLeft, afRight);
			return std::max(fValue, fCombatLocationTargetRadiusMaxBase.Float());
		}

	public:
		CombatLocationHook() {
			kDetour.ReplaceCall(uiAddress, Hook);
		}
	};

	template <uintptr_t uiAddress>
	class CombatRangedWeaponRangeHook {
	private:
		static inline HookUtils::CallDetour kDetour;

		static float __fastcall Hook(TESObjectWEAP* apWeapon) {
			float fMaxRange = ThisCall<float>(kDetour, apWeapon);
			if (!apWeapon->IsFixedRange() && apWeapon->IsRangedWeapon())
				fMaxRange *= fCombatRangedWeaponRangeBaseMult.Float();
			return fMaxRange;
		}

	public:
		CombatRangedWeaponRangeHook() {
			kDetour.ReplaceCall(uiAddress, Hook);
		}
	};

	template <uintptr_t uiAddress, const CustomGameSetting& rSetting>
	class CombatTimerResetHook {
	private:
		static inline HookUtils::CallDetour kDetour;

		static void __fastcall Hook(void* apTimer, float afValue) {
			ThisCall<float>(kDetour, apTimer, rSetting.Float());
		}

	public:
		CombatTimerResetHook() {
			kDetour.ReplaceCall(uiAddress, Hook);
		}
	};

	template <uintptr_t uiAddress>
	class OverrideEmotionValuesHook {
		static inline HookUtils::CallDetour kDetour;

		static uint32_t __fastcall Hook(void* apResponse) {
			uint32_t eEmotionType = ThisCall<uint32_t>(kDetour, apResponse);
			if (iOverrideDialogueEmotionValues.Int() <= 0)
				eEmotionType = 0;

			return eEmotionType;
		}

	public:
		OverrideEmotionValuesHook() {
			kDetour.ReplaceCall(uiAddress, Hook);
		}
	};

	void InitCombatValues() { 
		fCombatLocationTargetRadiusMaxBase.Initialize("fCombatLocationTargetRadiusMaxBase", 10.0f);
		fCombatRangedWeaponRangeBaseMult.Initialize("fCombatRangedWeaponRangeBaseMult", 1.0f);

		fCombatPlanChangeTimer.Initialize("fCombatPlanChangeTimer", 1.f);
		fCombatDynamicCoverLostTimer.Initialize("fCombatDynamicCoverLostTimer", 2.f);
		fCombatTargetUnreachableTimer.Initialize("fCombatTargetUnreachableTimer", 5.f);
		fCombatSuppressiveFireTimer.Initialize("fCombatSuppressiveFireTimer", 2.f);
		fCombatCoverReevaluateCoverTimer.Initialize("fCombatCoverReevaluateCoverTimer", 1.f);
		fCombatCoverHoldingGroundTimer.Initialize("fCombatCoverHoldingGroundTimer", 2.f);
		fCombatCoverTargetBlockedTimer.Initialize("fCombatCoverTargetBlockedTimer", 2.f);

		// Thanks lStewieAl
		CombatLocationHook<0x9A089F>();
		CombatLocationHook<0x9A0A0C>();

		CombatRangedWeaponRangeHook<0x9A91C1>();

		CombatTimerResetHook<0x97E037, fCombatPlanChangeTimer>();
		CombatTimerResetHook<0x97E533, fCombatPlanChangeTimer>();
		CombatTimerResetHook<0x97EDAB, fCombatPlanChangeTimer>();

		HookUtils::SafeWrite32(0x998042 + 2, uint32_t(&fCombatDynamicCoverLostTimer.uValue.f));

		HookUtils::SafeWrite32(0x998F4E + 2, uint32_t(&fCombatTargetUnreachableTimer.uValue.f));
		HookUtils::SafeWrite32(0x998FB7 + 2, uint32_t(&fCombatTargetUnreachableTimer.uValue.f));
		
		HookUtils::SafeWrite32(0x9D1019 + 2, uint32_t(&fCombatSuppressiveFireTimer.uValue.f));
		HookUtils::SafeWrite32(0x9D1068 + 2, uint32_t(&fCombatSuppressiveFireTimer.uValue.f));

		CombatTimerResetHook<0x9D26A5, fCombatCoverReevaluateCoverTimer>();
		CombatTimerResetHook<0x9D26D7, fCombatCoverReevaluateCoverTimer>();

		HookUtils::SafeWrite32(0x9D275C + 2, uint32_t(&fCombatCoverHoldingGroundTimer.uValue.f));

		HookUtils::SafeWrite32(0x9D2D3F + 2, uint32_t(&fCombatCoverTargetBlockedTimer.uValue.f));
	}

	void InitOverrideDialogueEmotionValues() {
		iOverrideDialogueEmotionValues.Initialize("iOverrideDialogueEmotionValues", 0);

		OverrideEmotionValuesHook<0x617D59>();
	}

	void InitSandboxValues() {
		fSandboxDurationMultSitting.Initialize("fSandboxDurationMultSitting", 2.f);
		fSandboxDurationMultSleeping.Initialize("fSandboxDurationMultSleeping", 2.f);
		fSandboxDurationMultDialogue.Initialize("fSandboxDurationMultDialogue", 0.5f);

		fSandboxEnergyMultSitting.Initialize("fSandboxEnergyMultSitting", -0.1f);
		fSandboxEnergyMultSleeping.Initialize("fSandboxEnergyMultSleeping", -0.1f);
		fSandboxEnergyMultDialogue.Initialize("fSandboxEnergyMultDialogue", 0.2f);


		HookUtils::SafeWrite32(0x119B194, uint32_t(&fSandboxDurationMultSitting));
		HookUtils::SafeWrite32(0x119B198, uint32_t(&fSandboxDurationMultSleeping));
		HookUtils::SafeWrite32(0x119B1A8, uint32_t(&fSandboxDurationMultDialogue));

		HookUtils::SafeWrite32(0x119B1AC, uint32_t(&fSandboxEnergyMultSitting));
		HookUtils::SafeWrite32(0x119B1B0, uint32_t(&fSandboxEnergyMultSleeping));
		HookUtils::SafeWrite32(0x119B1C0, uint32_t(&fSandboxEnergyMultDialogue));
	}

	void InitPathingValues() {
		fPreferredTriangleCostMultiplier.Initialize("fPreferredTriangleCostMultiplier", 0.01f);
		fMinimalUsePathingCost.Initialize("fMinimalUsePathingCost", 409600.f);

		HookUtils::SafeWrite8(0x6A74A4, 0xD8);
		HookUtils::SafeWrite32(0x6A74A4 + 2, uint32_t(&fPreferredTriangleCostMultiplier.uValue.f));
		
		HookUtils::SafeWrite32(0x6B894D + 2, uint32_t(&fMinimalUsePathingCost.uValue.f));
		HookUtils::SafeWrite32(0x6B8973 + 2, uint32_t(&fMinimalUsePathingCost.uValue.f));
		HookUtils::SafeWrite32(0x6F38DC + 2, uint32_t(&fMinimalUsePathingCost.uValue.f));
		HookUtils::SafeWrite32(0x6F391D + 2, uint32_t(&fMinimalUsePathingCost.uValue.f));
	}

	void InitAIValues() {
		fAIDialogueDistance.Initialize("fAIDialogueDistance", 400.f);

		HookUtils::SafeWrite32(0x8E91D7 + 2, uint32_t(&fAIDialogueDistance.uValue.f));
	}

	HookUtils::CallDetour kHavokInitDetour;
	void __cdecl DeferredHavokInitHook() {
		CdeclCall(kHavokInitDetour);

		// The reason we are only setting values is because game already has globals for them
		// and in order to not confuse other engine modders, it's better this way
		// Also, other Havok GameSettings (which are set after us), also work like this

		float& fMaxWind = *reinterpret_cast<float*>(0x11B02DC);
		fMaxWind = GameSettingCollection::fMaximumWind->Float();

		float& fJumpMoveBase = *reinterpret_cast<float*>(0x1267BBC);
		fJumpMoveBase = GameSettingCollection::fJumpMoveBase->Float();

		float& fJumpMoveMult = *reinterpret_cast<float*>(0x11B0140);
		fJumpMoveMult = GameSettingCollection::fJumpMoveMult->Float();

		float& fJumpFallVelocityMin = *reinterpret_cast<float*>(0x11D01E4);
		fJumpFallVelocityMin = GameSettingCollection::fJumpFallVelocityMin->Float();

		float& fCalculatePitchTimeOut = *reinterpret_cast<float*>(0x11B014C);
		fCalculatePitchTimeOut = fHavokCalculatePitchTimeOut.Float();

		float& fMaxSlopeDefault = *reinterpret_cast<float*>(0x11B0148);
		fMaxSlopeDefault = fHavokMaxSlopeDefault.Float();
	}

	void InitHavokValues() {
		fHavokCalculatePitchTimeOut.Initialize("fHavokCalculatePitchTimeOut", 5.f);
		fHavokMaxSlopeDefault.Initialize("fHavokMaxSlopeDefault", 47.f);

		kHavokInitDetour.ReplaceCall(0x44FC25, DeferredHavokInitHook);
	}

	void InitNPCValues() {
		fNPCMaxGunWobbleAngleVATS.Initialize("fNPCMaxGunWobbleAngleVATS", 15.f);
		HookUtils::SafeWrite32(0x8B1026 + 1, uint32_t(&fNPCMaxGunWobbleAngleVATS));
	}

	void Init() {
		iFixAudioMarkerLookupAlgo.Initialize("iFixAudioMarkerLookupAlgo", 1);

		sNewline.Initialize("sNewline", "\n");

		InitCombatValues();
		InitOverrideDialogueEmotionValues();
		InitSandboxValues();
		InitPathingValues();
		InitAIValues();
		InitHavokValues();
		InitNPCValues();
	}
}