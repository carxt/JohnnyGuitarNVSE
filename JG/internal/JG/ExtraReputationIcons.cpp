#include "ExtraReputationIcons.hpp"
#include "Bethesda/FileFinder.hpp"
#include "Bethesda/GameSettingCollection.hpp"
#include "GameAPI.h"
#include "GameForms.h"
#include "array"
#include "unordered_map"

namespace ExtraReputationIcons {
	using FactionsMap = std::unordered_map<uint32_t, std::array<NiFixedString, 4>>;
	FactionsMap* pFactionIconsMap = nullptr;
	SRWLOCK kMapLock = SRWLOCK_INIT;

	constexpr uint8_t ucReactionMap[Tier::COUNT][Tier::COUNT] = {
		{ Tier::NEUTRAL, Tier::NEUTRAL, Tier::VERY_HAPPY, Tier::VERY_HAPPY },
		{ Tier::IN_PAIN, Tier::NEUTRAL, Tier::VERY_HAPPY, Tier::VERY_HAPPY },
		{ Tier::SAD,	 Tier::SAD,		Tier::IN_PAIN,	  Tier::SAD },
		{ Tier::SAD,	 Tier::SAD,		Tier::IN_PAIN,	  Tier::IN_PAIN }
	};

	SPEC_NOINLINE Tier __fastcall GetCurrentTier(const TESReputation* apReputation) {
		const uint8_t ucNegative = apReputation->GetReputationLevel(TESReputationType::NEGATIVE);
		const uint8_t ucPositive = apReputation->GetReputationLevel(TESReputationType::POSITIVE);
		return static_cast<Tier>(ucReactionMap[ucNegative][ucPositive]);
	}

	STACK_FRAME_OPT_ENABLE
	SPEC_NOINLINE const char* __fastcall GetCustomIcon(const TESReputation* apReputation, const Setting* apGameSetting = nullptr) {
		if (!pFactionIconsMap)
			return nullptr;

		SRWSharedLock kLock(kMapLock);
		auto it = pFactionIconsMap->find(apReputation->GetFormID());
		if (it != pFactionIconsMap->end()) {
			Tier eTier;
			if (apGameSetting) {
				eTier = Tier::IN_PAIN;
				if (apGameSetting == &GameSettingCollection::sRepNegativeGainIcon || apGameSetting == &GameSettingCollection::sRepPositiveLossIcon)
					eTier = Tier::SAD;
				else if (apGameSetting == &GameSettingCollection::sRepNegativeLossIcon || apGameSetting == &GameSettingCollection::sRepPositiveGainIcon)
					eTier = Tier::VERY_HAPPY;
			}
			else {
				eTier = GetCurrentTier(apReputation);
			}
			const char* pPath = it->second[eTier];
			if (pPath && pPath[0])
				return pPath;
		}
		return nullptr;
	}
	STACK_FRAME_OPT_RESET

	template<uint32_t uiAddress>
	class GetReputationIconHook {
		static inline HookUtils::CallDetour kDetour;

		const char* Hook() {
			TESReputation* pThis = reinterpret_cast<TESReputation*>(this);
			const char* pPath = GetCustomIcon(pThis);
			if (pPath)
				return pPath;

			return ThisCall<const char*>(kDetour, pThis);
		}

	public:
		GetReputationIconHook() {
			kDetour.ReplaceCall(uiAddress, &GetReputationIconHook::Hook);
		}
	};

	template<uint32_t uiAddress, uint32_t uiOffset>
	class GetReputationMessageIconHook {
		static inline HookUtils::CallDetour kDetour;

		const char* Hook() {
			Setting* pThis = reinterpret_cast<Setting*>(this);
			uint8_t* pEBP = GetParentBasePtr(_AddressOfReturnAddress());
			TESReputation* pReputation = *reinterpret_cast<TESReputation**>(pEBP - uiOffset);
			if (pReputation) {
				const char* pPath = GetCustomIcon(pReputation, pThis);
				if (pPath)
					return pPath;
			}
			return ThisCall<const char*>(kDetour, pThis);
		}

	public:
		GetReputationMessageIconHook() {
			kDetour.ReplaceCall(uiAddress, &GetReputationMessageIconHook::Hook);
		}
	};

	void Install() {
		// SetCustomReputationChangeIcon
		GetReputationIconHook<0x6156A2>();
		GetReputationIconHook<0x6156FB>();

		// TESReputation::RemoveReputationExact
		GetReputationMessageIconHook<0x615B19, 0x110>();
		GetReputationMessageIconHook<0x615C04, 0x110>();

		// TESReputation::AddReputationExact
		GetReputationMessageIconHook<0x615855, 0x110>();
		GetReputationMessageIconHook<0x61594C, 0x110>();

		// TESReputation::RemoveReputation
		GetReputationMessageIconHook<0x61610A, 0x128>();
		GetReputationMessageIconHook<0x616203, 0x128>();

		// TESReputation::AddReputation
		GetReputationMessageIconHook<0x615F0B, 0x128>();
		GetReputationMessageIconHook<0x615E06, 0x128>();
	}

	STACK_FRAME_OPT_ENABLE
	SPEC_NOINLINE const char* __fastcall Get(const TESReputation* apReputation, Tier aeTier) {
		if (!pFactionIconsMap)
			return nullptr;

		SRWSharedLock kLock(kMapLock);
		auto it = pFactionIconsMap->find(apReputation->GetFormID());
		if (it != pFactionIconsMap->end()) {
			const char* pPath = it->second[aeTier];
			if (pPath && pPath[0])
				return pPath;
		}
		return nullptr;
	}

	const char* __fastcall Get(const TESReputation* apReputation) {
		return Get(apReputation, GetCurrentTier(apReputation));
	}

	SPEC_NOINLINE void __fastcall Set(TESReputation* apReputation, Tier aeTier, const char* apPath) {
		const uint32_t uiFormID = apReputation->GetFormID();
		
		SRWUniqueLock kLock(kMapLock);
		if (apPath && apPath[0]) {
			char cFinalPath[MAX_PATH];
			uint32_t i = 0;
			for (; apPath[i] && i < sizeof(cFinalPath); ++i) {
				cFinalPath[i] = tolower(apPath[i]);
			}
			cFinalPath[i] = 0;

			if (!pFactionIconsMap)
				pFactionIconsMap = new FactionsMap();

			(*pFactionIconsMap)[uiFormID][aeTier] = cFinalPath;
		}
		else if (pFactionIconsMap) {
			(*pFactionIconsMap)[uiFormID][aeTier] = nullptr;
		}
	}

	SPEC_NOINLINE void Dump() {
		if (!pFactionIconsMap)
			return;

		SRWSharedLock kLock(kMapLock);
		auto it = pFactionIconsMap->begin();
		for (auto const& it : *pFactionIconsMap) {
			Console_Print("0x%X - %s %s %s %s", it.first, it.second[0], it.second[1], it.second[2], it.second[3]);
		}
	}

	STACK_FRAME_OPT_RESET
}