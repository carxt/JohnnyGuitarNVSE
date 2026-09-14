#pragma once

#include "TESForm.hpp"
#include "TESTexture.hpp"
#include "TESFullName.hpp"
#include "BSSimpleArray.hpp"
#include "BSMap.hpp"
#include "Gamebryo/NiSmartPointer.hpp"
#include "Gamebryo/NiPoint2.hpp"
#include "Gamebryo/NiPoint3.hpp"

class BGSTerrainManager;
class TESClimate;
class TESImageSpace;
class TESWaterForm;
class BGSMusicType;
class BGSEncounterZone;
class BGSImpactData;
class TESGrassAreaParam;
class ImpactSwap;
class BSPortalGraph;

class TESWorldSpace : public TESForm, public TESFullName, public TESTexture {
public:
	TESWorldSpace();
	~TESWorldSpace();

	virtual bool GetMapNameForLocation(BSString& arName, NiPoint3 akLocation) const;
	virtual void GetGrassForLocation(NiPoint2 aMinWorldLoc, NiPoint2 aMaxWorldLoc, TESGrassAreaParam* apGrassParams, uint32_t auiNumGrassParams) const;

	struct OFFSET_DATA {
		uint32_t*	pCellFileOffsets;
		NiPoint2	kOffsetMinCoords;
		NiPoint2	kOffsetMaxCoords;
		uint32_t	uiFileOffset;
	};

	struct MapData {
		uint32_t	uiUsableWidth;
		uint32_t	uiUsableHeight;
		int16_t		sNWCellX;
		int16_t		sNWCellY;
		int16_t		sSECellX;
		int16_t		sSECellY;
	};

	struct MapOffsetData {
		float		fMapScale;
		float		fMapOffsetX;
		float		fMapOffsetY;
	};

	struct ALIGN1 _WorldSpaceFlags {
		enum Flags : uint8_t {
			SMALL_WORLD				= 1u << 0,
			NO_FAST_TRAVEL			= 1u << 1,
			//						= 1u << 2,
			HAS_BORDER_REGION		= 1u << 3,
			NO_LOD_WATER			= 1u << 4,
			NO_LOD_NOISE			= 1u << 5,
			NO_NPC_FALL_DAMAGE		= 1u << 6,
			NEEDS_WATER_ADJUSTMENT	= 1u << 7,
		};

		bool bSmallWorld			: 1;
		bool bNoFastTravel			: 1;
		bool						: 1;
		bool bHasBorderRegion		: 1;
		bool bNoLODWater			: 1;
		bool bNoLODNoise			: 1;
		bool bNoNPCFallDamage		: 1;
		bool bNeedsWaterAdjustment	: 1;
	};
	using WorldSpaceFlags = _WorldSpaceFlags::Flags;

	struct ALIGN2 _ParentUseFlags {
		enum Flags : uint16_t {
			LAND	= 1u << 0,
			LOD		= 1u << 1,
			MAP		= 1u << 2,
			WATER	= 1u << 3,
			CLIMATE	= 1u << 4,
		};

		struct FlagBits {
			enum Bits : uint16_t {
				LAND	= 0,
				LOD		= 1,
				MAP		= 2,
				WATER	= 3,
				CLIMATE = 4,
				COUNT
			};
		};

		bool bLand		: 1;
		bool bLOD		: 1;
		bool bMap		: 1;
		bool bWater		: 1;
		bool bClimate	: 1;
	};
	using ParentUseFlags	= _ParentUseFlags::Flags;
	using ParentUseBit		= _ParentUseFlags::FlagBits::Bits;

	using RefListPointerMap = NiTPointerMap<uint32_t, BSSimpleList<TESObjectREFR*>*>;
	using CellPointerMap	= NiTPointerMap<int32_t, TESObjectCELL*>;
	using OffsetDataMap		= NiTMap<TESFile*, TESWorldSpace::OFFSET_DATA*>;

	CellPointerMap*						pCellMap;
	TESObjectCELL*						pPersistentCell;
	uint32_t							kTerrainLODManager; // Unused
	BGSTerrainManager*					pTerrainManager;
	TESClimate*							pClimate;
	TESImageSpace*						pImageSpace;
	ImpactSwap*							pImpactSwap;
	Bitfield<_WorldSpaceFlags>			ucWorldFlags;
	Bitfield<_ParentUseFlags>			usParentUseFlags;
#ifdef GAME
	RefListPointerMap					kFixedPersistentRefMap;
	BSSimpleList<TESObjectREFR*>		kMobilePersistentRefs;
	NiTMap<uint32_t, TESObjectREFR*>*	pOverlappedMultiBoundMap;
#endif
	NiPointer<BSPortalGraph>			spPortalGraph;
	TESWorldSpace*						pParentWorld;
	TESWaterForm*						pWorldWater;
	TESWaterForm*						pLODWater;
	float								fWaterLODHeight;
	MapData								kMapData;
	MapOffsetData						kMapOffsetData;
	BGSMusicType*						pMusicType;
	NiPoint2							kMinCoords;
	NiPoint2							kMaxCoords;
#ifdef GAME
	OffsetDataMap						kOffsetMap;
	BSString							strEditorID;
#endif
	float								fDefaultLandHeight;
	float								fDefaultWaterHeight;
	BGSEncounterZone*					pEncounterZone;
	TESTexture							kCanopyShadowTexture;
	TESTexture							kWaterNoiseTexture;

	TESFORM_TYPE(TESWorldSpace);

