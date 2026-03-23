#include "NPCAccuracy.hpp"
#include <unordered_map>
#include "GameObjects.h"
namespace NPCAccuracy {

	Tables tables;

	std::vector<uintptr_t> GetFactionsInList(ExtraFactionChanges::FactionListEntry* pFactList) {
		std::vector<uintptr_t> retObj{};
		auto factHead = pFactList->Head();
		while (factHead) {
			if (factHead->data && factHead->data->rank >= 0) {
				retObj.push_back(factHead->data->faction->GetFormID());
			}
			factHead = factHead->next;
		}
		return retObj;
	}

	__declspec (noinline) std::vector<uintptr_t> GetFactionsForActor(Actor* r_act) {

		auto actBase = (TESActorBase*)GetPermanentBaseForm(r_act);
		auto retVec = GetFactionsInList(&(actBase->baseData.factionList));

		ExtraFactionChanges* fRanks = (ExtraFactionChanges*)r_act->extraDataList.GetByType(kExtraData_FactionChanges);
		if (fRanks) {
			if (auto factionDataList = fRanks->data) {
				auto vec2 = GetFactionsInList(factionDataList);
				retVec.insert(retVec.end(), vec2.begin(), vec2.end());
			}
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