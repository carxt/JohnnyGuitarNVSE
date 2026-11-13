#pragma once

#ifdef EDITOR
#include "BSSimpleArray.hpp"
#else
#include "BSSoundHandle.hpp"
#endif
#include "TESObjectREFR.hpp"
#include "Gamebryo/NiPlane.hpp"
#include "Gamebryo/NiPoint2.hpp"

class TESWaterForm;
class WadingWaterData;
class PlaceableWaterGroup;
class Actor;
class BSShaderAccumulator;
class BSRenderedTexture;
class NiCamera;
class NiTexture;
class NiDepthStencilBuffer;

class TESWaterSystem {
public:
	TESWaterSystem();
	~TESWaterSystem();

#ifdef GAME
	int32_t												iAccumulationCount;
	int32_t												iGlobalGetWaterGeometryCount;
#else
	bool												bUnk0;
	int32_t												iAccumulationCount;
	int32_t												iGlobalGetWaterGeometryCount;
	bool												bUnkC;
#endif
	NiPointer<BSRenderedTexture>						spWaterHeightMapTexture;
	NiPointer<BSRenderedTexture>						spWaterHeightMapTextureFiltered;
	NiPointer<BSRenderedTexture>						spWaterNormalMapTexture;
	NiPointer<BSRenderedTexture>						spRainHeightMapTexture;
	NiPointer<NiDepthStencilBuffer>						spRefractionDepthStencilBuffer;
	NiPointer<NiTexture>								spWaterNoiseTexture;
	NiPointer<NiTexture>								spWaterNormalMap;
#ifdef EDITOR
	NiPointer<NiRefObject>								spUnk2C;
	NiPointer<NiRefObject>								spUnk30;
#endif
	float												fBlendTimer;
	NiPoint2											kLastDisplaceOffset;
	TESWaterForm*										pBlendToWaterType;
	bool												bUpdateWaterBlend;
	float												fWaterTypeBlendAmount;
	NiTPointerList<PlaceableWaterGroup*>				kPlaceableWaterGroups;
	PlaceableWaterGroup*								pLODWaterGroup;
	NiTPointerMap<TESObjectREFR*, TESObjectREFR*>		kReflectionReferences;
	NiTPointerMap<TESObjectREFR*, TESObjectREFR*>		kDepthReferences;
#ifdef EDITOR
	BSSimpleArray<TESObjectREFR*>*						pAutoWaterReferences;
#endif
	NiTPointerMap<TESWaterForm*, bool>					kWaterTypeUpdates;
#ifdef GAME
	NiTPointerMap<TESObjectREFR*, WadingWaterData*>		kWadingWaterMap;
	BSSoundHandle										hSound;
	float												fLastSplashTime;
	bool												bCull3rdPerson;
#endif

#ifdef GAME
	PlaceableWaterGroup* FindWaterGroup(TESObjectREFR* apWaterRef, TESObjectREFR* apLookupRef, float afHeight) const;
#endif
};

#ifdef GAME
ASSERT_SIZE(TESWaterSystem, 0xA0);
#else
ASSERT_SIZE(TESWaterSystem, 0x90);
#endif

class PlaceableWaterGroup {
public:
	TESWaterForm*							pWaterForm;
	NiPlane									kReflectWaterPlane;
	NiPlane									kRefractWaterPlane;
	NiTPointerList<TESObjectREFR*>			kPlaceableWaters;
	NiTPointerList<TESObjectREFR*>			kObjecstInWater;
	NiTPointerList<Actor*>					kActorsInWater;
	NiTPointerList<PlaceableWaterGroup*>	kSharedReflectionGroups;
	NiPointer<BSRenderedTexture>			spReflectionMap;
	NiAVObjectPtr							spWadingWaterGeometry;
	bool									bGroupAtWorldSpaceWaterHeight;
	bool									bRenderGroup;
	bool									bRenderDepth;
	bool									bRenderGroupReflections;
	bool									bRenderSilhouetteReflections;
	NiTPointerList<NiNode*>					kStaticReflectiveObjects;
	NiTPointerList<NiNode*>					kDynamicReflectiveObjects;
	NiTPointerList<NiNode*>					kStaticDepthObjects;
	NiTPointerList<NiNode*>					kDynamicDepthObjects;
	NiPointer<BSShaderAccumulator>			spGroupReflectionSorter;
	NiPointer<BSShaderAccumulator>			spDepthSorter;
	int32_t									iReflectionThreadStage;
	int32_t									iDepthThreadStage;
	NiPointer<NiCamera>						spReflectionCamera;
	NiPointer<NiCamera>						spDepthCamera;
	int32_t									iStencilMask;
};

ASSERT_SIZE(PlaceableWaterGroup, 0xB0);

class WadingWaterData {
public:
	NiPoint2 kDisplaceOffset;
	NiPoint2 kLastDisplaceOffset;
	NiPoint3 kLastPosition;
};

ASSERT_SIZE(WadingWaterData, 0x1C);