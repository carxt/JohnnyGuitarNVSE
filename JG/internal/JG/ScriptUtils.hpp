#pragma once

class NiAVObject;
class TESForm;
class TESObject;
class TESObjectREFR;
class TESObjectCELL;
class TESWorldSpace;
class NiDefaultAVObjectPalette;
class BGSLoadGameSubBuffer;
class Animation;
class NiPoint3;

namespace ScriptUtils {

	template<typename T>
		requires (T::NONE < T::COUNT)
	inline bool __fastcall InRange(volatile T value) {
		return value > T::NONE && value < T::COUNT;
	}

	inline bool __fastcall IsWildcard(const char* text) {
		return text[0] == '*' && text[1] == 0;
	}

	class AutoSaveFormChanges {
		bool bOrgVal;
	public:
		AutoSaveFormChanges(bool abAllow) noexcept;
		~AutoSaveFormChanges() noexcept;
	};


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

	SPEC_NOINLINE void __fastcall MoveRefTo(TESObjectREFR* apRef, const NiPoint3& arPos, const NiPoint3& arRot, TESObjectREFR* apTarget = nullptr, TESObjectCELL* apCell = nullptr, TESWorldSpace* apWorld = nullptr);

	void __fastcall UpdateReference3D(TESObjectREFR* apReference);

	TESObject* __fastcall GetTESObject(const TESForm* apForm);
}

namespace ScriptUtils {

	void InitData();

}