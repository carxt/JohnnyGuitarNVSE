#pragma once

#include "BSExtraData.hpp"
#include "BSSimpleList.hpp"
#include "RefActivateData.hpp"

class ExtraActivateRefChildren : public BSExtraData {
public:
	ExtraActivateRefChildren();
	~ExtraActivateRefChildren();

	BSSimpleList<RefActivateData*>	kChildren;
	float							fActivateTimer;

	BSEXTRA_TYPE(ExtraActivateRefChildren);
};

ASSERT_SIZE(ExtraActivateRefChildren, 0x18);