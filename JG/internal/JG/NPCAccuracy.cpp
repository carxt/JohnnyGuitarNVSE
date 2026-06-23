#include "NPCAccuracy.hpp"
#include "GameObjects.h"

#include <Shared/BSMemory/BSScrapMemory.hpp>

#include <unordered_map>
#include <algorithm>

namespace NPCAccuracy {

	using AccuracyMultMap = std::unordered_map<uint32_t, float>;

	template<typename T>
	using ScrapVector = std::vector<T, BSScrapAllocator<T>>;

	struct alignas(32) AccuracyMultipliers {
		enum MultType {
			ACTOR,
			ACTOR_BASE,
			COMBAT_STYLE,
			FACTION,

			COUNT,
		};

		AccuracyMultMap kMaps[MultType::COUNT];

		AccuracyMultipliers() {
			for (uint32_t i = 0; i < MultType::COUNT; ++i) {
				kMaps[i].max_load_factor(0.75f);
			}
		}

		inline AccuracyMultMap& __fastcall GetMap(MultType aeType) {
			ASSUME_ASSERT(aeType < MultType::COUNT);
			ASSUME_ASSERT(aeType >= MultType::ACTOR);
			return kMaps[aeType];
		}

		float __fastcall GetMultiplier(uint32_t auiFormID, MultType aeType) {
			AccuracyMultMap& rMap = GetMap(aeType);
			auto it = rMap.find(auiFormID);
			if (it != rMap.end())
				return it->second;
			return 1.f;
		}

		inline float __fastcall GetMultiplier(const TESForm* apForm, MultType aeType) {
			return GetMultiplier(apForm->GetFormID(), aeType);
		}

		void __fastcall SetMultiplier(uint32_t auiFormID, MultType aeType, float afMult) {
			GetMap(aeType)[auiFormID] = afMult;
		}

		void __fastcall RemoveMultiplier(uint32_t auiFormID, MultType aeType) {
			GetMap(aeType).erase(auiFormID);
		}

		void __fastcall Reset() {
			GetMap(MultType::ACTOR).clear();
		}
	};

	AccuracyMultipliers* pMultipliers = nullptr;

	static ScrapVector<uint32_t> __fastcall GetFactionsInList(const BSSimpleList<FactionRank*>* apList) {
		ScrapVector<uint32_t> kFactions;
		auto pIter = apList->GetHead();
		while (pIter && !pIter->IsEmpty()) {
			const FactionRank* pRank = pIter->GetItem();
			pIter = pIter->GetNext();
			if (pRank && pRank->cRank >= 0)
				kFactions.push_back(pRank->pFaction->GetFormID());
		}
		return kFactions;
	}

	static SPEC_NOINLINE ScrapVector<uint32_t> __fastcall GetFactionsForActor(Actor* apActor) {
		TESActorBase* pActorBase = static_cast<TESActorBase*>(GetPermanentBaseForm(apActor));
		ScrapVector<uint32_t> kFactions = GetFactionsInList(&pActorBase->baseData.factionList);

		const ExtraFactionChanges* pFactionChanges = apActor->extraDataList.GetExtraData<ExtraFactionChanges>();
		if (pFactionChanges && pFactionChanges->pFactionChanges) {
			ScrapVector<uint32_t> kAdditionalFactions = GetFactionsInList(pFactionChanges->pFactionChanges);
			kFactions.append_range(kAdditionalFactions);

			std::sort(kFactions.begin(), kFactions.end());

			auto kNewEnd = std::unique(kFactions.begin(), kFactions.end());
			kFactions.erase(kNewEnd, kFactions.end());
		}
		return kFactions;
	}

