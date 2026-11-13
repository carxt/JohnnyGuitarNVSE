#include "BSFile.hpp"

BSFile* BSFile::Create(const char* apFileName, OpenMode aeMode, uint32_t auiBufferSize, bool abTextMode) {
#ifdef GAME
	return BSMemory::create<BSFile, 0xB00260>(apFileName, aeMode, auiBufferSize, abTextMode);
#else
	return BSMemory::create<BSFile, 0x8A1160>(apFileName, aeMode, auiBufferSize, abTextMode);
#endif
}

// GAME - 0xAFFD10
// GECK - 0x8A0BF0
void BSFile::Close() {
#ifdef GAME
    ThisCall(0xAFFD10, this);
#else
    ThisCall(0x8A0BF0, this);
#endif
}

// GAME - 0xAFF490
// GECK - 0x8A0370
void BSFile::CheckIsGood() {
#ifdef GAME
    ThisCall(0xAFF490, this);
#else
	ThisCall(0x8A0370, this);
#endif
}

// GAME - 0xAFFD80
// GECK - 0x8A0C60
bool BSFile::ChangeBufferSize(uint32_t auiSize) {
#ifdef GAME
	return ThisCall<bool>(0xAFFD80, this, auiSize);
#else
	return ThisCall<bool>(0x8A0C60, this, auiSize);
#endif
}