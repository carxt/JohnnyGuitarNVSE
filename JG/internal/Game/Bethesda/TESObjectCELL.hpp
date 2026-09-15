#pragma once

#include "BSExtraData.hpp"
#include "BSMultiBoundNode.hpp"
#include "BSRenderedTexture.hpp"
#include "CellData.hpp"
#include "ExtraDataList.hpp"
#include "TESForm.hpp"
#include "TESFullName.hpp"
#include "TESTexture.hpp"
#include "Gamebryo/NiTMap.hpp"

class NiNode;
class NavMeshArray;
class TESObjectLAND;
class TESWorldSpace;
class TESImageSpace;
class TESObjectREFR;
class TESWaterForm;
class TESClimate;
class BGSLightingTemplate;
class BGSAcousticSpace;
class BGSEncounterZone;
class CellMopp;
class bhkWorld;
class SeenData;
class NiAVObject;
class NiNode;
class BSPortalGraph;
class Actor;
class TESActorBase;
class IntSeenData;
class TESRegionList;

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
			ACTOR			= 0,
			MARKER			= 1,
			LAND			= 2,
			STATIC			= 3,
			DYNAMIC			= 4,
			OCCLUSION_PLANE	= 5,
			PORTAL			= 6,
			MULTIBOUND		= 7,
			COLLISION		= 8,
			LIGHT_MARKER	= 9,
			SOUND_MARKER	= 10,
			WATER			= 11,
			COUNT,
		};
	};
	using CellNodeType = _CellNodeType::Type;

	struct LoadedData {
		LoadedData(const LoadedData&) = delete;
		LoadedData& operator=(const LoadedData&) = delete;

		NiPointer<NiNode>									spCell3D;
		BSSimpleList<TESObjectREFR*>						kLargeAnimatedRefs;
		NiTMap<TESObjectREFR*, NiNode*>						kAnimatedRefs;
		NiTMap<TESForm*, TESObjectREFR*>					kEmittanceSourceRefMap; // Form can be either TESRegion or TESObjectLIGH
		NiTMap<TESObjectREFR*, NiNode*>						kEmittanceLightRefMap;
		NiTMap<TESObjectREFR*, NiPointer<BSMultiBoundNode>> kMultiboundRefMap;
		BSSimpleList<TESObjectREFR*>						kScriptedRefs;
		BSSimpleList<TESObjectREFR*>						kActivatingRefs;
		BSSimpleList<TESObjectREFR*>						kWaterRefs;
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

	struct ALIGN4 _TemplateInheritFlags {
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
	using TemplateInheritFlags = _TemplateInheritFlags::Flags;

	Bitfield<_CellFlags>					ucCellFlags;
#ifdef GAME
	Bitfield<_CellGameFlags>				ucCellGameFlags;
#endif
	uint8_t									eCellState;
	ExtraDataList							kExtraList;
	union {
		ExteriorCellData*		 __restrict pCellDataExterior;
		InteriorCellData*		 __restrict pCellDataInterior;
	};
	TESObjectLAND*							pCellLand;
	float									fWaterHeight;
	bool									bAutoWaterLoaded;
	TESTexture								kWaterNoiseTexture;
	NavMeshArray*							pNavMeshes;
	BSSpinLock								kSpinLock;
	int32_t									iCriticalQueuedRefCount;
	int32_t									iQueuedRefCount;
	int16_t									sDistantRefCount;
	int16_t									sLoadedDistantRefCount;
	BSSimpleList<TESObjectREFR*>			kReferences;
	NiPointer<NiNode>						spLightMarkerNode;
	NiPointer<NiNode>						spSoundMarkerNode;
	NiPointer<NiAVObject>					spMultiBoundNode;
#ifdef GAME
	union {
		TESWorldSpace*			 __restrict pWorldSpace;		// Exteriors
		uint32_t							uiTempDataOffset;	// Interiors
	};
#endif
	LoadedData*								pLoadedData;
	float									fLODFadeInPercent;
	bool									bLODFadingIn;
	bool									bFadedIn;
	bool									bFadingToHighDetail;
	bool									bFadingToLowDetail;
	bool									bDisplayHighDetail;
	bool									bCellDetached;
	bool									bUpdateTerrain;
	NiPointer<BSPortalGraph>				spPortalGraph;
	BGSLightingTemplate*					pLightingTemplate;
	Bitfield<_TemplateInheritFlags>			uiLightingTemplateInheritFlags;
#ifdef EDITOR
	uint32_t								unkFC;
#endif

	TESFORM_TYPE(TESObjectCELL);

	bool GetPersistentCell() const;
	void SetPersistentCell(bool abPersist);

	bool GetInterior() const;
	void SetInterior(bool abInterior);

	bool GetHasWater() const;
	void SetHasWater(bool abHasWater);

	bool GetCantTravelFrom() const;

	bool GetHasTempData() const;

	bool GetPublic() const;
	void SetPublic(bool abPublic);

	bool GetTempPublic() const;
	void SetTempPublic(bool abPublic);

	bool GetFakeExterior() const;
	void SetFakeExterior(bool abExterior);

	bool GetPublicState() const;

	bool GetOffLimits() const;
	void SetOffLimits(bool abOffLimits);

	bool GetCantWaitHere() const;

#ifdef GAME
	bool GetFullySeen() const;
#endif

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

	NavMeshArray* GetNavMeshArray() const;
	void SetNavMeshArray(NavMeshArray* apArray);

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
	uint32_t GetReferenceCount() const;
	BSSimpleList<TESObjectREFR*>* GetRefList();
	const BSSimpleList<TESObjectREFR*>* GetRefList() const;

	void AddReference(TESObjectREFR* apReference, bool abOnTop);
#ifdef GAME
	void AddReferenceSimple(TESObjectREFR* apReference);
#endif
	void RemoveReference(TESObjectREFR* apReference);

	void AddAnimatedRef(TESObjectREFR* apReference);
	void RemoveAnimatedRef(TESObjectREFR* apReference);

	void AddEmittanceRef(TESObjectREFR* apReference);
	void RemoveEmittanceRef(TESObjectREFR* apReference);

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

	InteriorCellData* GetInteriorData() const;
	ExteriorCellData* GetExteriorData() const;

	uint32_t GetDataAmbientColor() const;
	void GetDataAmbientColor(NiColor& arColor) const;
	void SetDataAmbientColor(uint32_t auiColor);

	uint32_t GetDataDirectionalColor() const;
	void GetDataDirectionalColor(NiColor& arColor) const;
	void SetDataDirectionalColor(uint32_t auiColor);

	uint32_t GetDataFogColor() const;
	void GetDataFogColor(NiColor& arColor) const;
	void SetDataFogColor(uint32_t auiColor);

	float GetDataFogNearPlane() const;
	void SetDataFogNearPlane(float afVal);

	float GetDataFogFarPlane() const;
	void SetDataFogFarPlane(float afVal);

	int32_t GetDataDirectionalXY() const;
	void SetDataDirectionalXY(int32_t aiVal);

	int32_t GetDataDirectionalZ() const;
	void SetDataDirectionalZ(int32_t aiVal);

	float GetDataDirectionalFade() const;
	void SetDataDirectionalFade(float afVal);

	float GetDataClipDist() const;
	void SetDataClipDist(float afVal);

	float GetDataFogPower() const;
	void SetDataFogPower(float afVal);

	bool GetHideLand(uint8_t aucBlock) const;

	CellMopp* GetCellMopp() const;
	void SetupMopp();

	float GetDistanceFromPoint(const NiPoint3& arPoint);

	BGSLightingTemplate* GetLightingTemplate() const;
	void SetLightingTemplate(BGSLightingTemplate* apTemplate);

	bool GetLightingTemplateInheritFlag(TemplateInheritFlags aeFlag) const;
	void SetLightingTemplateInheritFlag(TemplateInheritFlags aeFlag, bool abVal);

	BGSEncounterZone* GetEncounterZone() const;
	void SetEncounterZone(BGSEncounterZone* apZone);

	BGSAcousticSpace* GetAcousticSpace() const;
	void SetAcousticSpace(BGSAcousticSpace* apSpace);

	TESClimate* GetClimate() const;
	void SetClimate(TESClimate* apClimate);

	TESImageSpace* GetImageSpace() const;
	TESImageSpace* GetUsableImageSpace() const;
	void SetImageSpace(TESImageSpace* apImageSpace);

	TESWaterForm* GetWaterType() const;
	void SetWaterType(TESWaterForm* apWater);

	ImpactSwap* GetImpactSwap() const;
	void SetImpactSwap(ImpactSwap* apSwap);

	BGSMusicType* GetMusicType(NiPoint3* apPos = nullptr) const;
	void SetMusicType(BGSMusicType* apType);

	TESRegionList* GetRegionList() const;
	TESRegionList* GetRegionList(bool abCreate);

	TESForm* GetOwner() const;

	TESGlobal* GetOwnershipGlobal() const;

	int32_t GetOwnershipRank() const;

	void SetOwnership(TESForm* apOwner);

#ifdef GAME
	bool IsActorCellOwner(Actor* apActor) const;

	bool IsActorTrespassing(Actor* apActor) const;
#endif

	bool IsActorBaseCellOwner(TESActorBase* apActorBase) const;

#ifdef GAME
	float GetNorthRotation() const;

	SeenData* GetSeenData() const;
	void ClearSeenData();

	void UpdateSeenDataForPlayer();

	void UpdateSeenData(const NiPoint3& arPos);

	IntSeenData* GetIntSeenSection(int32_t aiSectionX, int32_t aiSectionY) const;
	IntSeenData* GetIntSeenSection(int32_t aiSectionX, int32_t aiSectionY, bool abCreate);

	int32_t GetSeenValue(const NiPoint3& arPos) const;

	static float GetSeenDataUpdateRadius();

	uint32_t GetDetachTime() const;
	void SetDetachTime();
	void SetDetachTime(uint32_t auiTime, bool abForce);

	static uint32_t GetHoursToClearCorpses();
#endif
};

#ifdef GAME
ASSERT_SIZE(TESObjectCELL, 0xE0);
#else
ASSERT_SIZE(TESObjectCELL, 0x100);
#endif
ASSERT_SIZE(TESObjectCELL::LoadedData, 0x64);