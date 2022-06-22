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

#include "md5.h"

//	Constants for MD5Transform routine.
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

static BYTE PADDING[64] =
{
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

//	F, G, H and I are basic MD5 functions.
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

//	ROTATE_LEFT rotates x left n bits.
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/*
	FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
	Rotation is separate from addition to prevent recomputation.
*/
#define FF(a, b, c, d, x, s, ac) { \
	(a) += F ((b), (c), (d)) + (x) + (DWORD)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}
#define GG(a, b, c, d, x, s, ac) { \
	(a) += G ((b), (c), (d)) + (x) + (DWORD)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}
#define HH(a, b, c, d, x, s, ac) { \
	(a) += H ((b), (c), (d)) + (x) + (DWORD)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}
#define II(a, b, c, d, x, s, ac) { \
	(a) += I ((b), (c), (d)) + (x) + (DWORD)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}

//	MD5 initialization. Begins an MD5 operation, writing a new context.
void MD5::MD5Init() {
	context.count[0] = context.count[1] = 0;
	context.state[0] = 0x67452301;
	context.state[1] = 0xEFCDAB89;
	context.state[2] = 0x98BADCFE;
	context.state[3] = 0x10325476;
}

/*
	 MD5 block update operation. Continues an MD5 message-digest
	 operation, processing another message block, and updating the
	 context.
*/
void MD5::MD5Update(BYTE* input, DWORD inputLen) {
	// Compute number of bytes mod 64
	DWORD index = (DWORD)((context.count[0] >> 3) & 0x3F);

	// Update number of bits
	if ((context.count[0] += ((DWORD)inputLen << 3)) < ((DWORD)inputLen << 3))
		context.count[1]++;

	context.count[1] += ((DWORD)inputLen >> 29);
	DWORD partLen = 64 - index;

	// Transform as many times as possible
	DWORD i = 0;
	if (inputLen >= partLen) {
		MD5_memcpy((BYTE*)&context.buffer[index], (BYTE*)input, partLen);
		MD5Transform(context.state, context.buffer);
		for (i = partLen; i + 63 < inputLen; i += 64)
			MD5Transform(context.state, &input[i]);
		index = 0;
	}

	// Buffer remaining input
	MD5_memcpy((BYTE*)&context.buffer[index], (BYTE*)&input[i], inputLen - i);
}

//	MD5 finalization. Ends an MD5 message-digest operation, writing the the message digest and zeroizing the context.
void MD5::MD5Final(BYTE digest[16]) {
	BYTE bits[8];

	// Save number of bits
	Encode(bits, context.count, 8);

	// Pad out to 56 mod 64
	DWORD index = (DWORD)((context.count[0] >> 3) & 0x3F);
	DWORD padLen = (index < 56) ? (56 - index) : (120 - index);
	MD5Update(PADDING, padLen);

	// Append length (before padding)
	MD5Update(bits, 8);

	// Store state in digest
	Encode(digest, context.state, 16);
}

