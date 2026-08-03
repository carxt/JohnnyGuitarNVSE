#pragma once

#include "NiGeometry.hpp"

class NiTriBasedGeomData;

NiSmartPointer(NiTriBasedGeom);

class NiTriBasedGeom : public NiGeometry {
public:
	NiTriBasedGeom();
	virtual ~NiTriBasedGeom();

	virtual void GetModelTriangle(uint16_t ausTriangle, NiPoint3*& arVert0, NiPoint3*& arVert1, NiPoint3*& arVert2) const;

	NIRTTI_ADDRESS(0x11F5B70);

	NiTriBasedGeomData* GetModelData() const;
};

ASSERT_SIZE(NiTriBasedGeom, 0xC4);