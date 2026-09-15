#pragma once

#include "TESForm.hpp"
#include "MagicItem.hpp"

class MagicItemForm : public TESForm, public MagicItem {
public:
};

#ifdef GAME
ASSERT_SIZE(MagicItemForm, 0x34);
#else
ASSERT_SIZE(MagicItemForm, 0x128);
#endif