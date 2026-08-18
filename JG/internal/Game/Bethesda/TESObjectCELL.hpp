#pragma once

#include "Gamebryo/NiSmartPointer.hpp"
#include "Gamebryo/NiTMap.hpp"
#include "BSExtraData.hpp"
#include "BSMultiBoundNode.hpp"
#include "BSPortalGraph.hpp"
#include "BSRenderedTexture.hpp"
#include "ExtraDataList.hpp"
#include "TESForm.hpp"
#include "TESFullName.hpp"
#include "TESTexture.hpp"

class NiNode;
class NavMeshArray;
class TESObjectLAND;
class TESWorldSpace;
class TESObjectREFR;
class BGSLightingTemplate;
class BGSAcousticSpace;
class CellMopp;
class bhkWorld;
class SeenData;

class TESObjectCELL : public TESForm, public TESFullName {
public:
	TESObjectCELL();
	~TESObjectCELL();

	struct _State {
		enum State {
			NOT_LOADED	= 0,
			UNLOADING	= 1,
			LOADING		= 2,
			LOADED		= 3,
			DETACHING	= 4,
			ATTACHING	= 5,
			ATTACHED	= 6,
		};
	};
	using State = _State::State;

	struct _CellNodeType {
		enum Type {
			ACTOR = 0,
			MARKER = 1,
			LAND = 2,
			STATIC = 3,
			DYNAMIC = 4,
			OCCLUSION_PLANE = 5,
			PORTAL = 6,
			MULTIBOUND = 7,
			COLLISION = 8,
			LIGHT_MARKER = 9,
			SOUND_MARKER = 10,
			WATER = 11,
			COUNT,
		};
	};
	using CellNodeType = _CellNodeType::Type;

	struct LoadedData {
		NiNodePtr											spCell3D;
		BSSimpleList<TESObjectREFR*>						kLargeAnimatedRefs;
		NiTMap<TESObjectREFR*, NiNode*>						kAnimatedRefs;
		NiTMap<TESForm*, TESObjectREFR*>					kEmittanceSourceRefMap; // Form can be either TESRegion or TESObjectLIGH
		NiTMap<TESObjectREFR*, NiNode*>						kEmittanceLightRefMap;
		NiTMap<TESObjectREFR*, NiPointer<BSMultiBoundNode>> kMultiboundRefMap;
		BSSimpleList<TESObjectREFR*>						kScriptedRefs;
		BSSimpleList<TESObjectREFR*>						kActivatingRefs;
		BSSimpleList<TESObjectREFR*>						kWaterRefs;
	};

	struct ExteriorData {
		int32_t		iCellX;
		int32_t		iCellY;
		Bitfield8	ucLandHideFlags;
	};

	struct InteriorData {
		uint32_t	uiAmbientColor;
		uint32_t	uiDirectionalColor;
		uint32_t	uiFogColor;
		float		fFogNear;
		float		fFogFar;
		int32_t		iDirectionalXY;
		int32_t		iDirectionalZ;
		float		fDirectionalFade;
		float		fClipDist;
		float		fFogPower;
		uint32_t	uiInteriorOffset;
	};

	struct ALIGN1 _CellFlags {
		enum Flags : uint8_t {
			INTERIOR			= 1u << 0,
			HAS_WATER			= 1u << 1,
			CANT_FAST_TRAVEL	= 1u << 2,
			NO_LOD_WATER		= 1u << 3,
			HAS_TEMP_DATA		= 1u << 4,
			PUBLIC				= 1u << 5,
			TEMP_PUBLIC			= 1u << 6,
			FAKE_EXTERIOR		= 1u << 7,
		};

		bool bInterior				: 1;
		bool bHasWater				: 1;
		bool bCantFastTravel		: 1;
		bool bNoLODWater			: 1;
		bool bHasTempData			: 1;
		bool bPublic				: 1;
		bool bTempPublic			: 1;
		bool bFakeExterior			: 1;
	};
	using CellFlags = _CellFlags::Flags;

	struct ALIGN1 _CellGameFlags {
		enum Flags : uint8_t {
			FULLY_SEEN = 1u << 0,
		};

		bool bFullySeen : 1;
	};
	using CellGameFlags = _CellGameFlags::Flags;

	struct ALIGN4 _CellInheritFlags {
		enum Flags : uint32_t {
			AMBIENT_COLOR		= 1u << 0,
			DIRECTIONAL_COLOR	= 1u << 1,
			FOG_COLOR			= 1u << 2,
			FOG_NEAR			= 1u << 3,
			FOG_FAR				= 1u << 4,
			DIRECTIONAL_ROT		= 1u << 5,
			DIRECTIONAL_FADE	= 1u << 6,
			CLIP_DIST			= 1u << 7,
			FOG_POWER			= 1u << 8,
		};

		bool bAmbientColor		: 1;
		bool bDirectionalColor	: 1;
		bool bFogColor			: 1;
		bool bFogNear			: 1;
		bool bFogFar			: 1;
		bool bDirectionalRot	: 1;
		bool bDirectionalFade	: 1;
		bool bClipDist			: 1;
		bool bFogPower			: 1;
	};
	using CellInheritFlags = _CellInheritFlags::Flags;

