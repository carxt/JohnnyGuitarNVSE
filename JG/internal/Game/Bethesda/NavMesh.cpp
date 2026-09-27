#include "NavMesh.hpp"

// GAME - 0x5582F0
NavMeshTriangle* NavMesh::GetTriangle(uint16_t ausTriangle) const {
    return &kTriangles.GetAt(ausTriangle);
}

// GAME - 0x558200
uint32_t NavMesh::GetTriangleCount() const {
    return kTriangles.GetSize();
}

// GAME - 0x68F0A0
NiPoint3* NavMesh::GetVertex(uint16_t ausVertex) const {
    return &kVertices.GetAt(ausVertex);
}

uint32_t NavMesh::GetVertexCount() const {
    return kVertices.GetSize();
}

// GAME - 0x68F230
// GECK - 0x6A81C0
EdgeExtraInfo* NavMesh::GetEdgeInfo(uint16_t ausTriangle, uint16_t ausEdge) const {
#ifdef GAME
    return ThisCall<EdgeExtraInfo*>(0x68F230, this, ausTriangle, ausEdge);
#else
    return ThisCall<EdgeExtraInfo*>(0x6A81C0, this, ausTriangle, ausEdge);
#endif
}

uint32_t NavMesh::GetEdgeInfoCount() const {
    return kEdgeInfos.GetSize();
}

// GAME - 0x558220
// GECK - 0x626570
NiPoint3 NavMesh::GetTriangleCenter(uint16_t ausTriangle) const {
#ifdef GAME
    return ThisCall<NiPoint3>(0x558220, this, ausTriangle);
#else
    return ThisCall<NiPoint3>(0x626570, this, ausTriangle);
#endif
}

// GAME - 0x68F460
// GECK - 0x6A83A0
bool NavMesh::GetMatchingEdge(uint16_t ausTriangle, uint32_t auiEdge, NavMesh*& arReturnNavMesh, uint16_t& arReturnTriangle, uint16_t& arReturnEdge) const {
#ifdef GAME
    return ThisCall<bool>(0x68F460, this, ausTriangle, auiEdge, &arReturnNavMesh, &arReturnTriangle, &arReturnEdge);
#else
    return ThisCall<bool>(0x6A83A0, this, ausTriangle, auiEdge, &arReturnNavMesh, &arReturnTriangle, &arReturnEdge);
#endif
}

// GAME - 0x696A50
// GECK - 0x6B2080
uint16_t NavMesh::FindTriangleForLocation(const NiPoint3& arLocation, FindTriangleForLocationFilter* apFilter) const {
#ifdef GAME
    return ThisCall<uint16_t>(0x696A50, this, &arLocation, apFilter);
#else
    return ThisCall<uint16_t>(0x6B2080, this, &arLocation, apFilter);
#endif
}

// GAME - 0x697810
// GECK - 0x6B08C0
bool NavMesh::IsPointInsideTriangle(uint16_t ausTriangle, const NiPoint3& arLocatiom, float& arZDiff, FindTriangleForLocationFilter* apFilter) const {
#ifdef GAME
    return ThisCall<bool>(0x697810, this, ausTriangle, &arLocatiom, &arZDiff, apFilter);
#else
    return ThisCall<bool>(0x6B08C0, this, ausTriangle, &arLocatiom, &arZDiff, apFilter);
#endif
}

// GAME - 0x697730
// GECK - 0x6B0810
bool NavMesh::IsPointInsideTriangle(uint16_t ausTriangle, const NiPoint3& arLocatiom, float& arZDiff, float afMaxZdistAbove, float afMaxZdistBelow) const {
#ifdef GAME
    return ThisCall<bool>(0x697730, this, ausTriangle, &arLocatiom, &arZDiff, afMaxZdistAbove, afMaxZdistBelow);
#else
    return ThisCall<bool>(0x6B0810, this, ausTriangle, &arLocatiom, &arZDiff, afMaxZdistAbove, afMaxZdistBelow);
#endif
}

// GAME - 0x690890
// GECK - 0x41FA50
void NavMeshPtr::MakeNavMeshPtr(NavMeshPtr& arNavMeshOut, NavMesh* apNavMesh) {
    arNavMeshOut = NavMeshPtr(apNavMesh);
}

// GAME - 0x464FC0
// GECK - 0x41FA20
NavMeshPtr NavMeshPtr::MakeNavMeshPtr(NavMesh* apNavMesh) {
    return NavMeshPtr(apNavMesh);
}

// GAME - 0x469500
// GECK - 0x423810
uint32_t NavMeshArray::AddNavMesh(NavMeshPtr aPtr) {
#ifdef GAME
    return ThisCall<uint32_t>(0x469500, this, aPtr);
#else
    return ThisCall<uint32_t>(0x423810, this, aPtr);
#endif
}

#ifdef GAME
// GAME - 0x69BB00
void NavMeshArray::RemoveNavMesh(NavMeshPtr aPtr) {
    ThisCall(0x69BB00, this, aPtr);
}

// GAME - 0x69BC50
void NavMeshArray::RemoveNavMeshByIndex(uint32_t auiIndex) {
    ThisCall(0x69BC50, this, auiIndex);
}
#endif

// GAME - 0x69BB90
uint32_t NavMeshArray::GetNavMeshIndex(NavMeshPtr aPtr) const {
    for (uint32_t i = 0; i < kNavMeshes.GetSize(); i++) {
        if (kNavMeshes[i] == aPtr)
            return i;
    }

    return UINT32_MAX;
}

// GAME - 0x464F60
// GECK - 0x41FB10
NavMeshPtr NavMeshArray::GetNavMeshByIndex(uint32_t auiIndex) const {
    if (auiIndex >= kNavMeshes.GetSize())
        return NavMeshPtr::MakeNavMeshPtr(nullptr);
    else
        return kNavMeshes.GetAt(auiIndex);
}

uint32_t NavMeshArray::GetNavMeshCount() const {
    return kNavMeshes.GetSize();
}

// GECK - 0x6B6FE0
uint32_t NavMeshArray::GetNonDeletedNavMeshCount() const {
#ifdef GAME
    uint32_t uiCount = 0;
    const uint32_t uiSize = kNavMeshes.GetSize();
    for (uint32_t i = 0; i < uiSize; ++i) {
        if (!kNavMeshes[i]->GetDeleted())
            ++uiCount;
    }
    return uiCount;
#else
    return ThisCall<uint32_t>(0x6B6FE0, this);
#endif
}