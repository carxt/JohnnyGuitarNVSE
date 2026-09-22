#pragma once

#include "Bethesda/ItemChange.hpp"
#include "Bethesda/ContainerObject.hpp"

class TESContainer;

// The cooler Daniel
class FastInventoryIterator {
public:
	struct _Stage {
		enum Stage {
			ONE = 0,
			TWO = 1,
		};
	};
	using Stage = _Stage::Stage;

	BSSimpleList<ContainerObject*>* pOriginalList;
	BSSimpleList<ContainerObject*>* pList;
	int32_t							iNumber;
	ItemChange*						pReturnitem;
	TESContainer*					pContainer;
	BSSimpleList<ItemChange*>*		pFirst;
	Stage							eStage;
	BSSimpleList<ExtraDataList*>*	pStageOneExtraList;
	BSSimpleList<ExtraDataList*>*	pStageTwoFirst;
	BSSimpleList<ExtraDataList*>*	pStageTwoExtraList;
};

ASSERT_SIZE(FastInventoryIterator, 0x28);