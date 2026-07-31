#pragma once

class NiAVObject;
class TESObjectREFR;

namespace ScriptUtils {

	template<typename T>
		requires (T::NONE < T::COUNT)
	inline bool __fastcall InRange(volatile T value) {
		return value > T::NONE && value < T::COUNT;
	}

	SPEC_NOINLINE NiAVObject* __fastcall GetReferenceScene(TESObjectREFR* apRef, bool abFirstPerson);

}