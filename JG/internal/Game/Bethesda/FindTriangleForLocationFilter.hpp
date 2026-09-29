#pragma once

class NavMesh;
class NiPoint3;

class FindTriangleForLocationFilter {
public:
	virtual bool IsValidTri(const NiPoint3& arLocation, NavMesh* apNavMesh, uint16_t ausTriangle, const NiPoint3& arLocationDiff) const;
};

ASSERT_SIZE(FindTriangleForLocationFilter, 0x4);