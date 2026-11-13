#pragma once

#include "BSMultiBoundShape.hpp"

NiSmartPointer(BSMultiBound);

class BSMultiBound : public NiObject {
public:
	BSMultiBound();
	~BSMultiBound();

	virtual bool GetPointWithin(const NiPoint3& arPoint);
	virtual void SetCenter(const NiPoint3& arCenter);

	uint32_t				uiBoundFrameCount;
	BSMultiBoundShapePtr	spShape;

	CREATE_OBJECT(BSMultiBound, 0xC361A0);
	NIRTTI_ADDRESS(0x1202810);
};

ASSERT_SIZE(BSMultiBound, 0x10)