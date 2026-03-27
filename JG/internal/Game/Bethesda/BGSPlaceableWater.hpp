#pragma once

#include "TESBoundObject.hpp"
#include "TESModel.hpp"

class TESWaterForm;

class BGSPlaceableWater : public TESBoundObject, public TESModel {
public:
	BGSPlaceableWater();
	~BGSPlaceableWater();

	struct ALIGN4 _WaterFlags {
		enum WaterFlags {
			REFLECTION_ENABLED				= 0x1,
			REFLECTS_ACTORS					= 0x2,
			REFLECTS_LAND					= 0x4,
			REFLECTS_LOD_LAND				= 0x8,
			REFLECTS_LOD_BUILDINGS			= 0x10,
			REFLECTS_LOD_TREES				= 0x20,
			REFLECTS_SKY					= 0x40,
			REFLECTS_NO_REFERENCE			= 0x80,
			REFLECTS_DEAD_ACTORS			= 0x100,
			REFRACTION_ENABLED				= 0x200,
			REFRACTS_ACTORS					= 0x400,
			REFRACTS_LAND					= 0x800,
			//								  0x1000
			//								  0x2000
			//								  0x4000
			//								  0x8000
			REFRACTS_NO_REFERENCE			= 0x10000,
			REFRACTS_DEAD_ACTORS			= 0x20000,
			SILHOUETTE_REFLECTIONS			= 0x40000,
			// 								  0x80000
			//								  0x100000
			//								  0x200000
			//								  0x400000
			//								  0x800000
			//								  0x1000000
			//								  0x2000000
			//								  0x4000000
			LOD_WATER						= 0x8000000,
			ENABLE_DEPTH					= 0x10000000,
			ENABLE_OBJECT_TEXCOORD			= 0x20000000,
			AUTO_WATER						= 0x40000000,
			NO_UNDERWATER_FOG				= 0x80000000,
		};

		bool bReflectionEnabled		: 1;
		bool bReflectsActors		: 1;
		bool bReflectsLand			: 1;
		bool bReflectsLODLand		: 1;
		bool bReflectsLODBuildings	: 1;
		bool bReflectsLODTrees		: 1;
		bool bReflectsSky			: 1;
		bool bReflectsNoReference	: 1;
		bool bReflectsDeadActors	: 1;
		bool bRefractionEnabled		: 1;
		bool bRefractsActors		: 1;
		bool bRefractsLand			: 1;
		bool						: 4;
		bool bRefractsNoReference	: 1;
		bool bRefractsDeadActors	: 1;
		bool bSilhouetteReflections	: 1;
		bool						: 5;
		bool						: 3;
		bool bLODWater				: 1;
		bool bEnableDepth			: 1;
		bool bEnableObjectTexCoord	: 1;
		bool bAutoWater				: 1;
		bool bNoUnderwaterFog		: 1;
	};
	using WaterFlags = _WaterFlags::WaterFlags;

	struct Data {
		Bitfield<_WaterFlags>	uiWaterFlags;
		TESWaterForm*			pWaterType;
	};

	Data kData;

	TESFORM_TYPE(BGSPlaceableWater);

	Data* GetData();

	void SetWaterType(TESWaterForm* apWaterType);

	bool GetFlag(uint32_t aeFlag) const;
	void SetFlag(uint32_t aeFlag, bool abVal);
	
	bool GetReflectionEnabled() const;
	void SetReflectionEnabled(bool abVal);

	bool GetReflectsActors() const;
	void SetReflectsActors(bool abVal);

	bool GetReflectsLand() const;
	void SetReflectsLand(bool abVal);

	bool GetReflectsSky() const;
	void SetReflectsSky(bool abVal);

	bool GetReflectsLODLand() const;
	void SetReflectsLODLand(bool abVal);

	bool GetReflectsLODBuildings() const;
	void SetReflectsLODBuildings(bool abVal);

	bool GetReflectsLODTrees() const;
	void SetReflectsLODTrees(bool abVal);

	bool GetReflectsLOD() const;
	void SetReflectrsLOD(bool abVal);

	bool GetReflectsNoReference() const;
	void SetReflectsNoReference(bool abVal);

	bool GetReflectsDeadActors() const;
	void SetReflectsDeadActors(bool abVal);

	bool GetLODWater() const;
	void SetLODWater(bool abVal);

	bool GetRefractionEnabled() const;
	void SetRefractionEnabled(bool abVal);

	bool GetRefractsActors() const;
	void SetRefractsActors(bool abVal);

	bool GetRefractsLand() const;
	void SetRefractsLand(bool abVal);

	bool GetSilhouetteReflections() const;
	void SetSilhouetteReflections(bool abVal);

	bool GetDepthEnabled() const;
	void SetDepthEnabled(bool abVal);

	bool GetObjectTexCoordsEnabled() const;
	void SetObjectTexCoordsEnabled(bool abVal);

	bool GetAutomaticWater() const;
	void SetAutomaticWater(bool abVal);

	bool GetUnderwaterFog() const;
	void SetUnderwaterFog(bool abVal);
};

ASSERT_SIZE(BGSPlaceableWater, 0x50);