//	MD5 basic transformation. Transforms state based on block.
void MD5::MD5Transform(DWORD state[4], BYTE block[64]) {
	DWORD A = state[0], B = state[1], C = state[2], D = state[3], x[16];

	Decode(x, block, 64);

	// Round 1
	FF(A, B, C, D, x[0], S11, 0xD76AA478);
	FF(D, A, B, C, x[1], S12, 0xE8C7B756);
	FF(C, D, A, B, x[2], S13, 0x242070DB);
	FF(B, C, D, A, x[3], S14, 0xC1BDCEEE);
	FF(A, B, C, D, x[4], S11, 0xF57C0FAF);
	FF(D, A, B, C, x[5], S12, 0x4787C62A);
	FF(C, D, A, B, x[6], S13, 0xA8304613);
	FF(B, C, D, A, x[7], S14, 0xFD469501);
	FF(A, B, C, D, x[8], S11, 0x698098D8);
	FF(D, A, B, C, x[9], S12, 0x8B44F7AF);
	FF(C, D, A, B, x[10], S13, 0xFFFF5BB1);
	FF(B, C, D, A, x[11], S14, 0x895CD7BE);
	FF(A, B, C, D, x[12], S11, 0x6B901122);
	FF(D, A, B, C, x[13], S12, 0xFD987193);
	FF(C, D, A, B, x[14], S13, 0xA679438E);
	FF(B, C, D, A, x[15], S14, 0x49B40821);

	// Round 2
	GG(A, B, C, D, x[1], S21, 0xF61E2562);
	GG(D, A, B, C, x[6], S22, 0xC040B340);
	GG(C, D, A, B, x[11], S23, 0x265E5A51);
	GG(B, C, D, A, x[0], S24, 0xE9B6C7AA);
	GG(A, B, C, D, x[5], S21, 0xD62F105D);
	GG(D, A, B, C, x[10], S22, 0x02441453);
	GG(C, D, A, B, x[15], S23, 0xD8A1E681);
	GG(B, C, D, A, x[4], S24, 0xE7D3FBC8);
	GG(A, B, C, D, x[9], S21, 0x21E1CDE6);
	GG(D, A, B, C, x[14], S22, 0xC33707D6);
	GG(C, D, A, B, x[3], S23, 0xF4D50D87);
	GG(B, C, D, A, x[8], S24, 0x455A14ED);
	GG(A, B, C, D, x[13], S21, 0xA9E3E905);
	GG(D, A, B, C, x[2], S22, 0xFCEFA3F8);
	GG(C, D, A, B, x[7], S23, 0x676F02D9);
	GG(B, C, D, A, x[12], S24, 0x8D2A4C8A);

	// Round 3
	HH(A, B, C, D, x[5], S31, 0xFFFA3942);
	HH(D, A, B, C, x[8], S32, 0x8771F681);
	HH(C, D, A, B, x[11], S33, 0x6D9D6122);
	HH(B, C, D, A, x[14], S34, 0xFDE5380C);
	HH(A, B, C, D, x[1], S31, 0xA4BEEA44);
	HH(D, A, B, C, x[4], S32, 0x4BDECFA9);
	HH(C, D, A, B, x[7], S33, 0xF6BB4B60);
	HH(B, C, D, A, x[10], S34, 0xBEBFBC70);
	HH(A, B, C, D, x[13], S31, 0x289B7EC6);
	HH(D, A, B, C, x[0], S32, 0xEAA127FA);
	HH(C, D, A, B, x[3], S33, 0xD4EF3085);
	HH(B, C, D, A, x[6], S34, 0x04881D05);
	HH(A, B, C, D, x[9], S31, 0xD9D4D039);
	HH(D, A, B, C, x[12], S32, 0xE6DB99E5);
	HH(C, D, A, B, x[15], S33, 0x1FA27CF8);
	HH(B, C, D, A, x[2], S34, 0xC4AC5665);

	// Round 4
	II(A, B, C, D, x[0], S41, 0xF4292244);
	II(D, A, B, C, x[7], S42, 0x432AFF97);
	II(C, D, A, B, x[14], S43, 0xAB9423A7);
	II(B, C, D, A, x[5], S44, 0xFC93A039);
	II(A, B, C, D, x[12], S41, 0x655B59C3);
	II(D, A, B, C, x[3], S42, 0x8F0CCC92);
	II(C, D, A, B, x[10], S43, 0xFFEFF47D);
	II(B, C, D, A, x[1], S44, 0x85845DD1);
	II(A, B, C, D, x[8], S41, 0x6FA87E4F);
	II(D, A, B, C, x[15], S42, 0xFE2CE6E0);
	II(C, D, A, B, x[6], S43, 0xA3014314);
	II(B, C, D, A, x[13], S44, 0x4E0811A1);
	II(A, B, C, D, x[4], S41, 0xF7537E82);
	II(D, A, B, C, x[11], S42, 0xBD3AF235);
	II(C, D, A, B, x[2], S43, 0x2AD7D2BB);
	II(B, C, D, A, x[9], S44, 0xEB86D391);

	state[0] += A;
	state[1] += B;
	state[2] += C;
	state[3] += D;
}

//	Encodes input (unsigned long int) into output (unsigned char). Assumes len is a multiple of 4.
void MD5::Encode(BYTE* output, DWORD* input, DWORD len) {
	for (DWORD i = 0, j = 0; j < len; i++, j += 4) {
		output[j] = (BYTE)(input[i] & 0xff);
		output[j + 1] = (BYTE)((input[i] >> 8) & 0xFF);
		output[j + 2] = (BYTE)((input[i] >> 16) & 0xFF);
		output[j + 3] = (BYTE)((input[i] >> 24) & 0xFF);
	}
}

//	Decodes input (unsigned char) into output (unsigned long int). Assumes len is a multiple of 4.
void MD5::Decode(DWORD* output, BYTE* input, DWORD len) {
	for (DWORD i = 0, j = 0; j < len; i++, j += 4)
		output[i] = ((DWORD)input[j]) | (((DWORD)input[j + 1]) << 8) | (((DWORD)input[j + 2]) << 16) | (((DWORD)input[j + 3]) << 24);
}

//	Note: Replace "for loop" with standard memcpy if possible.
void MD5::MD5_memcpy(BYTE* output, BYTE* input, DWORD len) {
	for (DWORD i = 0; i < len; i++)
		output[i] = input[i];
}