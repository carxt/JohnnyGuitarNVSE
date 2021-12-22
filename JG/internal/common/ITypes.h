#pragma once

#pragma warning(disable: 4221)
#include <cmath>

typedef unsigned char		UInt8;		//!< An unsigned 8-bit integer value
typedef unsigned short		UInt16;		//!< An unsigned 16-bit integer value
typedef unsigned long		UInt32;		//!< An unsigned 32-bit integer value
typedef unsigned long long	UInt64;		//!< An unsigned 64-bit integer value
typedef signed char			SInt8;		//!< A signed 8-bit integer value
typedef signed short		SInt16;		//!< A signed 16-bit integer value
typedef signed long			SInt32;		//!< A signed 32-bit integer value
typedef signed long long	SInt64;		//!< A signed 64-bit integer value
typedef float				Float32;	//!< A 32-bit floating point value
typedef double				Float64;	//!< A 64-bit floating point value

inline UInt32 Extend16(UInt32 in)
{
	return (in & 0x8000) ? (0xFFFF0000 | in) : in;
}

inline UInt32 Extend8(UInt32 in)
{
	return (in & 0x80) ? (0xFFFFFF00 | in) : in;
}

inline UInt16 Swap16(UInt16 in)
{
	return	((in >> 8) & 0x00FF) |
			((in << 8) & 0xFF00);
}

inline UInt32 Swap32(UInt32 in)
{
	return	((in >> 24) & 0x000000FF) |
			((in >>  8) & 0x0000FF00) |
			((in <<  8) & 0x00FF0000) |
			((in << 24) & 0xFF000000);
}

inline UInt64 Swap64(UInt64 in)
{
	UInt64	temp;

	temp = Swap32(in);
	temp <<= 32;
	temp |= Swap32(in >> 32);

	return temp;
}

inline void SwapFloat(float * in)
{
	UInt32	* temp = (UInt32 *)in;

	*temp = Swap32(*temp);
}

inline void SwapDouble(double * in)
{
	UInt64	* temp = (UInt64 *)in;

	*temp = Swap64(*temp);
}

inline bool IsBigEndian(void)
{
	union
	{
		UInt16	u16;
		UInt8	u8[2];
	} temp;

	temp.u16 = 0x1234;
	
	return temp.u8[0] == 0x12;
}

inline bool IsLittleEndian(void)
{
	return !IsBigEndian();
}

#define CHAR_CODE(a, b, c, d)	(((a & 0xFF) << 0) | ((b & 0xFF) << 8) | ((c & 0xFF) << 16) | ((d & 0xFF) << 24))
#define MACRO_SWAP16(a)			((((a) & 0x00FF) << 8) | (((a) & 0xFF00) >> 8))
#define MACRO_SWAP32(a)			((((a) & 0x000000FF) << 24) | (((a) & 0x0000FF00) << 8) | (((a) & 0x00FF0000) >> 8) | (((a) & 0xFF000000) >> 24))

#define VERSION_CODE(primary, secondary, sub)	(((primary & 0xFFF) << 20) | ((secondary & 0xFFF) << 8) | ((sub & 0xFF) << 0))
#define VERSION_CODE_PRIMARY(in)				((in >> 20) & 0xFFF)
#define VERSION_CODE_SECONDARY(in)				((in >> 8) & 0xFFF)
#define VERSION_CODE_SUB(in)					((in >> 0) & 0xFF)

#define MAKE_COLOR(a, r, g, b)	(((a & 0xFF) << 24) | ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | ((b & 0xFF) << 0))
#define COLOR_ALPHA(in)			((in >> 24) & 0xFF)
#define COLOR_RED(in)			((in >> 16) & 0xFF)
#define COLOR_GREEN(in)			((in >> 8) & 0xFF)
#define COLOR_BLUE(in)			((in >> 0) & 0xFF)




