#include "NiTriBasedGeom.hpp"
#include "NiTriBasedGeomData.hpp"

NiTriBasedGeomData* NiTriBasedGeom::GetModelData() const {
	return static_cast<NiTriBasedGeomData*>(m_spModelData.m_pObject);
}