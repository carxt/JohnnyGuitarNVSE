#pragma once

// 4018 - signed/unsigned mismatch
// 4244 - loss of data by assignment
// 4267 - possible loss of data (truncation)
// 4305 - truncation by assignment
// 4288 - disable warning for crap microsoft extension screwing up the scope of variables defined in for loops
// 4311 - pointer truncation
// 4312 - pointer extension
// credits to Ian Patterson
#pragma warning(disable: 4018 4244 4267 4305 4288 4312 4311)

// winxp and above
#define _WIN32_WINNT	0x0501

#include <map>
#include <Windows.h>
#include "nvse/nvse_version.h"

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


// based on the boost implementation of static asserts
template <bool x> struct StaticAssertFailure;
template <> struct StaticAssertFailure <true> { enum { a = 1 }; };
template <int x> struct static_assert_test { };


#define STATIC_ASSERT(a)	typedef static_assert_test <sizeof(StaticAssertFailure<(bool)(a)>)> static_assert_typedef_ ## __COUNTER__