	static SPEC_NOINLINE float __fastcall GetAdditionalWobbleMultiplier(Actor* apActor) {
		float fMultiplier = 1.f;
		if (!pMultipliers) 
			return fMultiplier;

		fMultiplier *= pMultipliers->GetMultiplier(apActor, AccuracyMultipliers::ACTOR);
		
		const TESBoundObject* pBaseForm = GetPermanentBaseForm(apActor);
		if (pBaseForm) [[likely]]
			fMultiplier *= pMultipliers->GetMultiplier(pBaseForm, AccuracyMultipliers::ACTOR_BASE);

		const TESCombatStyle* pCombatStyle = apActor->GetCombatStyle();
		if (pCombatStyle) [[likely]]
			fMultiplier *= pMultipliers->GetMultiplier(pCombatStyle, AccuracyMultipliers::COMBAT_STYLE);

		const ScrapVector<uint32_t> kFactions = GetFactionsForActor(apActor);
		for (uint32_t uiFactionFormID : kFactions) {
			fMultiplier *= pMultipliers->GetMultiplier(uiFactionFormID, AccuracyMultipliers::FACTION);
		}
		return fMultiplier;
	}

	HookUtils::CallDetour kGetGunSpreadDetour;
	class Hook : public Actor {
	public:
		float GetGunSkillHook(enum SpreadMode aeMode) {
			float fSpread = ThisCall<float>(kGetGunSpreadDetour, this, aeMode);
			if (fSpread != 0.f)
				fSpread *= GetAdditionalWobbleMultiplier(this);
			return fSpread;
		}
	};

	void Reset() {
		if (pMultipliers)
			pMultipliers->Reset();
	}

	void __fastcall SetMultiplier(const TESForm* apForm, float afMultiplier) {
		if (!pMultipliers)
			pMultipliers = new AccuracyMultipliers;

		const uint32_t uiFormID = apForm->GetFormID();
		if (apForm->IsActor()) {
			return pMultipliers->SetMultiplier(uiFormID, AccuracyMultipliers::ACTOR, afMultiplier);
		}
		else {
			switch (apForm->GetFormType()) {
				case FORM_TYPE::TESNPC:
				case FORM_TYPE::TESCreature:
					return pMultipliers->SetMultiplier(uiFormID, AccuracyMultipliers::ACTOR_BASE, afMultiplier);
				case FORM_TYPE::TESCombatStyle:
					return pMultipliers->SetMultiplier(uiFormID, AccuracyMultipliers::COMBAT_STYLE, afMultiplier);
				case FORM_TYPE::TESFaction:
					return pMultipliers->SetMultiplier(uiFormID, AccuracyMultipliers::FACTION, afMultiplier);
			}
		}
	}

	float __fastcall GetMultiplier(const TESForm* apForm) {
		if (!pMultipliers)
			return 1.f;

		const uint32_t uiFormID = apForm->GetFormID();
		if (apForm->IsActor()) {
			return pMultipliers->GetMultiplier(uiFormID, AccuracyMultipliers::ACTOR);
		}
		else {
			switch (apForm->GetFormType()) {
				case FORM_TYPE::TESNPC:
				case FORM_TYPE::TESCreature:
					return pMultipliers->GetMultiplier(uiFormID, AccuracyMultipliers::ACTOR_BASE);
				case FORM_TYPE::TESCombatStyle:
					return pMultipliers->GetMultiplier(uiFormID, AccuracyMultipliers::COMBAT_STYLE);
				case FORM_TYPE::TESFaction:
					return pMultipliers->GetMultiplier(uiFormID, AccuracyMultipliers::FACTION);
			}
		}
		return 1.f;
	}

	void __fastcall RemoveMultiplier(const TESForm* apForm) {
		if (!pMultipliers)
			return;

		const uint32_t uiFormID = apForm->GetFormID();
		if (apForm->IsActor()) {
			pMultipliers->RemoveMultiplier(uiFormID, AccuracyMultipliers::ACTOR);
		}
		else {
			switch (apForm->GetFormType()) {
				case FORM_TYPE::TESNPC:
				case FORM_TYPE::TESCreature:
					return pMultipliers->RemoveMultiplier(uiFormID, AccuracyMultipliers::ACTOR_BASE);
				case FORM_TYPE::TESCombatStyle:
					return pMultipliers->RemoveMultiplier(uiFormID, AccuracyMultipliers::COMBAT_STYLE);
				case FORM_TYPE::TESFaction:
					return pMultipliers->RemoveMultiplier(uiFormID, AccuracyMultipliers::FACTION);
			}
		}
	}

	void Install() {
		kGetGunSpreadDetour.ReplaceCall(0x0524019, &Hook::GetGunSkillHook);
	}
};