#pragma once

#include "NiBinaryStream.hpp"

class NiFile : public NiBinaryStream {
public:
	virtual void		Seek(int32_t aiOffset, int32_t aiWhence);
	virtual const char*	GetFileName();
	virtual uint32_t	GetFileSize();

	struct _OpenMode {
		enum Mode {
			READ_ONLY	= 0,
			WRITE_ONLY	= 1,
			APPEND_ONLY	= 2,
		};
	};
	using OpenMode = _OpenMode::Mode;

	uint32_t	m_uiBufferAllocSize;
	uint32_t	m_uiBufferReadSize;
	uint32_t	m_uiPos;
	uint32_t	m_uiAbsolutePos;
	char*		m_pBuffer;
	union {
		HANDLE	__restrict m_hFile; // Mod Limit Fix uses Win32 handles
		FILE*	__restrict m_pFile;
	};
	OpenMode	m_eMode;
	bool		m_bGood;

	bool Flush();

	char* GetBuffer() const;

	uint32_t FileRead(void* apBuffer, uint32_t auiBytes);
	uint32_t FileWrite(const void* apBuffer, uint32_t auiBytes);

	static NiFile* GetFile(const char* apFileName, OpenMode aeMode, uint32_t auiBufferAllocSize);
};

ASSERT_SIZE(NiFile, 0x30);