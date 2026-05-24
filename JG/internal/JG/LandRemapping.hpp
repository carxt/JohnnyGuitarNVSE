#pragma once

class TESWorldSpace;
class TESObjectLAND;

namespace LandRemapping {
	void Install();
	void Reset();
	void RemapLand(uint32_t auiLandFormID, TESWorldSpace* apWorld, int16_t asX, int16_t asY);
	void ReloadModel(TESObjectLAND* apLand, bool abLoad);

	using WriteFunc = bool (*)(const void*, uint32_t);
	using ReadFunc = uint32_t(*)(void*, uint32_t);
	bool HasDataToSave();
	void SerializeData(WriteFunc writeFunc);
	void DeserializeData(ReadFunc readFunc);
}