#pragma once

#include "NiTriBasedGeom.hpp"
#include "NiTriStripsData.hpp"

NiSmartPointer(NiTriStrips);

class NiTriStrips : public NiTriBasedGeom {
public:
	NiTriStrips();
	virtual ~NiTriStrips();

	CREATE_OBJECT(NiTriStrips, 0xA71CE0);
	NIRTTI_ADDRESS(0x11F4A20);

	static NiTriStrips* Create(uint16_t ausVertices, NiPoint3* apVertex, NiPoint3* apNormal, NiColorA* apColor, NiPoint2* apTexture, uint16_t ausNumTextureSets, NiGeometryData::DataFlags aeNBTMethod, uint16_t ausTriangles, uint16_t ausStrips, uint16_t* apusStripLengths, uint16_t* apusStripLists);

	NiTriStripsData* GetModelData() const;
};

ASSERT_SIZE(NiTriStrips, 0xC4)