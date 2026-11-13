#pragma once

#include "NiTriBasedGeomData.hpp"

NiSmartPointer(NiTriStripsData);

class NiTriStripsData : public NiTriBasedGeomData {
public:
	NiTriStripsData();
	virtual ~NiTriStripsData();

	uint16_t	m_usStrips;
	uint16_t*	m_pusStripLengths;
	uint16_t*	m_pusStripLists;

	CREATE_OBJECT(NiTriStripsData, 0xA75EC0);
	NIRTTI_ADDRESS(0x11F4A70);

	static NiTriStripsData* Create(uint16_t ausVertices, NiPoint3* apVertex, NiPoint3* apNormal, NiColorA* apColor, NiPoint2* apTexture, uint16_t ausNumTextureSets, DataFlags aeNBTMethod, uint16_t ausTriangles, uint16_t ausStrips, uint16_t* apusStripLengths, uint16_t* apusStripLists);

	uint16_t GetStripCount() const;

	uint16_t* GetStripLengths() const;

	uint16_t* GetStripLists() const;

	uint16_t* GetIndices() const { return GetStripLists(); }

	uint16_t GetIndexCount(uint32_t auiStrip = 0) const;

	uint32_t GetStripLengthSum() const;

	void Replace(uint16_t ausStrips, uint16_t* apStripLengths, uint16_t* apStripLists);
};

ASSERT_SIZE(NiTriStripsData, 0x50);