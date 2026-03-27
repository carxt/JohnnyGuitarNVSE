#include "NPCAccuracy.hpp"
#include <unordered_map>
#include "GameObjects.h"
namespace NPCAccuracy {

	Tables tables;

	std::vector<uintptr_t> GetFactionsInList(BSSimpleList<FactionRank*>* pFactList) {
		std::vector<uintptr_t> retObj{};
		auto pIter = pFactList->GetHead();
		while (pIter && !pIter->IsEmpty()) {
			const FactionRank* pRank = pIter->GetItem();
			pIter = pIter->GetNext();
			if (pRank && pRank->cRank >= 0)
				retObj.push_back(pRank->pFaction->GetFormID());
		}
		return retObj;
	}

	__declspec (noinline) std::vector<uintptr_t> GetFactionsForActor(Actor* r_act) {

		auto actBase = (TESActorBase*)GetPermanentBaseForm(r_act);
		auto retVec = GetFactionsInList(actBase->baseData.GetFactionList());

		ExtraFactionChanges* pFactionChanges = r_act->extraDataList.GetExtraData<ExtraFactionChanges>();
		if (pFactionChanges && pFactionChanges->pFactionChanges) {
			auto vec2 = GetFactionsInList(pFactionChanges->pFactionChanges);
			retVec.insert(retVec.end(), vec2.begin(), vec2.end());
		}
		return retVec;
	}

	void Reset() {
		tables.ACTREF.clear();
	}
	__declspec (noinline) double __fastcall returnActorMult(Actor* a_refr) {

		auto findValInTable = [](uintptr_t dRefId, std::unordered_map<uintptr_t, float>& pMap) -> float {
			auto it = pMap.find(dRefId);
			if (it != pMap.end()) {
				return it->second;
			}
			return 1.0f;
			};
		double retMul = 1.0f;
		retMul *= findValInTable(a_refr->GetFormID(), tables.ACTREF);
		retMul *= findValInTable(GetPermanentBaseForm(a_refr)->GetFormID(), tables.ACTBAS);
		if (auto pCStyle = a_refr->GetCombatStyle()) {
			retMul *= findValInTable(pCStyle->GetFormID(), tables.CSTY);
		}
		auto factionsForAct = GetFactionsForActor(a_refr);
		for (auto factRefId : factionsForAct) {
			retMul *= findValInTable(factRefId, tables.FACT);
		}
		return retMul;

	}
	
	void Install() {
		tables.ACTREF.max_load_factor(0.75);
		tables.FACT.max_load_factor(0.75);
		tables.CSTY.max_load_factor(0.75);
		tables.ACTBAS.max_load_factor(0.75);
		HookNPCAccuracy<0x0524019>();
	}
};