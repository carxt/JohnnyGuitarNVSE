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

class MD5 {
	struct MD5_CTX {
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

	MD5() { MD5Init(); }
};

#endif