#pragma once

#include "GridCellArray.hpp"
#include "IOTask.hpp"
#include "Sky.hpp"
#include "TESWaterSystem.hpp"

class TESActorBase;
class NavMeshInfoMap;
class LoadedAreaBound;
class NiFogProperty;
class TESWorldSpace;
class ImageSpaceModifierInstance;
class TESObjectREFR;
class QueuedFile;
class GridDistantArray;
class BSTempNodeManager;
class bhkPickData;
class TESRegion;
class TESLandTexture;
NiSmartPointer(NiTexture);

struct DeadCountObject {
	TESActorBase*	pActorBase;
	uint16_t		uiCount;
};

class TES {
public:
	virtual bool GetMapNameForLocation(BSString& arName, NiPoint3 akLocation, TESWorldSpace* apWorldSpace) const;

	GridDistantArray*									pGridDistantArray;
	GridCellArray*										pGridCellArray;
	NiNode*												pObjRoot;
	NiNode*												pLODRoot;
	NiNode*												pObjLODWaterRoot;
	BSTempNodeManager*									pTempNodeManager;
	NiDirectionalLight*									pObjLight;
	NiFogProperty*										pObjFog;
	int32_t												iCurrentGridX;
	int32_t												iCurrentGridY;
	int32_t												iCurrentQueuedX;
	int32_t												iCurrentQueuedY;
	TESObjectCELL*										pInteriorCell;
	TESObjectCELL**										pInteriorBuffer;
	TESObjectCELL**										pExteriorBuffer;
	uint32_t											uiTempInteriorBufferSize;
	uint32_t											uiTempExteriorBufferSize;
	int32_t												iSaveGridX;
	int32_t												iSaveGridY;
	bool												bCollisionBoxes;
	bool												bRunningCellTests;
	bool												bRunningCellTests2;
	void*												pfnTACCallbackFunc;
	void*												pTACCallbackData;
	TESRegion*											pTACRegionFilter;
	bool												bShowLandBorders;
	TESWaterSystem*										pWaterSystem;
	Sky*												pSky;
	BSSimpleList<NiPointer<ImageSpaceModifierInstance>> kActiveImageSpaceModifiers;
	uint32_t											uiTotalToLoad;
	uint32_t											uiLoaded;
	bool												bDisablePercentageUpdate;
	bool												bUpdateGridString;
	float												fCellDeltaX;
	float												fCellDeltaY;
	TESWorldSpace*										pWorldSpace;
	BSSimpleList<TESObjectCELL*>						kLastLoadedExteriors;
	BSSimpleList<TESObjectREFR*>						kBedsAndChairs;
	BSSimpleList<DeadCountObject*>						kDeadCount;
	NiPointer<QueuedFile>								spPreloadedAddonNodes;
	NiPointer<NiTexture>								spBloodDecalPreload1;
	NiPointer<QueuedFile>								spPreloadedForms;
	void*												pParticleCacheHead;
	bool												bFadeWhenLoading;
	bool												bAllowUnusedPurge;
	uint32_t											uiPlaceableWaterCount;
	NavMeshInfoMap*										pNavMeshInfoMap;
#ifdef GAME
	NiPointer<LoadedAreaBound>							spLoadedAreaBound;
#endif

	static TES* GetSingleton();

	Sky* GetSky() const;

	NiNode* GetRoot() const;

	TESWaterSystem* GetWaterSystem() const;

	TESWorldSpace* GetWorldSpace() const;

	TESObjectCELL* GetInterior() const;
	TESObjectCELL* GetCurrentCell() const;
	TESObjectCELL* GetGridCellCell(int32_t aiX, int32_t aiY) const;
	TESObjectCELL* GetCellForPoint(NiPoint3 akPoint) const;

	NavMeshInfoMap* GetNavMeshInfoMap();

	BSSimpleList<NiPointer<ImageSpaceModifierInstance>>* GetActiveImageSpaceModifiers();

	BSSimpleList<TESObjectREFR*>* GetBedsAndChairs();

	bool IsRunningCellTests() const;

	void AddTempDebugObject(NiAVObject* apObject, float afTime);

	bool IsCellLoaded(const TESObjectCELL* apCell, bool abIgnoreBuffered) const;
	IO_TASK_PRIORITY GetCellPriority(TESObjectCELL* apCell, NiPoint3* apPos) const;

	bool CanAttach3D(TESObjectREFR* apRef);

	GridCell* GetGridCell(int32_t aX, int32_t aY);

	bool GetLandHeight(const NiPoint3& arPosition, float& arfHeight) const;
#ifdef GAME
	bool GetLandNormal(const NiPoint3& arPosition, NiPoint3& arNormal, NiPoint3& arFaceNormal) const;
	bool GetLandColor(const NiPoint3& arPosition, NiColorA& arColor) const;
	TESLandTexture* GetLandTexture(const NiPoint3& arPosition) const;
	float GetLandFrictionValue(const NiPoint3& arPosition) const;
	float GetLandRestitutionValue(const NiPoint3& arPosition) const;
#endif
	NiGeometry* GetLandGeometry(const NiPoint2& arPosition) const;

#ifdef GAME
	NiAVObject* Pick(bhkPickData& arPickData, bool abHavok) const;
	NiAVObject* HavokPick(bhkPickData& arPickData) const;
#endif

	void CreateTextureImage(const char* apPath, NiTexturePtr& aspTexture, bool abNoFileOK, bool abArchiveOnly);

	NiObject* CreateDeepCopySameTextures(NiObject* apObject, NiCloningProcess& arCloneProc);
	static void CloneModelData(NiObject* apObject);

	float GetWaterHeight(const NiPoint3& arPos, const TESObjectCELL* apCell) const;
};

#ifdef GAME
ASSERT_SIZE(TES, 0xC4);
#else
ASSERT_SIZE(TES, 0xC0);
#endif