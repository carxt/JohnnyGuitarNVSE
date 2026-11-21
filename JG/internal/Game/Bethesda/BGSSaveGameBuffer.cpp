#include "BGSSaveGameBuffer.hpp"

// GAME - 0x865E50
void BGSSaveGameBuffer::SaveData(const void* apData, uint32_t auiSize, uint32_t unused) {
	ThisCall(0x865E50, this, apData, auiSize, unused);
}

// GAME - 0x865E70
void BGSSaveGameBuffer::SaveString(const char* apData, uint32_t auiSize) {
	ThisCall(0x865E70, this, apData, auiSize);
}

// GAME - 0x865C40
void BGSSaveGameBuffer::Save(BGSSaveLoadFile* apFile) {
	ThisCall(0x865C40, this, apFile);
}
