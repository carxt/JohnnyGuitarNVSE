#pragma once

#include "BSExtraData.hpp"
#include "SeenData.hpp"

class ExtraSeenData : public BSExtraData {
public:
	ExtraSeenData();
	~ExtraSeenData();

	SeenData* pSeenData;

	BSEXTRA_TYPE(ExtraSeenData);
};

ASSERT_SIZE(ExtraSeenData, 0x10);