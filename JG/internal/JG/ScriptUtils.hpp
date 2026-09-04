#pragma once

class NiAVObject;
class TESObjectREFR;
class NiDefaultAVObjectPalette;
class BGSLoadGameSubBuffer;
class Animation;

namespace ScriptUtils {

	template<typename T>
		requires (T::NONE < T::COUNT)
	inline bool __fastcall InRange(volatile T value) {
		return value > T::NONE && value < T::COUNT;
	}

	SPEC_NOINLINE NiAVObject* __fastcall GetReferenceScene(TESObjectREFR* apRef, bool abFirstPerson);

	void RecurseAndAddObjectsToPalette(NiAVObject* apObject, NiDefaultAVObjectPalette* apPalette);

	void RecurseAndRemoveObjectsFromPalette(NiAVObject* apObject, NiDefaultAVObjectPalette* apPalette);

	NiDefaultAVObjectPalette* __fastcall GetObjectPalette(const NiAVObject* apRoot);

	SPEC_NOINLINE void __fastcall RecurseAddObjectsToPalette(NiAVObject* apRoot, NiAVObject* apObject);

	SPEC_NOINLINE void __fastcall RecurseRemoveObjectsFromPalette(NiAVObject* apRoot, NiAVObject* apObject);

	SPEC_NOINLINE void __fastcall AddObjectToPalette(NiAVObject* apRoot, NiAVObject* apObject);

	SPEC_NOINLINE void __fastcall RemoveObjectFromPalette(NiAVObject* apRoot, NiAVObject* apObject);

	SPEC_NOINLINE void __fastcall SaveAnimation(BGSLoadGameSubBuffer& arBuffer, TESObjectREFR* apReference, Animation* apAnimation);

	SPEC_NOINLINE void __fastcall LoadAnimation(BGSLoadGameSubBuffer& arBuffer, TESObjectREFR* apReference, Animation* apAnimation);

}