#pragma once

class TESWorldSpace;
class TESObjectLAND;

namespace LandRemapping {

	void Install();

	void Reset();

	void __fastcall RemapLand(uint32_t auiLandFormID, const TESWorldSpace* apWorld, int16_t asX, int16_t asY);

	void __fastcall ReloadModel(TESObjectLAND* apLand, bool abLoad);

	bool HasDataToSave();

	using WriteFunc = bool (*)(const void*, uint32_t);
	using ReadFunc = uint32_t(*)(void*, uint32_t);

	void __fastcall SerializeData(WriteFunc writeFunc);
	void __fastcall DeserializeData(ReadFunc readFunc);

}