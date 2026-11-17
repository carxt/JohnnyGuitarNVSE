#include "NiTriBasedGeom.hpp"
#include "NiTriBasedGeomData.hpp"

NiTriBasedGeomData* NiTriBasedGeom::GetModelData() const {
	return static_cast<NiTriBasedGeomData*>(NiGeometry::GetModelData());
}

// GAME - 0x4567B0
uint16_t NiTriBasedGeom::GetTriangleCount() const {
	return GetModelData()->GetTriangleCount();
}

void NiTriBasedGeom::GetTriangleIndices(uint16_t ausTriangle, uint16_t& arIndex0, uint16_t& arIndex1, uint16_t& arIndex2) const {
	GetModelData()->GetTriangleIndices(ausTriangle, arIndex0, arIndex1, arIndex2);
}
