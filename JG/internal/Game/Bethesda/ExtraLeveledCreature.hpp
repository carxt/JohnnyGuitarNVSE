#pragma once

#include "BSExtraData.hpp"

class TESForm;

class ExtraLeveledCreature : public BSExtraData {
public:
    ExtraLeveledCreature();
    ~ExtraLeveledCreature();

  	TESActorBase *pOriginalBase;
  	TESActorBase *pTemplate;

	BSEXTRA_TYPE(ExtraLeveledCreature);
};

ASSERT_SIZE(ExtraLeveledCreature, 0x14);