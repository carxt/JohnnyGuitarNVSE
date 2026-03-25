#pragma once

#include "BSExtraData.hpp"

class TESObjectCELL;

class ExtraPersistentCell : public BSExtraData {
public:
	ExtraPersistentCell();
	~ExtraPersistentCell();

	TESObjectCELL* pPersistentCell;

	BSEXTRA_TYPE(ExtraPersistentCell);
};

ASSERT_SIZE(ExtraPersistentCell, 0x10);