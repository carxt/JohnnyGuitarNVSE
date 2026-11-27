#pragma once

#include <nvse/FormExtraData.hpp>

class JGExtraEmittanceSource : public NVSE::FormExtraData {
public:
	NVSE_FED_DEFAULTS(JGExtraEmittanceSource);

	TESForm* pSource = nullptr;

	TESForm* __fastcall GetExternalEmittanceSource() const { return pSource; }
	void __fastcall SetExternalEmittanceSource(TESForm* apSource) { pSource = apSource; };
};