	uint32_t GetCellCount() const;

	bool AddCell(TESObjectCELL* apCell);
	void ReleaseCell(TESObjectCELL* apCell);

#ifdef GAME
	TESObjectCELL* LoadCell(int32_t aiX, int32_t aiY);
	void UnloadCell(TESObjectCELL* apCell);
#endif

	TESObjectCELL* GetCellFromWorldCoord(const NiPoint3& arPos) const;

	TESObjectCELL* GetCellFromCellCoord(int32_t aiX, int32_t aiY) const;

	TESObjectCELL* GetCellFromKey(int32_t aiKey) const;

#ifdef GAME
	TESObjectCELL* GetCellByEditorID(const char* apEDID) const;
#endif

	void ClearCellMap();

	TESObjectCELL* GetPersistentCell() const;
	TESObjectCELL* CreatePersistentCell();

	BGSTerrainManager* GetTerrainManager() const;

	TESClimate* GetClimate() const;
	void SetClimate(TESClimate* apClimate);

	TESImageSpace* GetImageSpace() const;
	void SetImageSpace(TESImageSpace* apImageSpace);

	ImpactSwap* GetImpactSwap() const;

	bool GetSmallWorld() const;
	void SetSmallWorld(bool abVal);

	bool GetCantTravelFrom() const;
	void SetCantTravelFrom(bool abVal);

	bool GetCantWaitHere() const;
	void SetCantWaitHere(bool abVal);

	bool GetHasBorderRegion() const;
	void SetHasBorderRegion(bool abVal);

	bool GetNoLODWater() const;
	void SetNoLODWater(bool abVal);

	bool GetNoLODNoise() const;
	void SetNoLODNoise(bool abVal);

	bool GetAllowsNPCFallDamage() const;
	void SetAllowsNPCFallDamage(bool abVal);

	bool GetNeedsWaterAdjustment() const;
	void SetNeedsWaterAdjustment(bool abVal);

	bool GetParentUseFlag(ParentUseBit auiBit) const;
	void SetParentUseFlag(ParentUseBit auiBit, bool abVal);

	void AddPersistentRef(TESObjectREFR* apRef);
	void RemovePersistentRef(TESObjectREFR* apRef);

#ifdef GAME
	void AddToPersistentRefData(TESObjectREFR* apRef);
	void RemoveFromPersistentRefData(TESObjectREFR* apRef);
	void ClearPersistentRefData() const;

	void AssignPersistentRefsToCell(TESObjectCELL* apCell);

	BSSimpleList<TESObjectREFR*>* GetOverlappedMultiBoundRefs(TESObjectCELL* apCell) const;

	void AddMultiBoundRef(TESObjectREFR* apRef);

	void ClearMultiBoundRefs();
#endif

	BSPortalGraph* GetPortalGraph() const;
	BSPortalGraph* CreatePortalGraph();

	TESWorldSpace* GetParentWorld(ParentUseBit auiBit) const;
	TESWorldSpace* GetParentWorldSimple() const;
	void SetParentWorld(TESWorldSpace* apWorld);

	TESWaterForm* GetWaterType() const;
	void SetWaterType(TESWaterForm* apWater);

	TESWaterForm* GetLODWaterType() const;
	void SetLODWaterType(TESWaterForm* apWater);

	float GetWaterLODHeight() const;
	void SetWaterLODHeight(float afHeight);

	MapData* GetWorldMapData() const;

	const char* GetWorldMapTextureName() const;
	void SetWorldMapTextureName(const char* apName);

	float GetWorldMapScale() const;
	void SetWorldMapScale(float afScale);

	float GetWorldMapOffsetX() const;
	void SetWorldMapOffsetX(float afOffset);

	float GetWorldMapOffsetY() const;
	void SetWorldMapOffsetY(float afOffset);

	BGSMusicType* GetMusicType() const;
	void SetMusicType(BGSMusicType* apType);

	float GetMinimumXCoord() const;
	float GetMinimumYCoord() const;
	
	float GetMaximumXCoord() const;
	float GetMaximumYCoord() const;

	float GetDefaultLandHeight() const;
	void SetDefaultLandHeight(float afHeight);

	float GetDefaultWaterHeight() const;
	void SetDefaultWaterHeight(float afHeight);

	BGSEncounterZone* GetEncounterZone() const;
	void SetEncouterZone(BGSEncounterZone* apZone);

	const char* GetCanopyShadowTextureName() const;
	void SetCanopyShadowTextureName(const char* apName);

	const char* GetWaterNoiseTextureName() const;
	void SetWaterNoiseTextureName(const char* apName);

	bool FindCellInFile(TESFile* apFile, int32_t aiX, int32_t aiY) const;

#ifdef GAME
	OFFSET_DATA* CreateOffsetData(const TESFile* apFile);

	OFFSET_DATA* GetOffsetData(const TESFile* apFile) const;

	uint32_t GetIndexForCellCoord(const TESFile* apFile, int32_t aiX, int32_t aiY) const;

	bool GetExtCellDataFromFileByEditorID(const char* apCellID, int32_t& aiOutX, int32_t& aiOutY);
	
	static bool IsFixedRef(const TESObjectREFR* apRef);
#endif

	static uint32_t GetKeyForWorldCoord(NiPoint3& arPoint);
};

#ifdef GAME
ASSERT_SIZE(TESWorldSpace, 0xEC);
#else
ASSERT_SIZE(TESWorldSpace, 0xFC);
#endif