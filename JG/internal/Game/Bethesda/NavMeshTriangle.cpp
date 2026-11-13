#include "NavMeshTriangle.hpp"

// GAME - 0x5582D0
uint16_t NavMeshTriangle::GetVertex(uint16_t ausVertex) const {
    ASSUME_ASSERT(ausVertex < 3);
    return usVertices[ausVertex];
}

// GAME - 0x68F2C0
uint16_t NavMeshTriangle::GetTriOrExtraInfo(uint16_t ausTriangle) const {
    ASSUME_ASSERT(ausTriangle < 3);
    return usTriangles[ausTriangle];
}

uint16_t NavMeshTriangle::GetTriangle(uint16_t ausTriangle) const {
    ASSUME_ASSERT(ausTriangle < 3);
    if (!EdgeHasExtraInfo(ausTriangle))
        return usTriangles[ausTriangle];
    else
        return UINT16_MAX;
}

// GAME - 0x6A5B30
void NavMeshTriangle::GetVerts(uint16_t& ausVertex0, uint16_t& ausVertex1, uint16_t& ausVertex2) const {
    ausVertex0 = usVertices[0];
    ausVertex1 = usVertices[1];
	ausVertex2 = usVertices[2];
}

// GAME - 0x6A5B70
void NavMeshTriangle::GetSides(uint16_t& ausTriangle0, uint16_t& ausTriangle1, uint16_t& ausTriangle2) const {
	ausTriangle0 = usTriangles[0];
	ausTriangle1 = usTriangles[1];
	ausTriangle2 = usTriangles[2];
}

void NavMeshTriangle::InvalidateVertex(uint16_t ausVertex) {
    ASSUME_ASSERT(ausVertex < 3);
    usVertices[ausVertex] = UINT16_MAX;
}

void NavMeshTriangle::InvalidateTriangle(uint16_t ausTriangle) {
    ASSUME_ASSERT(ausTriangle < 3);
    usTriangles[ausTriangle] = UINT16_MAX;
}

bool NavMeshTriangle::IsVertexValid(uint16_t ausVertex) const {
    ASSUME_ASSERT(ausVertex < 3);
    return usVertices[ausVertex] != UINT16_MAX;
}

// GAME - 0x68F200
bool NavMeshTriangle::IsEdgeConnected(uint16_t ausEdge) const {
    ASSUME_ASSERT(ausEdge < 3);
    return usTriangles[ausEdge] != UINT16_MAX;
}

bool NavMeshTriangle::IsEdgeOpen(uint16_t ausEdge) const {
    ASSUME_ASSERT(ausEdge < 3);
    return usTriangles[ausEdge] == UINT16_MAX && !GetEdgeCover(ausEdge);
}

// GAME - 0x690E10
bool NavMeshTriangle::HasEdgeExtraInfo() const {
    return uiFlags.uiEdgeInfo != 0;
}

// GAME - 0x68F1D0
bool NavMeshTriangle::EdgeHasExtraInfo(uint8_t aucTriangle) const {
    return uiFlags.GetBit(aucTriangle);
}

uint16_t NavMeshTriangle::GetEdgeExtraInfo(uint16_t ausTriangle) const {
    ASSUME_ASSERT(ausTriangle < 3);
    if (EdgeHasExtraInfo(ausTriangle))
        return usTriangles[ausTriangle];
    else
        return UINT16_MAX;
}

// GAME - 0x699790
uint32_t NavMeshTriangle::GetObjectCount() const {
	return uiFlags.uiObjectCount;
}

// GAME - 0x691140
bool NavMeshTriangle::GetFlag(uint32_t auiFlag) const {
    return uiFlags.Get(auiFlag);
}

// GAME - 0x691570
void NavMeshTriangle::SetFlag(uint32_t auiFlag) {
    uiFlags.Set(auiFlag);
}

// GAME - 0x693B90
bool NavMeshTriangle::IsLargeActor() const {
	return uiFlags.bLargeActor;
}

bool NavMeshTriangle::IsDisabled() const {
    return uiFlags.bDisabled;
}

// GAME - 0x693B70
bool NavMeshTriangle::IsPreferred() const {
    return uiFlags.bPreferred;
}

// GAME - 0x6A5EC0
bool NavMeshTriangle::IsWater() const {
	return uiFlags.bWater;
}

// GAME - 0x690E70
bool NavMeshTriangle::IsDoor() const {
	return uiFlags.bDoor;
}

bool NavMeshTriangle::HasCoverOrWallFlags() const {
    return uiFlags.Get(Flags::COVER_WALL_MASK);
}

// GAME - 0x691040
void NavMeshTriangle::GetEdgeCoverData(uint16_t ausEdge, uint16_t& ausCoverValue, bool& abLeft, bool& abRight) const {
    ASSUME_ASSERT(ausEdge < 2);
    const Bitfield<_CoverFlags> uiCoverFlags = uiFlags.GetEdgeCover(ausEdge);
    ausCoverValue   = uiCoverFlags.ucData;
    abLeft          = uiCoverFlags.bSideLeft;
    abRight         = uiCoverFlags.bSideRight;
}

bool NavMeshTriangle::GetEdgeSides(uint16_t ausEdge, bool& abLeft, bool& abRight) const {
    ASSUME_ASSERT(ausEdge < 2);
    const Bitfield<_CoverFlags> uiCoverFlags = uiFlags.GetEdgeCover(ausEdge);
    abLeft  = uiCoverFlags.bSideLeft;
    abRight = uiCoverFlags.bSideRight;
    return abLeft || abRight;
}

// GAME - 0x698030
uint32_t NavMeshTriangle::GetEdgeCover(uint16_t ausEdge) const {
    ASSUME_ASSERT(ausEdge < 2);
    return uiFlags.GetEdgeCover(ausEdge) & CoverFlags::DATA_MASK;
}

// GAME - 0x6AD2F0
// GECK - 0x6C6710
void NavMeshTriangle::SetEdgeCover(uint16_t ausEdge, uint16_t ausCoverValue, bool abLeft, bool abRight) {
#ifdef GAME
    ThisCall(0x6AD2F0, this, ausEdge, ausCoverValue, abLeft, abRight);
#else
    ThisCall(0x6C6710, this, ausEdge, ausCoverValue, abLeft, abRight);
#endif
}

// GAME - 0x6A5AF0
float NavMeshTriangle::GetCoverHeight(uint32_t auiVal) {
    if (auiVal > 15)
        auiVal = 15;
    return auiVal * 16.f;
}
