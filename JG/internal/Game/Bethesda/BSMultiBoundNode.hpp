#pragma once

#include "BSNiNode.hpp"
#include "BSMultiBound.hpp"

NiSmartPointer(BSMultiBoundNode);

class BSCullingProcess;
class BSOcclusionPlane;
class BSMultiBoundRoom;

class BSMultiBoundNode : public BSNiNode {
public:
	BSMultiBoundNode();
	virtual ~BSMultiBoundNode();

	virtual BSMultiBoundRoom*	GetMultiBoundRoom() const;
	virtual bool				IsPointWithin(const NiPoint3& arPoint) const;
	virtual BS_INTERSECT_RESULT	CheckBound(const BSMultiBound& arBound) const;
	virtual BS_INTERSECT_RESULT	CheckNiBound(const NiBound& arBound) const;

	BSMultiBoundPtr spMultiBound;
	BS_CULLING_TYPE	eCullingMode;

	CREATE_OBJECT(BSMultiBoundNode, 0xC46DF0);
	NIRTTI_ADDRESS(0x1202E74);
};

ASSERT_SIZE(BSMultiBoundNode, 0xB4);