	Bitfield<_CellFlags>					ucCellFlags;
	Bitfield<_CellGameFlags>				ucCellGameFlags;
	uint8_t									eCellState;
	ExtraDataList							kExtraList;
	union {
		ExteriorData*			 __restrict pCellDataExterior;
		InteriorData*			 __restrict pCellDataInterior;
	};
	TESObjectLAND*							pCellLand;
	float									fWaterHeight;
	bool									bAutoWaterLoaded;
	TESTexture								kNoiseTexture;
	NavMeshArray*							pNavMeshes;
	BSSpinLock								kSpinLock;
	int32_t									iCriticalQueuedRefCount;
	int32_t									iQueuedRefCount;
	int16_t									sDistantRefCount;
	int16_t									sLoadedDistantRefCount;
	BSSimpleList<TESObjectREFR*>			kReferences;
	NiNodePtr								spLightMarkerNode;
	NiNodePtr								spSoundMarkerNode;
	NiAVObjectPtr							spMultiBoundNode;
	union {
		TESWorldSpace*			 __restrict pWorldSpace;		// Exteriors
		uint32_t							uiTempDataOffset;	// Interiors
	};
	LoadedData*								pLoadedData;
	float									fLODFadeInPercent;
	bool									bLODFadingIn;
	bool									bFadedIn;
	bool									bFadingToHighDetail;
	bool									bFadingToLowDetail;
	bool									bDisplayHighDetail;
	bool									bCellDetached;
	bool									bUpdateTerrain;
	BSPortalGraphPtr						spPortalGraph;
	BGSLightingTemplate*					pLightingTemplate;
	Bitfield<_CellInheritFlags>				uiInheritFlags;

	TESFORM_TYPE(TESObjectCELL);

	bool GetInheritFlag(CellInheritFlags aeFlag) const;

	bool IsInterior() const;

	bool HasWater() const;
	void SetHasWater(bool abHasWater);

	bool CantTravelFrom() const;

	bool GetHasTempData() const;

	bool GetPublic() const;

	bool GetTempPublic() const;

	bool GetFakeExterior() const;

	bool GetPublicState() const;

	bool GetOffLimits() const;

	bool GetCantWaitHere() const;

	bool GetFullySeen() const;

	State GetState() const;

	bool IsAttached() const;

	bool IsAttaching() const;

	bool IsLoaded() const;

	bool IsLoading() const;

	ExtraDataList* GetExtra();
	const ExtraDataList* GetExtra() const;

	BSExtraData* GetExtraData(uint8_t aucType) const;

	template <class T>
	inline T* GetExtraData() const noexcept { return static_cast<T*>(GetExtraData(T::_TYPE)); }

	bool HasExtra(uint8_t aucType) const;

	template<class T>
	inline bool HasExtra() const noexcept { return HasExtra(T::_TYPE); }

	TESObjectLAND* GetLand();

	float GetWaterHeight() const;
	bool GetWaterHeight(const NiPoint3& arPos, float& arHeight) const;
	void SetWaterHeight(float afHeight);

	bool GetAutoWaterLoaded() const;

	const char* GetWaterNoiseTextureName() const;

	bool IsRefListLocked() const;
	void CellRefLockEnter();
	void CellRefLockLeave();

	int32_t	GetCriticalQueuedRefCount() const;

	int32_t	GetQueuedRefCount() const;

	bool HasReferences() const;
	BSSimpleList<TESObjectREFR*>* GetRefList();
	const BSSimpleList<TESObjectREFR*>* GetRefList() const;

	TESWorldSpace* GetWorldSpace() const;

	NiNode* Get3D() const;

	NiNode* GetChildNode(CellNodeType aeNode) const;

	NiNode* GetMarkerNode() const;

	NiNode* GetLandNode(uint32_t auiIndex) const;

	NiNode* GetDynamicNode() const;

	BSPortalGraph* GetPortalGraph() const;

	static uint32_t GetCoord(int16_t x, int16_t y);

	int32_t GetDataX() const;
	int32_t GetDataY() const;

	void GetDataXandY(int32_t& aiX, int32_t& aiY) const;
	void GetWorldXandY(float& afX, float& afY) const;

	bool GetHeightAtPos(const NiPoint3& arPos, float& afHeight) const;

	void GetWorldPosition(NiPoint3& arPos) const;

	bhkWorld* GetbhkWorld() const;
	static bhkWorld* GetExteriorbhkWorld();

	InteriorData* GetInteriorData() const;
	ExteriorData* GetExteriorData() const;
	float GetDataClipDist() const;

	int32_t GetDirectionalXY() const;
	int32_t GetDirectionalZ() const;

	float GetNorthRotation() const;

	bool GetHideLand(uint8_t aucBlock) const;

	CellMopp* GetCellMopp() const;
	void SetupMopp();

	float GetDistanceFromPoint(const NiPoint3& arPoint);

	BGSLightingTemplate* GetLightingTemplate() const;
	void SetLightingTemplate(BGSLightingTemplate* apTemplate);

	BGSEncounterZone* GetEncounterZone() const;
	void SetEncounterZone(BGSEncounterZone* apZone);

	BGSAcousticSpace* GetAcousticSpace() const;
	void SetAcousticSpace(BGSAcousticSpace* apSpace);

	SeenData* GetSeenData() const;

	uint32_t GetDetachTime() const;
	void SetDetachTime();
	void SetDetachTime(uint32_t auiTime, bool abForce);

	static uint32_t GetHoursToClearCorpses();
};

ASSERT_SIZE(TESObjectCELL::LoadedData, 0x64);
ASSERT_OFFSET(TESObjectCELL, pCellLand, 0x4C);
ASSERT_OFFSET(TESObjectCELL, spPortalGraph, 0xD4);
ASSERT_SIZE(TESObjectCELL, 0xE0);