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

	TESIdleForm* GetIdleAnim() const;
	void SetIdleAnim(TESIdleForm* apIdle);

	bool GetUsesIdle(TESIdleForm* apIdle) const;
};

#ifdef GAME
ASSERT_SIZE(TESObjectANIO, 0x3C);
#else
ASSERT_SIZE(TESObjectANIO, 0x60);
#endif