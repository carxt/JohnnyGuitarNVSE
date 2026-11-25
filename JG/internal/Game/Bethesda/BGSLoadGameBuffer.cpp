#include "BGSLoadGameBuffer.hpp"

// GAME - 0x864740
int32_t BGSLoadGameBuffer::Load(BGSSaveLoadFile* apFile) {
	return ThisCall<int32_t>(0x864740, this, apFile);
}

// GAME - 0x864980
void BGSLoadGameBuffer::LoadData(char* apData, uint32_t auiSize) {
	ThisCall(0x864980, this, apData, auiSize);
}

// GAME - 0x8649A0
char* BGSLoadGameBuffer::LoadString(char* apText) {
	return ThisCall<char*>(0x8649A0, this, apText);
}
