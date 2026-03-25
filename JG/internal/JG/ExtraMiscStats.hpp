#pragma once
#include <unordered_map>
#include <unordered_set>

namespace ExtraMiscStats {
	
	void Reset();
	void Install();
	void Update();

	bool InitStat(const char* name);
	bool ModStat(const char* name, int mod);
	int GetStat(const char* name);

	// Serialization interface
	using WriteFunc = bool (*)(const void*, uint32_t);
	using ReadFunc = uint32_t(*)(void*, uint32_t);
	bool HasDataToSave();
	void SerializeData(WriteFunc writeFunc);
	void DeserializeData(ReadFunc readFunc);
}