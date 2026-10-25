#pragma once

#include "BSStringT.hpp"

namespace {

	inline size_t BSstrlen(const char* apString) noexcept { return std::strlen(apString); };
	inline size_t BSstrlen(const wchar_t* apString) noexcept { return std::wcslen(apString); };

	inline int32_t BSstricmp(const char* apString1, const char* apString2) noexcept { return _stricmp(apString1, apString2); };
	inline int32_t BSstricmp(const wchar_t* apString1, const wchar_t* apString2) noexcept { return _wcsicmp(apString1, apString2); };

	inline int32_t BSstrcmp(const char* apString1, const char* apString2) noexcept { return strcmp(apString1, apString2); };
	inline int32_t BSstrcmp(const wchar_t* apString1, const wchar_t* apString2) noexcept { return wcscmp(apString1, apString2); };

	inline int32_t BSvsnprintf(char* apString, uint32_t auiSize, const char* apFormat, va_list aList) noexcept { return our_vsnprintf(apString, auiSize, apFormat, aList); };
	inline int32_t BSvsnprintf(wchar_t* apString, uint32_t auiSize, const wchar_t* apFormat, va_list aList) noexcept { return _vsnwprintf_s(apString, auiSize, auiSize, apFormat, aList); };

	inline errno_t BSstrupr(char* apString, uint32_t auiSize) noexcept { return _strupr_s(apString, auiSize); };
	inline errno_t BSstrupr(wchar_t* apString, uint32_t auiSize) noexcept { return _wcsupr_s(apString, auiSize); };

	inline errno_t BSstrlwr(char* apString, uint32_t auiSize) noexcept { return _strlwr_s(apString, auiSize); };
	inline errno_t BSstrlwr(wchar_t* apString, uint32_t auiSize) noexcept { return _wcslwr_s(apString, auiSize); };

}

// GAME - 0x4037B0
template<typename T>
inline BSStringT<T>::BSStringT() noexcept {
	Init();
}

// GAME - 0x40C0E0
// GECK - 0x4070F0
template<typename T>
inline BSStringT<T>::BSStringT(const T* apText) noexcept {
	Init();
	Set(apText);
}

// GAME - 0x4047F0
// GECK - 0x4070C0
template<typename T>
inline BSStringT<T>::BSStringT(const BSStringT& arSrc) noexcept {
	Init();
	Set(arSrc);
}

template<typename T>
inline BSStringT<T>::BSStringT(BSStringT&& arSrc) noexcept {
	pString = arSrc.pString;
	usLength = arSrc.usLength;
	usMaxLength = arSrc.usMaxLength;
	arSrc.pString = nullptr;
	arSrc.usLength = 0;
	arSrc.usMaxLength = 0;
}

// GAME - 0x4037D0
// GECK - 0x40CBF0
template<typename T>
inline BSStringT<T>::~BSStringT() noexcept {
	Set(nullptr);
}

// GAME - 0x403970
template<typename T>
inline void BSStringT<T>::Init() noexcept {
	pString = nullptr;
	SetLength(0);
	SetMaxLength(0);
}

// GAME - 0x559450
template<typename T>
inline const T* BSStringT<T>::GetString() const noexcept {
	return pString;
}

// GAME - 0x4048E0
// GECK - 0x405280
template<typename T>
inline uint32_t BSStringT<T>::GetLength() const noexcept {
	if (usLength == UINT16_MAX) [[unlikely]] {
		return BSstrlen(pString);
	}
	else [[likely]] {
		return usLength;
	}
}

// GAME - 0x4039C0
template<typename T>
inline void BSStringT<T>::SetLength(uint32_t auiLength) noexcept {
	usLength = auiLength > UINT16_MAX ? UINT16_MAX : auiLength;
}

// GAME - 0x4039A0
template<typename T>
inline uint16_t BSStringT<T>::GetMaxLength() const noexcept {
	return usMaxLength;
}

// GAME - 0x403A00
template<typename T>
inline void BSStringT<T>::SetMaxLength(uint32_t auiLength) noexcept {
	usMaxLength = auiLength > UINT16_MAX ? UINT16_MAX : auiLength;
}

template<typename T>
inline uint32_t BSStringT<T>::GetByteLengthWithNull() const noexcept {
	return GetLength() + sizeof(T);
}

// GAME - 0x4037F0
// GECK - 0x405B40
template<typename T>
inline bool BSStringT<T>::Set(const T* apText, uint32_t auiLength) noexcept {
	const uint32_t uiLength = apText ? BSstrlen(apText) : 0;
	const uint32_t uiAllocLength = std::max(uiLength, auiLength);
	if (uiAllocLength > GetMaxLength()) {
		T* pOrgStr = pString;
		pString = BSMemory::malloc<T>(uiAllocLength + sizeof(T));
		if (apText)
			std::memcpy(pString, apText, uiLength + sizeof(T));
		else
			pString[0] = 0;

		if (pOrgStr)
			BSMemory::free(pOrgStr);
		
		SetMaxLength(uiAllocLength);
	}
	else if (uiAllocLength) {
		if (apText)
			std::memcpy(pString, apText, uiLength + sizeof(T));
		else
			pString[0] = 0;
	}
	else {
		if (pString)
			BSMemory::free(pString);

		pString = nullptr;
		SetMaxLength(0);
	}
	SetLength(uiLength);
	return uiLength != 0;
}

