#pragma once

#include "TESForm.hpp"
#include "TESModelTextureSwap.hpp"

class TESIdleForm;

class TESObjectANIO : public TESForm, public TESModelTextureSwap {
public:
	TESObjectANIO();
	~TESObjectANIO();

	TESIdleForm* pIdleAnim;

	TESFORM_TYPE(TESObjectANIO);
};

ASSERT_SIZE(TESObjectANIO, 0x3C);