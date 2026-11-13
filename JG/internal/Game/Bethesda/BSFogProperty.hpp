#pragma once

#include "Gamebryo/NiFogProperty.hpp"
#include "Gamebryo/NiPlane.hpp"

NiSmartPointer(BSFogProperty);

class BSFogProperty : public NiFogProperty {
public:
	BSFogProperty();
	~BSFogProperty();

	float	fStartDistance;
	float	fEndDistance;
	float	fStartWaterDistance;
	float	fEndWaterDistance;
	NiPlane kPlane;
	float	fFalloff;
	float	fHeight;
	NiColor kWaterColor;
	float	fPower;

	void GetDistance(float& arStart, float& arEnd, float& arPower) const;
	void SetDistance(float afStart, float afEnd);

	void GetWaterDistance(float& arStart, float& arEnd) const;
	void SetWaterDistance(float afStart, float afEnd);

	float GetFogHeight() const;
	void SetFogHeight(float afHeight);

	const NiColor& GetWaterColor() const;
	void SetWaterColor(const NiColor& arColor);

	float GetPower() const;
	void SetPower(float afPower);

	void SetDepth(float afDepth);
};

ASSERT_SIZE(BSFogProperty, 0x64)