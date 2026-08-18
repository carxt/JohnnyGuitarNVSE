#pragma once

#include "Gamebryo/NiTPointerList.hpp"
#include "BSMultiBoundNode.hpp"
#include "BSSimpleArray.hpp"

class BSPortal;
class ShadowSceneLight;
class BSCompoundFrustum;
class BSOcclusionPlane;

NiSmartPointer(BSMultiBoundRoom);

class BSMultiBoundRoom : public BSMultiBoundNode {
public:
	BSMultiBoundRoom();
	virtual ~BSMultiBoundRoom();

	NiTPointerList<BSPortal*>			kPortals;
	NiTPointerList<BSOcclusionPlane*>	kOccluders;
	BSCompoundFrustum*					pFrustum;
	NiTPointerList<BSMultiBound*>		kJoinedMultiBounds;
	BSSimpleArray<ShadowSceneLight*>	kLights;

	NIRTTI_ADDRESS(0x1202828);
};

ASSERT_SIZE(BSMultiBoundRoom, 0xEC);
