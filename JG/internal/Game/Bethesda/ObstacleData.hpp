#pragma once

#include "BSSimpleArray.hpp"
#include "Gamebryo/NiRefObject.hpp"
#include "Gamebryo/NiMatrix3.hpp"

class NavMeshInfo;
class ReferenceObstacleArray;
class bhkRigidBody;
class NiAVObject;

class ObstacleData : public NiRefObject {
public:
	ReferenceObstacleArray*				pParentArray;
	NiPointer<bhkRigidBody>				spRigidBody;
	NiPoint3							kCenter;
	NiMatrix3							kOrientation;
	NiPoint3							kBoxMin;
	NiPoint3							kBoxMax;
	NiPoint3							kAABBMin;
	NiPoint3							kAABBMax;
	uint32_t							uiLastUpdateTime;
	bool								bActive;
	BSSimpleArray<NavMeshInfo*>			kNavMeshInfos;
	NiPointer<NiAVObject>				sp3D;
};

ASSERT_SIZE(ObstacleData, 0x8C);