// GAME - 0x438470
// GECK - 0x406710
template<typename T>
inline bool BSStringT<T>::Set(const BSStringT& arSource) noexcept {
	const uint32_t uiLength = arSource.GetLength();
	if (uiLength > GetMaxLength()) {
		T* pOrgStr = pString;
		pString = BSMemory::malloc<T>(uiLength + sizeof(T));
		std::memcpy(pString, arSource.GetString(), uiLength + sizeof(T));

		if (pOrgStr)
			BSMemory::free(pOrgStr);

		SetMaxLength(uiLength);
	}
	else if (uiLength) {
		std::memcpy(pString, arSource.GetString(), uiLength + sizeof(T));
	}
	else {
		if (pString)
			BSMemory::free(pString);

		pString = nullptr;
		SetMaxLength(0);
	};
	SetLength(uiLength);
	return uiLength != 0;
}

// GAME - 0x408A80
// GECK - 0x40BB10
template<typename T>
inline int32_t BSStringT<T>::StrCmp(const T* apText, bool abNotCaseSensitive) const noexcept {
	if (apText && GetString()) {
		if (abNotCaseSensitive)
			return BSstricmp(GetString(), apText);
		else
			return BSstrcmp(GetString(), apText);
	}
	else if (apText || GetString()) {
		return 2 * (apText == nullptr) - 1;
	}
	else {
		return 0;
	}
}

// GAME - 0x501C90
template<typename T>
inline int32_t BSStringT<T>::StrCmp(const BSStringT& arOther, bool abNotCaseSensitive) const noexcept {
	return StrCmp(arOther.GetString(), abNotCaseSensitive);
}

// GAME - 0x438390
// GECK - 0x407080
template<typename T>
inline BSStringT<T>& BSStringT<T>::operator=(const T* apText) noexcept {
	Set(apText);
	return *this;
}

// GAME - 0x501C10
template<typename T>
inline BSStringT<T>& BSStringT<T>::operator=(const BSStringT& arOther) noexcept {
	Set(arOther);
	return *this;
}

template<typename T>
inline BSStringT<T>& BSStringT<T>::operator=(BSStringT&& arOther) noexcept {
	pString = arOther.pString;
	usLength = arOther.usLength;
	usMaxLength = arOther.usMaxLength;
	arOther.pString = nullptr;
	arOther.usLength = 0;
	arOther.usMaxLength = 0;
	return *this;
}

template<typename T>
inline bool BSStringT<T>::operator==(const T* apText) const noexcept {
	return StrCmp(apText, true) == 0;
}

// GAME - 0x501C60
template<typename T>
inline bool BSStringT<T>::operator==(const BSStringT& arOther) const noexcept {
	return StrCmp(arOther, true) == 0;
}

// GAME - 0x404820
// GECK - 0x405C40
template<typename T>
inline BSStringT<T>& BSStringT<T>::operator+=(const T* apText) noexcept {
	if (!apText)
		return *this;

	if (GetString()) {
		const uint32_t uiAppendLength = apText ? BSstrlen(apText) : 0;
		const uint32_t uiNewLength = GetLength() + uiAppendLength;
		if (uiNewLength > GetMaxLength())
			Set(GetString(), uiNewLength);

		const uint32_t uiLength = GetLength();
		memcpy(&pString[uiLength], apText, uiAppendLength + sizeof(T));
		SetLength(uiNewLength);
	}
	else {
		Set(apText);
	}
	return *this;
}

// GAME - 0x7E0D80
// GECK - 0x406810
template<typename T>
inline BSStringT<T>& BSStringT<T>::operator+=(const BSStringT& arOther) noexcept {
	if (!arOther)
		return *this;

	if (GetString()) {
		const uint32_t uiAppendLength = arOther.GetLength();
		const uint32_t uiNewLength = GetLength() + uiAppendLength;
		if (uiNewLength > GetMaxLength())
			Set(GetString(), uiNewLength);

		const uint32_t uiLength = GetLength();
		memcpy(&pString[uiLength], arOther.GetString(), arOther.GetByteLengthWithNull());
		SetLength(uiNewLength);
	}
	else {
		Set(arOther);
	}
	return *this;
}

// GAME - 0x83DA30
template<typename T>
inline const T* BSStringT<T>::operator[](uint32_t auiIndex) noexcept {
	return &pString[pString ? auiIndex : 0];
}

template<typename T>
inline BSStringT<T>::operator const T* () noexcept {
	return GetString();
}

// GAME - 0x406F60
// GECK - 0x407120
template<typename T>
inline void BSStringT<T>::SPrintF(const T* apFmt, ...) noexcept {
	va_list args;
	va_start(args, apFmt);
	VSPrintF(apFmt, args);
	va_end(args);
}

