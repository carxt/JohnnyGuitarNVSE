#pragma once

#include "BSExtraData.hpp"

class AlchemyItem;

class ExtraPoison : public BSExtraData {
public:
	ExtraPoison();
	~ExtraPoison();

	AlchemyItem* pPoison;

	BSEXTRA_TYPE(ExtraPoison);
};

ASSERT_SIZE(ExtraPoison, 0x10);