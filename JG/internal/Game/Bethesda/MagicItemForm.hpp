#pragma once

#include "TESForm.hpp"
#include "MagicItem.hpp"

class MagicItemForm : public TESForm, public MagicItem {
public:
};

ASSERT_SIZE(MagicItemForm, 0x34);