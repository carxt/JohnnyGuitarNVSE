#include "NiBinaryStream.hpp"

// GAME - 0x462D80
// GECK - 0x401210
uint32_t NiBinaryStream::Read(void* apBuffer, uint32_t auiBytes) {
	uint32_t uiSize = 1;
	uint32_t uiBytesRead = BinaryRead(apBuffer, auiBytes, &uiSize, 1);
	return uiBytesRead;
}

// GAME - 0x473180
uint32_t NiBinaryStream::Write(const void* apBuffer, uint32_t auiBytes) {
	uint32_t uiSize = 1;
	uint32_t uiBytesWritten = BinaryWrite(apBuffer, auiBytes, &uiSize, 1);
	return uiBytesWritten;
}

// GAME - 0x462DC0
uint32_t NiBinaryStream::BinaryRead(void* apBuffer, uint32_t auiTotalBytes, uint32_t* apComponentSizes, uint32_t auiComponentCount) {
	uint32_t uiBytesRead = m_pfnRead(this, apBuffer, auiTotalBytes, apComponentSizes, auiComponentCount);
	m_uiAbsoluteCurrentPos += uiBytesRead;
	return uiBytesRead;
}

// GAME - 0x44E120
uint32_t NiBinaryStream::BinaryWrite(const void* apBuffer, uint32_t auiTotalBytes, uint32_t* apComponentSizes, uint32_t auiComponentCount) {
	uint32_t uiBytesWritten = m_pfnWrite(this, apBuffer, auiTotalBytes, apComponentSizes, auiComponentCount);
	m_uiAbsoluteCurrentPos += uiBytesWritten;
	return uiBytesWritten;
}

// GAME - 0xAA1DE0
// GECK - 0x852C90
void NiBinaryStream::DoByteSwap(void* apData, uint32_t auiBytes, uint32_t* apComponentSizes, uint32_t auiComponentCount) {
#ifdef GAME
    CdeclCall(0xAA1DE0, apData, auiBytes, apComponentSizes, auiComponentCount);
#else
	CdeclCall(0x852C90, apData, auiBytes, apComponentSizes, auiComponentCount);
#endif
}
