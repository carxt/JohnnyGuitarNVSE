#pragma once

class TESForm;

namespace NPCAccuracy {

	void Install();
	void Reset();	

	SPEC_NOINLINE void  __fastcall SetMultiplier(const TESForm* apForm, float afMultiplier);
	SPEC_NOINLINE float __fastcall GetMultiplier(const TESForm* apForm);
	SPEC_NOINLINE void  __fastcall RemoveMultiplier(const TESForm* apForm);

};