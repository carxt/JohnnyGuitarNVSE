#pragma once

#include "MobileObjectTaskletData.hpp"

// Unused
class ActorsScriptTaskData : public MobileObjectTaskletData {
public:
	BSSimpleList<MobileObject*>*	pPrevObjectList;
	uint32_t						uiRunCount;
};

ASSERT_SIZE(ActorsScriptTaskData, 0x40);