// GAME - 0x406F90
// GECK - 0x4069E0
template<typename T>
inline void BSStringT<T>::VSPrintF(const T* apFmt, va_list args) noexcept {
	T cBuffer[1024];
	BSvsnprintf(cBuffer, _countof(cBuffer), apFmt, args);
	Set(cBuffer);
}

// GAME - 0x4AFAD0
template<typename T>
inline void BSStringT<T>::MakeLower() noexcept {
	if (pString)
		BSstrlwr(pString, usLength + 1);
}

// GAME - 0x7B52A0
template<typename T>
inline void BSStringT<T>::MakeUpper() noexcept {
	if (pString)
		BSstrupr(pString, usLength + 1);
}

template<typename T>
inline const T* BSStringT<T>::c_str() const noexcept {
	return pString ? pString : "";
}

#pragma region Specializations - char

// GAME - 0x40C0E0
// GECK - 0x4070F0
inline BSStringT<char>::BSStringT(const char* apText) noexcept {
#ifdef GAME
	ThisCall(0x40C0E0, this, apText);
#else
	ThisCall(0x4070F0, this, apText);
#endif
}

// GAME - 0x4047F0
// GECK - 0x4070C0
inline BSStringT<char>::BSStringT(const BSStringT<char>& arSrc) noexcept {
#ifdef GAME
	ThisCall(0x4047F0, this, &arSrc);
#else
	ThisCall(0x4070C0, this, &arSrc);
#endif
}

// GAME - 0x4037D0
// GECK - 0x40CBF0
inline BSStringT<char>::~BSStringT() noexcept {
#ifdef GAME
	ThisCall(0x4037D0, this);
#else
	ThisCall(0x40CBF0, this);
#endif
}

// GAME - 0x4048E0
// GECK - 0x405280
inline uint32_t BSStringT<char>::GetLength() const noexcept {
#ifdef GAME
	return ThisCall<uint32_t>(0x4048E0, this);
#else
	return ThisCall<uint32_t>(0x405280, this);
#endif
}

// GAME - 0x4037F0
// GECK - 0x405B40
inline bool BSStringT<char>::Set(const char* apText, uint32_t auiLength) noexcept {
#ifdef GAME
	return ThisCall<bool>(0x4037F0, this, apText, auiLength);
#else
	return ThisCall<bool>(0x405B40, this, apText, auiLength);
#endif
}

// GAME - 0x438470
// GECK - 0x406710
inline bool BSStringT<char>::Set(const BSStringT<char>& arSource) noexcept {
#ifdef GAME
	return ThisCall<bool>(0x438470, this, &arSource);
#else
	return ThisCall<bool>(0x406710, this, &arSource);
#endif
}

// GAME - 0x408A80
// GECK - 0x40BB10
inline int32_t BSStringT<char>::StrCmp(const char* apText, bool abNotCaseSensitive) const noexcept {
#ifdef GAME
	return ThisCall<int32_t>(0x408A80, this, apText, abNotCaseSensitive);
#else
	return ThisCall<int32_t>(0x40BB10, this, apText, abNotCaseSensitive);
#endif
}

// GAME - 0x404820
// GECK - 0x405C40
inline BSStringT<char>& BSStringT<char>::operator+=(const char* apText) noexcept {
#ifdef GAME
	return ThisCall<BSStringT<char>&>(0x404820, this, apText);
#else
	return ThisCall<BSStringT<char>&>(0x405C40, this, apText);
#endif
}

// GAME - 0x7E0D80
// GECK - 0x406810
inline BSStringT<char>& BSStringT<char>::operator+=(const BSStringT<char>& arOther) noexcept {
#ifdef GAME
	return ThisCall<BSStringT<char>&>(0x7E0D80, this, &arOther);
#else
	return ThisCall<BSStringT<char>&>(0x406810, this, &arOther);
#endif
}

// GAME - 0x406F90
// GECK - 0x4069E0
inline void BSStringT<char>::VSPrintF(const char* apFmt, va_list args) noexcept {
#ifdef GAME
	ThisCall(0x406F90, this, apFmt, args);
#else
	ThisCall(0x4069E0, this, apFmt, args);
#endif
}

#pragma endregion

#pragma region Specializations - wchar_t

// GAME - 0xAFFF50
// GECK - 0x8A0E30
inline bool BSStringT<wchar_t>::Set(const wchar_t* apText, uint32_t auiLength) noexcept {
#ifdef GAME
	return ThisCall<bool>(0xAFFF50, this, apText, auiLength);
#else
	return ThisCall<bool>(0x8A0E30, this, apText, auiLength);
#endif
}

// GAME - 0xB00120
// GECK - 0x8A1000
inline BSStringT<wchar_t>& BSStringT<wchar_t>::operator+=(const wchar_t* apText) noexcept {
#ifdef GAME
	return ThisCall<BSStringT<wchar_t>&>(0xB00120, this, apText);
#else
	return ThisCall<BSStringT<wchar_t>&>(0x8A1000, this, apText);
#endif
}

#pragma endregion