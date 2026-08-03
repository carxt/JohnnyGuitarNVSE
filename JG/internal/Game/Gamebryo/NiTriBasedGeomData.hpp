#pragma once

#include "NiGeometryData.hpp"

NiSmartPointer(NiTriBasedGeomData);

class NiTriBasedGeomData : public NiGeometryData {
public:
	NiTriBasedGeomData();
	virtual ~NiTriBasedGeomData();

	virtual void		SetActiveTriangleCount(uint16_t ausCount);
	virtual uint16_t	GetActiveTriangleCount() const;
	virtual void		GetTriangleIndices(uint16_t ausTriangle, uint16_t& arIndex0, uint16_t& arIndex1, uint16_t& arIndex2) const;
	virtual void		GetStripData(uint16_t& urStrips, const uint16_t*& arStripLengths, const uint16_t*& arTriList, uint16_t& arStripLengthSum) const;

	uint16_t m_usTriangles;
	uint16_t m_usActiveTriangles;

	NIRTTI_ADDRESS(0x11F5B90);

	uint16_t GetTriangleCount() const;
};

ASSERT_SIZE(NiTriBasedGeomData, 0x44);