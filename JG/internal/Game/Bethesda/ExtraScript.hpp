#pragma once

#include "BSExtraData.hpp"

class Script;
class ScriptLocals;
class TESObjectREFR;

class ExtraScript : public BSExtraData {
public:
	ExtraScript();
	~ExtraScript();

	Script*			pScript;
	ScriptLocals*	pLocals;

	BSEXTRA_TYPE(ExtraScript);
};

ASSERT_SIZE(ExtraScript, 0x14);