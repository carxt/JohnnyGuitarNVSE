#include "NiFile.hpp"

// GAME - 0xAA15A0
// GECK - 0x851F00
bool NiFile::Flush() {
#ifdef GAME
	return ThisCall<bool>(0xAA15A0, this);
#else
	return ThisCall<bool>(0x851F00, this);
#endif
}

// GAME - 0xAA1AC0
char* NiFile::GetBuffer() const {
	return m_pBuffer;
}

// GAME - 0xAA1750
// GECK - 0x8520B0
uint32_t NiFile::FileRead(void* apBuffer, uint32_t auiBytes) {
#ifdef GAME
	return ThisCall<uint32_t>(0xAA1750, this, apBuffer, auiBytes);
#else
	return ThisCall<uint32_t>(0x8520B0, this, apBuffer, auiBytes);
#endif
}

// GAME - 0xAA1810
// GECK - 0x852170
uint32_t NiFile::FileWrite(const void* apBuffer, uint32_t auiBytes) {
#ifdef GAME
	return ThisCall<uint32_t>(0xAA1810, this, apBuffer, auiBytes);
#else
	return ThisCall<uint32_t>(0x852170, this, apBuffer, auiBytes);
#endif
}

// GAME - 0xAA1A20
// GECK - 0x8528E0
NiFile* NiFile::GetFile(const char* apFileName, OpenMode aeMode, uint32_t auiBufferAllocSize) {
#ifdef GAME
	return CdeclCall<NiFile*>(0xAA1A20, apFileName, aeMode, auiBufferAllocSize);
#else
	return CdeclCall<NiFile*>(0xAA1A20, apFileName, aeMode, auiBufferAllocSize);
#endif
}