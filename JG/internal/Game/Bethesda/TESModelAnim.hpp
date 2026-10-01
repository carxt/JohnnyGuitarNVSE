#pragma once

#include "TESModel.hpp"

class TESModelAnim : public TESModel {
public:
	TESModelAnim();
	~TESModelAnim();

#ifdef EDITOR
	BSString strUnk24;
#endif
};

#ifdef GAME
ASSERT_SIZE(TESModelAnim, sizeof(TESModel));
#else
ASSERT_SIZE(TESModelAnim, 0x2C);
#endif