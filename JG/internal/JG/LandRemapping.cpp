#include "LandRemapping.hpp"
#include "GameForms.h"
#include "JohnnySerialization.hpp"
#include "Bethesda/BSShaderManager.hpp"
#include "Bethesda/TESMain.hpp"
#include "Bethesda/FixedStrings.hpp"

#include <shared/BSMemory/BSScrapMemory.hpp>

#include <unordered_map>
#include <vector>

namespace LandRemapping {

#define DEBUG_PRINTS 0

#if DEBUG_PRINTS
#define DEBUG_MSG(...) _MESSAGE(__VA_ARGS__)
#else
#define DEBUG_MSG(...) __noop(__VA_ARGS__)
#endif

	struct LandData {
		uint32_t uiCoords;
		uint32_t uiWorldID;

		int16_t GetX() const {
			return int16_t((uiCoords >> 16) & 0xFFFF);
		}

		int16_t GetY() const {
			return int16_t(uiCoords & 0xFFFF);
		}

		uint32_t GetWorld() const {
			return uiWorldID;
		}
	};

	std::unordered_map<uint32_t, LandData> kRemappedLands;

	class Hooks {
	public:
		bool IsRemapped() const {
			const TESObjectLAND* pThis = reinterpret_cast<const TESObjectLAND*>(this);
			const uint32_t uiFormID = pThis->GetFormID();
			if (auto it = kRemappedLands.find(uiFormID); it != kRemappedLands.end())
				return true;
			return pThis->GetLandRemapped();
		}

		TESWorldSpace* GetRemapWorld() const {
			const TESObjectLAND* pThis = reinterpret_cast<const TESObjectLAND*>(this);
			const uint32_t uiFormID = pThis->GetFormID();
			if (auto it = kRemappedLands.find(uiFormID); it != kRemappedLands.end()) {
				TESForm* pForm = TESForm::GetFormByNumericID(it->second.GetWorld());
				if (pForm->GetFormType() == FORM_TYPE::TESWorldSpace)
					return static_cast<TESWorldSpace*>(pForm);
				else
					return nullptr;
			}
			return ThisCall<TESWorldSpace*>(0x5340B0, pThis);
		}

		int32_t GetRemapX() const {
			const TESObjectLAND* pThis = reinterpret_cast<const TESObjectLAND*>(this);
			const uint32_t uiFormID = pThis->GetFormID();
			if (auto it = kRemappedLands.find(uiFormID); it != kRemappedLands.end())
				return it->second.GetX();

			return pThis->GetDataX();
		}
		
		int32_t GetRemapY() const {
			const TESObjectLAND* pThis = reinterpret_cast<const TESObjectLAND*>(this);
			const uint32_t uiFormID = pThis->GetFormID();
			if (auto it = kRemappedLands.find(uiFormID); it != kRemappedLands.end())
				return it->second.GetY();

			return pThis->GetDataY();
		}
	};

	void RemapLand(uint32_t auiLandFormID, TESWorldSpace* apWorld, int16_t asX, int16_t asY) {
		if (!apWorld) {
			kRemappedLands.erase(auiLandFormID);
		}
		else {
			LandData kData;
			kData.uiCoords = TESObjectCELL::GetCoord(asX, asY);
			kData.uiWorldID = apWorld->GetFormID();
			kRemappedLands[auiLandFormID] = kData;
		}
	}

	void ReloadModel(TESObjectLAND* apLand, bool abLoad) {
		// TallGrassShaderProperty::RemoveFromCell
		CdeclCall(0xB61570, apLand->GetDataX(), apLand->GetDataY());

		if (apLand->pLoadedData && apLand->pLoadedData->ppMesh) {
			for (uint32_t i = 0; i < 4; i++) {
				NiNode* pNode = apLand->pLoadedData->ppMesh[i];
				if (pNode) {
					pNode->RemoveExtraData(BSShaderManager::GetTexPercTag());
					NiAVObject* pDecalNode = pNode->GetObjectByName(FixedStrings::GetDecalNode());
					if (pDecalNode)
						pNode->DetachChild(pDecalNode);
				}
			}
		}

		TESObjectCELL* pCell = apLand->GetParentCell();

		if (pCell) {
			CellMopp* pMopp = pCell->GetCellMopp();
			if (pMopp)
				pMopp->Kill();
		}

		apLand->UnloadVertices();

		if (abLoad) {
			if (apLand->LoadVertices(false))
				apLand->Attach3D();

			if (pCell)
				pCell->SetupMopp();

			// TESTerrainLODManager::UpdateGrass
			CdeclCall(0x57D0A0, TESMain::GetWorldRootCamera()->m_kWorld.m_kTranslate, NiPoint3::UNIT_Y, 1.f);
		}
	}

