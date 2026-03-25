#pragma once

#include "BSExtraData.hpp"
#include "BSSimpleList.hpp"
#include "FactionRank.hpp"

class ExtraFactionChanges : public BSExtraData {
public:
	ExtraFactionChanges();
	~ExtraFactionChanges();

	BSSimpleList<FactionRank*>* pFactionChanges;

	BSEXTRA_TYPE(ExtraFactionChanges);
};

ASSERT_SIZE(ExtraFactionChanges, 0x10);