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

	using LandRemapMap = std::unordered_map<uint32_t, LandData>;

	LandRemapMap* pRemappedLands = nullptr;

	static SPEC_NOINLINE void CreateMap() {
		if (!pRemappedLands)
			pRemappedLands = new LandRemapMap();
	}

	static SPEC_NOINLINE void DestroyMap() {
		delete pRemappedLands;
		pRemappedLands = nullptr;
	}

	static SPEC_NOINLINE bool __fastcall GetLandRemapData(const TESObjectLAND* apLand, LandData* apData = nullptr) {
		if (!pRemappedLands)
			return false;

		const uint32_t uiFormID = apLand->GetFormID();
		auto it = pRemappedLands->find(uiFormID);
		const bool bRemapped = it != pRemappedLands->end();
		if (!bRemapped) [[likely]]
			return false;
		
		if (apData) [[likely]]
			*apData = it->second;

		return true;
	}

	static SPEC_NOINLINE TESWorldSpace* __fastcall GetLandRemapTargetWorld(const TESObjectLAND* apLand) {
		LandData kData;
		if (!GetLandRemapData(apLand, &kData)) [[likely]]
			return nullptr;

		const uint32_t uiWorldFormID = kData.uiWorldID;
		if (!uiWorldFormID) [[unlikely]]
			return nullptr;

		TESForm* pForm = TESForm::GetFormByNumericID(uiWorldFormID);
		if (pForm && pForm->GetFormType() == FORM_TYPE::TESWorldSpace) [[likely]]
			return static_cast<TESWorldSpace*>(pForm);
		else
			return nullptr;
	}

	template<uint32_t uiAddress>
	class IsLandRemappedHook {
		static inline HookUtils::CallDetour kDetour;

		bool Hook() const {
			const TESObjectLAND* pThis = reinterpret_cast<const TESObjectLAND*>(this);
			if (GetLandRemapData(pThis)) [[unlikely]]
				return true;

			return ThisCall<bool>(kDetour, this);
		}

	public:
		IsLandRemappedHook() {
			kDetour.ReplaceCall(uiAddress, &IsLandRemappedHook::Hook);
		}
	};

	template<uint32_t uiAddress>
	class GetRemapWorldHook {
		static inline HookUtils::CallDetour kDetour;

		TESWorldSpace* Hook() const {
			const TESObjectLAND* pThis = reinterpret_cast<const TESObjectLAND*>(this);
			TESWorldSpace* pWorld = GetLandRemapTargetWorld(pThis);
			if (pWorld) [[unlikely]]
				return pWorld;

			return ThisCall<TESWorldSpace*>(kDetour, pThis);
		}

	public:
		GetRemapWorldHook() {
			kDetour.ReplaceCall(uiAddress, &GetRemapWorldHook::Hook);
		}
	};

	template<uint32_t uiAddress>
	class GetLandXHook {
		static inline HookUtils::CallDetour kDetour;

		int32_t Hook() const {
			const TESObjectLAND* pThis = reinterpret_cast<const TESObjectLAND*>(this);
			LandData kData;
			if (GetLandRemapData(pThis, &kData)) [[unlikely]]
				return kData.GetX();

			return ThisCall<int32_t>(kDetour, pThis);
		}

	public:
		GetLandXHook() {
			kDetour.ReplaceCall(uiAddress, &GetLandXHook::Hook);
		}
	};

	template<uint32_t uiAddress>
	class GetLandYHook {
		static inline HookUtils::CallDetour kDetour;

		int32_t Hook() const {
			const TESObjectLAND* pThis = reinterpret_cast<const TESObjectLAND*>(this);
			LandData kData;
			if (GetLandRemapData(pThis, &kData)) [[unlikely]]
				return kData.GetY();

			return ThisCall<int32_t>(kDetour, pThis);
		}

	public:
		GetLandYHook() {
			kDetour.ReplaceCall(uiAddress, &GetLandYHook::Hook);
		}
	};

	void __fastcall RemapLand(uint32_t auiLandFormID, const TESWorldSpace* apWorld, int16_t asX, int16_t asY) {
		if (!apWorld) {
			if (pRemappedLands)
				pRemappedLands->erase(auiLandFormID);
		}
		else {
			CreateMap();

			LandData kData;
			kData.uiCoords = TESObjectCELL::GetCoord(asX, asY);
			kData.uiWorldID = apWorld->GetFormID();
			pRemappedLands->insert({ auiLandFormID, kData });
		}
	}

	void __fastcall ReloadModel(TESObjectLAND* apLand, bool abLoad) {
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
		return pRemappedLands && !pRemappedLands->empty();
	}

	void __fastcall SerializeData(WriteFunc writeFunc) {
		if (!pRemappedLands)
			return;

		DEBUG_MSG("Serializing remapped lands...");
		uint32_t uiMapSize = pRemappedLands->size();
		writeFunc(&uiMapSize, sizeof(uiMapSize));

		for (auto& it : *pRemappedLands) {
			writeFunc(&it.first, sizeof(uint32_t));
			writeFunc(&it.second, sizeof(LandData));
			DEBUG_MSG("Serialized remapped land: %08X -> world %08X, coords %i, %i", it.first, it.second.uiWorldID, it.second.GetX(), it.second.GetY());
		}
	}

	void __fastcall DeserializeData(ReadFunc readFunc) {
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
					
					CreateMap();

					pRemappedLands->insert({ uiResolvedLandID, kData });
				}
			}
		}

		if (pRemappedLands) {
			for (auto& it : *pRemappedLands) {
				TESForm* pForm = TESForm::GetFormByNumericID(it.first);
				if (pForm && pForm->GetFormType() == FORM_TYPE::TESObjectLAND) {
					TESObjectLAND* pLand = static_cast<TESObjectLAND*>(pForm);
					DEBUG_MSG("Reloading remapped land: %08X", it.first);
					ReloadModel(pLand, true);
				}
			}
		}
	}

	void Install() {
		IsLandRemappedHook<0x534BA8>();
		IsLandRemappedHook<0x535D75>();
		IsLandRemappedHook<0x535C2D>();
		IsLandRemappedHook<0x535FD6>();

		GetRemapWorldHook<0x535E22>();

		GetLandXHook<0x535E4A>();

		GetLandYHook<0x535E3E>();
	}

	void Reset() {
		if (!pRemappedLands)
			return;

		DEBUG_MSG("Resetting remapped lands...");
		std::vector<TESObjectLAND*, BSScrapAllocator<TESObjectLAND*>> kLandsToReload;
		for (auto& it : *pRemappedLands) {
			TESForm* pForm = TESForm::GetFormByNumericID(it.first);
			if (pForm && pForm->GetFormType() == FORM_TYPE::TESObjectLAND) {
				TESObjectLAND* pLand = static_cast<TESObjectLAND*>(pForm);
				if (pLand->pLoadedData)
					kLandsToReload.push_back(pLand);
			}
		}

		DestroyMap();

		for (TESObjectLAND* pLand : kLandsToReload) {
			DEBUG_MSG("Reloading land: %08X", pLand->GetFormID());
			ReloadModel(pLand, true);
		}
	}

}