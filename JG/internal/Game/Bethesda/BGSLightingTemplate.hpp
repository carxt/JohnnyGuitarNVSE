#pragma once

#include "TESForm.hpp"
#include "CellData.hpp"
#include "Gamebryo/NiColor.hpp"

class BGSLightingTemplate : public TESForm {
public:
	BGSLightingTemplate();
	~BGSLightingTemplate();

	InteriorCellData kData;

	TESFORM_TYPE(BGSLightingTemplate);

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
};

#ifdef GAME
ASSERT_SIZE(BGSLightingTemplate, 0x44);
#else
ASSERT_SIZE(BGSLightingTemplate, 0x54);
#endif