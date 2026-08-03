#pragma once

#include "Gamebryo/NiFile.hpp"
#include "BSStringT.hpp"

class BSFile : public NiFile {
public:
	virtual bool		Open(bool abWaitForOpen = false, bool abTextMode = false);
	virtual bool		OpenByFilePointer(FILE* apFile); // HANDLE if Mod Limit Fix is present
	virtual uint32_t	GetSize();
	virtual uint32_t	ReadString(BSString& arString, uint32_t auiMaxLength);
	virtual uint32_t	ReadStringAlt(BSString& arString, uint32_t auiMaxLength);
	virtual uint32_t	GetLine(char* apBuffer, uint32_t auiMaxBytes, wchar_t awcMark);
	virtual uint32_t	WriteString(const BSString& arString, bool abBinary);
	virtual uint32_t	WriteStringWide(const BSWideString& arString, bool abBinary);
	virtual bool		IsReadable();
	virtual uint32_t	ReadF(void* apBuffer, uint32_t auiBytes);
	virtual uint32_t	WriteF(const void* apBuffer, uint32_t auiBytes);

	bool		bUseAuxBuffer;
	char*		pAuxBuffer;
	int32_t		iAuxTrueFilePos;
	uint32_t	uiAuxBufferMinIndex;
	uint32_t	uiAuxBufferMaxIndex;
	char		cFileName[260];
	uint32_t	uiResult;
	uint32_t	uiIOSize;
	uint32_t	uiTrueFilePos;
	uint32_t	uiFileSize;

	[[nodiscard]] static BSFile* Create(const char* apFileName, OpenMode aeMode, uint32_t auiBufferSize, bool abTextMode);

	void Close();

	void CheckIsGood();

	bool ChangeBufferSize(uint32_t auiSize);

	// Based on GAME - 0x6FC920, 0x6FC950
	template<class T>
	BSFile& operator>>(T& arVal) {
		uiResult = Read(&arVal, sizeof(T));
		return *this;
	}

	template<class T>
	BSFile& operator<<(const T& arVal) {
		uiResult = Write(&arVal, sizeof(T));
		return *this;
	}
};

ASSERT_SIZE(BSFile, 0x158);