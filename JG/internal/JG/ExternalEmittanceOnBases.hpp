#pragma once

class TESForm;
class TESBoundObject;

namespace ExternalEmittanceOnBases {

	void Install();

	TESForm* __fastcall GetExternalEmittanceSource(const TESBoundObject* apObject);
	void __fastcall SetExternalEmittanceSource(TESBoundObject* apObject, TESForm* apSource);

}