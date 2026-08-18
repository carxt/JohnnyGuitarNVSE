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
	virtual bool				GetPointWithin(const NiPoint3& arPoint) const;
	virtual uint32_t			CheckBound(const BSMultiBound& arBound) const;
	virtual uint32_t			CheckBoundAlt(const NiBound& arBound) const;

	BSMultiBoundPtr spMultiBound;
	BS_CULLING_TYPE	eCullingMode;

	CREATE_OBJECT(BSMultiBoundNode, 0xC46DF0);
	NIRTTI_ADDRESS(0x1202E74);
};

ASSERT_SIZE(BSMultiBoundNode, 0xB4);