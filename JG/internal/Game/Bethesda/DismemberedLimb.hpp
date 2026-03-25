#pragma once

#include "BSSimpleArray.hpp"

class TESBoundObject;

class DismemberedLimb {
public:
	uint8_t							ucLimb;
	bool							bLimbExploded;
	bool							bObjectArrayIdentical;
	bool							bLimbRemoved;
	BSSimpleArray<TESBoundObject*>	kObjects;
};

ASSERT_SIZE(DismemberedLimb, 0x14);