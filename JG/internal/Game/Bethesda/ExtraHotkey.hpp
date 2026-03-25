#pragma once

#include "BSExtraData.hpp"

class ExtraHotkey : public BSExtraData {
public:
	ExtraHotkey();
	~ExtraHotkey();

	uint8_t	ucIndex;

	BSEXTRA_TYPE(ExtraHotkey);
};

ASSERT_SIZE(ExtraHotkey, 0x10);