#pragma once

#pragma warning(disable: 4100 4201 4244 4324 4389 5054 28159)

#include <d3d9.h>

#include <Windows.Foundation.h>
#include <wrl\wrappers\corewrappers.h>
#include <wrl\client.h>
#include <stdint.h>
#include <stdio.h>
#include <cmath>
#include <string>
#include <cassert>

#define JIP_CHANGES 1

constexpr inline auto our_snprintf	= snprintf;
constexpr inline auto our_sprintf	= sprintf;
constexpr inline auto our_vsprintf	= vsprintf;
constexpr inline auto our_vsnprintf	= vsnprintf;

#include "Utils/DebugLog.hpp"
#include "Utils/Bitfield.hpp"
#include "Utils/AddressPtr.hpp"

#include "SafeWrite/SafeWrite.hpp"

// Game unit conversion constants
constexpr inline double dM2NI	= 69.99125671386719;	// 1 Meter to Ni
constexpr inline double dDM2NI  = dM2NI / 10.0;			// 1 Decimeter to Ni
constexpr inline double dCM2NI  = dM2NI / 100.0;		// 1 Centimeter to Ni
constexpr inline double dMM2NI  = dM2NI / 1000.0;		// 1 Millimeter to Ni

constexpr inline double dNI2M	= 1.0 / dM2NI;			// 1 Ni to Meter
constexpr inline double dNI2DM  = 1.0 / dDM2NI;			// 1 Ni to Decimeter
constexpr inline double dNI2CM  = 1.0 / dCM2NI;			// 1 Ni to Centimeter
constexpr inline double dNI2MM  = 1.0 / dMM2NI;			// 1 Ni to Millimeter

// Havok uses decimeters (10cm) as base unit
constexpr inline float fHK2NI = static_cast<float>(dDM2NI); // 1 Havok to Ni
constexpr inline float fNI2HK = static_cast<float>(dNI2DM); // 1 Ni to Havok

template <typename T_Ret = void, typename ...Args>
__forceinline T_Ret ThisCall(uint32_t _addr, const void* _this, Args ...args) noexcept(false) {
	if constexpr (std::is_class_v<T_Ret>) {
		T_Ret ret;
		((T_Ret * (__thiscall*)(const void*, T_Ret&, Args...))_addr)(_this, ret, std::forward<Args>(args)...);
		return ret;
	}
	else {
		return ((T_Ret(__thiscall*)(const void*, Args...))_addr)(_this, std::forward<Args>(args)...);
	}
}

template <typename T_Ret = void, typename ...Args>
__forceinline T_Ret StdCall(uint32_t _addr, Args ...args) noexcept(false) {
	return ((T_Ret(__stdcall*)(Args...))_addr)(std::forward<Args>(args)...);
}

template <typename T_Ret = void, typename ...Args>
__forceinline T_Ret CdeclCall(uint32_t _addr, Args ...args) noexcept(false) {
	return ((T_Ret(__cdecl*)(Args...))_addr)(std::forward<Args>(args)...);
}

template <typename T_Ret = void, typename ...Args>
__forceinline T_Ret FastCall(uint32_t _addr, Args ...args) noexcept(false) {
	return ((T_Ret(__fastcall*)(Args...))_addr)(std::forward<Args>(args)...);
}

#pragma region Macros
#define EXTERN_DLL_EXPORT extern "C" __declspec(dllexport)

#define ALIGN1	alignas(1)
#define ALIGN2	alignas(2)
#define ALIGN4	alignas(4)
#define ALIGN8	alignas(8)
#define ALIGN16 alignas(16)

// KiB from bytes
#define B_KiB(x) (x##u << 10u)

// MiB from bytes
#define B_MiB(x) (x##u << 20u)

// GiB from bytes
#define B_GiB(x) (x##u << 30u)

#ifdef NDEBUG
#define ASSUME_ASSERT(x) __assume(x)
#else
#define ASSUME_ASSERT(x) assert(x)
#endif

#define ASSERT_SIZE(a, b) static_assert(sizeof(a) == b, "Wrong structure size!");
#define ASSERT_OFFSET(a, b, c) static_assert(offsetof(a, b) == c, "Wrong member offset!");

#define CREATE_OBJECT(CLASS, ADDRESS) static CLASS* CreateObject() { return CdeclCall<CLASS*>(ADDRESS); };

#ifdef GAME 
#define FUNCTION_UNKOWN static_assert(false, "Find \"" __FUNCSIG__ "\" in the game" );
#define FUNCTION_NOT_IMPLEMENTED static_assert(false, "Implement \"" __FUNCSIG__ "\" in the game" );
#else
#define FUNCTION_UNKOWN static_assert(false, "Find \"" __FUNCSIG__ "\" in GECK" );
#define FUNCTION_NOT_IMPLEMENTED static_assert(false, "Implement \"" __FUNCSIG__ "\" in GECK" );
#endif

#define SPEC_RESTRICT		__declspec(restrict)
#define SPEC_NOINLINE		__declspec(noinline)
#define SPEC_INLINE			__forceinline
#define SPEC_NORETURN		__declspec(noreturn)
#define SPEC_NOALIAS		__declspec(noalias)
#define SPEC_EMPTY_BASES	__declspec(empty_bases)
#define SPEC_NAKED			__declspec(naked)

#define _HELPER_COMBINE1(X,Y) X##Y
#define _HELPER_COMBINE(X,Y) _HELPER_COMBINE1(X,Y)

#define STACK_FRAME_OPT_ENABLE  _Pragma("optimize(\"y\", on)")
#define STACK_FRAME_OPT_DISABLE _Pragma("optimize(\"y\", off)")
#define STACK_FRAME_OPT_RESET   _Pragma("optimize(\"\", on)")

#define RUNTIME_CHECKS_DISABLE _Pragma("runtime_checks(\"\", off)")
#define RUNTIME_CHECKS_RESET   _Pragma("runtime_checks(\"\", restore)")
#pragma endregion