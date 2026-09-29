#pragma once

#include "TileRect.hpp"

class Menu;

class TileMenu : public TileRect {
public:
	Menu* pMenu;
};

ASSERT_SIZE(TileMenu, 0x40);