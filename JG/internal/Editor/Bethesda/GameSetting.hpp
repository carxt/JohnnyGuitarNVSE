#pragma once

#include "Bethesda/Setting.hpp"
#include "Bethesda/TESFormIDListView.hpp"

class GameSetting : public Setting, public TESFormIDListView {
public:
	TESFORM_TYPE(GameSetting);
};

ASSERT_SIZE(GameSetting, 0x38);