	bool HasDataToSave() {
		return !kRemappedLands.empty();
	}

	void SerializeData(WriteFunc writeFunc) {
		DEBUG_MSG("Serializing remapped lands...");
		uint32_t uiMapSize = kRemappedLands.size();
		writeFunc(&uiMapSize, sizeof(uiMapSize));

		for (auto& it : kRemappedLands) {
			writeFunc(&it.first, sizeof(uint32_t));
			writeFunc(&it.second, sizeof(LandData));
			DEBUG_MSG("Serialized remapped land: %08X -> world %08X, coords %i, %i", it.first, it.second.uiWorldID, it.second.GetX(), it.second.GetY());
		}
	}

	void DeserializeData(ReadFunc readFunc) {
		DEBUG_MSG("Deserializing remapped lands...");
		using namespace JohnnySerialization;
		uint32_t uiMapSize = 0;
		readFunc(&uiMapSize, sizeof(uiMapSize));

		if (uiMapSize > 0) {
			for (uint32_t i = 0; i < uiMapSize; i++) {
				uint32_t uiFormID = 0;
				LandData kData;
				readFunc(&uiFormID, sizeof(uint32_t));
				readFunc(&kData, sizeof(LandData));

				DEBUG_MSG("Deserialized remapped land: %08X -> world %08X, coords %i, %i", uiFormID, kData.uiWorldID, kData.GetX(), kData.GetY());

				uint32_t uiResolvedLandID = 0;
				if (_ResolveFormID(uiFormID, &uiResolvedLandID) && _ResolveFormID(kData.uiWorldID, &kData.uiWorldID)) {
					DEBUG_MSG("Resolved remapped land: %08X -> world %08X, coords %i, %i", uiResolvedLandID, kData.uiWorldID, kData.GetX(), kData.GetY());
					kRemappedLands[uiResolvedLandID] = kData;
				}
			}
		}

		for (auto& it : kRemappedLands) {
			TESForm* pForm = TESForm::GetFormByNumericID(it.first);
			if (pForm && pForm->GetFormType() == FORM_TYPE::TESObjectLAND) {
				TESObjectLAND* pLand = static_cast<TESObjectLAND*>(pForm);
				DEBUG_MSG("Reloading remapped land: %08X", it.first);
				ReloadModel(pLand, true);
			}
		}
	}

	void Install() {
		HookUtils::ReplaceCall(0x534BA8, &Hooks::IsRemapped);
		HookUtils::ReplaceCall(0x535D75, &Hooks::IsRemapped);
		HookUtils::ReplaceCall(0x535C2D, &Hooks::IsRemapped);
		HookUtils::ReplaceCall(0x535FD6, &Hooks::IsRemapped);
		HookUtils::ReplaceCall(0x535E22, &Hooks::GetRemapWorld);
		HookUtils::ReplaceCall(0x535E4A, &Hooks::GetRemapX);
		HookUtils::ReplaceCall(0x535E3E, &Hooks::GetRemapY);
	}

	void Reset() {
		DEBUG_MSG("Resetting remapped lands...");
		std::vector<TESObjectLAND*, BSScrapAllocator<TESObjectLAND*>> kLandsToReload;
		for (auto& it : kRemappedLands) {
			TESForm* pForm = TESForm::GetFormByNumericID(it.first);
			if (pForm && pForm->GetFormType() == FORM_TYPE::TESObjectLAND) {
				TESObjectLAND* pLand = static_cast<TESObjectLAND*>(pForm);
				if (pLand->pLoadedData)
					kLandsToReload.push_back(pLand);
			}
		}

		kRemappedLands.clear();

		for (TESObjectLAND* pLand : kLandsToReload) {
			DEBUG_MSG("Reloading land: %08X", pLand->GetFormID());
			ReloadModel(pLand, true);
		}
	}

}