#pragma once

#include "MobileObjectTaskletData.hpp"

// Unused
class PackageUpdateTaskData : public MobileObjectTaskletData {
public:
	BSSimpleList<MobileObject*>*	pPrevObjectList;
	uint32_t						uiUpdatedCount;
	uint32_t						uiSkippedCount;
};

ASSERT_SIZE(PackageUpdateTaskData, 0x44);