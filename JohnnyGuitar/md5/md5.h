/*
	This is the C++ implementation of the MD5 Message-Digest
	Algorithm desrcipted in RFC 1321.
	I translated the C code from this RFC to C++.
	There is now warranty.

	Feb. 12. 2005
	Benjamin Grüdelbach
*/

/*
	Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
	rights reserved.

	License to copy and use this software is granted provided that it
	is identified as the "RSA Data Security, Inc. MD5 Message-Digest
	Algorithm" in all material mentioning or referencing this software
	or this function.

	License is also granted to make and use derivative works provided
	that such works are identified as "derived from the RSA Data
	Security, Inc. MD5 Message-Digest Algorithm" in all material
	mentioning or referencing the derived work.

	RSA Data Security, Inc. makes no representations concerning either
	the merchantability of this software or the suitability of this
	software for any particular purpose. It is provided "as is"
	without express or implied warranty of any kind.

	These notices must be retained in any copies of any part of this
	documentation and/or software.
*/

//---------------------------------------------------------------------- 
#ifndef MD5_H
#define MD5_H

class MD5
{
	struct MD5_CTX
	{
		DWORD	state[4];		// State (ABCD)
		DWORD	count[2];		// Number of bits, modulo 2^64 (lsb first)
		BYTE	buffer[64];		// Input buffer
	}
	context;

	void MD5Transform(DWORD state[4], BYTE block[64]);
	void Encode(BYTE*, DWORD*, DWORD);
	void Decode(DWORD*, BYTE*, DWORD);
	void MD5_memcpy(BYTE*, BYTE*, DWORD);

public:
	void MD5Init();
	void MD5Update(BYTE*, DWORD);
	void MD5Final(BYTE[16]);

	static void GetMD5File(const char *filePath, char *outHash);
	MD5() {MD5Init();}
};



class FileStream
{
protected:
	HANDLE		theFile;
	UInt32		streamLength;
	UInt32		streamOffset;

public:
	FileStream() : theFile(INVALID_HANDLE_VALUE) {}
	~FileStream() { if (Good()) Close(); }

	bool Good() const { return theFile != INVALID_HANDLE_VALUE; }
	HANDLE GetHandle() const { return theFile; }
	UInt32 GetLength() const { return streamLength; }
	UInt32 GetOffset() const { return streamOffset; }
	bool HitEOF() const { return streamOffset >= streamLength; }

	bool Open(const char *filePath);
	bool OpenAt(const char *filePath, UInt32 inOffset);
	bool OpenWrite(const char *filePath);
	bool Create(const char *filePath, UInt32 attr = FILE_ATTRIBUTE_NORMAL);
	bool OpenWriteEx(char *filePath, bool append);
	void SetOffset(UInt32 inOffset);
	void Close()
	{
		CloseHandle(theFile);
		theFile = INVALID_HANDLE_VALUE;
	}

	void ReadBuf(void *outData, UInt32 inLength);
	void WriteBuf(const void *inData, UInt32 inLength);

	static void MakeAllDirs(char *fullPath);
};
#endif