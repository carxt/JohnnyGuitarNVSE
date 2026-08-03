#pragma once

#include "BSStringT.hpp"

namespace {

	inline size_t BSstrlen(const char* apString) { return std::strlen(apString); };
	inline size_t BSstrlen(const wchar_t* apString) { return std::wcslen(apString); };

	inline int32_t BSstricmp(const char* apString1, const char* apString2) { return _stricmp(apString1, apString2); };
	inline int32_t BSstricmp(const wchar_t* apString1, const wchar_t* apString2) { return _wcsicmp(apString1, apString2); };

	inline int32_t BSstrcmp(const char* apString1, const char* apString2) { return strcmp(apString1, apString2); };
	inline int32_t BSstrcmp(const wchar_t* apString1, const wchar_t* apString2) { return wcscmp(apString1, apString2); };

	inline int32_t BSvsnprintf(char* apString, uint32_t auiSize, const char* apFormat, va_list aList) { return our_vsnprintf(apString, auiSize, apFormat, aList); };
	inline int32_t BSvsnprintf(wchar_t* apString, uint32_t auiSize, const wchar_t* apFormat, va_list aList) { return _vsnwprintf_s(apString, auiSize, auiSize, apFormat, aList); };

	inline errno_t BSstrupr(char* apString, uint32_t auiSize) { return _strupr_s(apString, auiSize); };
	inline errno_t BSstrupr(wchar_t* apString, uint32_t auiSize) { return _wcsupr_s(apString, auiSize); };

	inline errno_t BSstrlwr(char* apString, uint32_t auiSize) { return _strlwr_s(apString, auiSize); };
	inline errno_t BSstrlwr(wchar_t* apString, uint32_t auiSize) { return _wcslwr_s(apString, auiSize); };

}

// GAME - 0x4037B0
template<typename T>
inline BSStringT<T>::BSStringT() {
	Init();
}

// GAME - 0x40C0E0
template<typename T>
inline BSStringT<T>::BSStringT(const T* apText) {
	Init();
	Set(apText);
}

// GAME - 0x4047F0
template<typename T>
inline BSStringT<T>::BSStringT(const BSStringT& arSrc) {
	Init();
	Set(arSrc);
}

template<typename T>
inline BSStringT<T>::BSStringT(BSStringT&& arSrc) {
	pString = arSrc.pString;
	usLength = arSrc.usLength;
	usMaxLength = arSrc.usMaxLength;
	arSrc.pString = nullptr;
	arSrc.usLength = 0;
	arSrc.usMaxLength = 0;
}

// GAME - 0x403970
template<typename T>
inline void BSStringT<T>::Init() {
	pString = nullptr;
	SetLength(0);
	SetMaxLength(0);
}

// GAME - 0x4037D0
template<typename T>
inline BSStringT<T>::~BSStringT() {
	Set(nullptr);
}

// GAME - 0x559450
template<typename T>
inline const T* BSStringT<T>::GetString() const {
	return pString;
}

// GAME - 0x4048E0
template<typename T>
inline uint32_t BSStringT<T>::GetLength() const {
	if (usLength == UINT16_MAX) [[unlikely]] {
		return BSstrlen(pString);
	}
	else [[likely]] {
		return usLength;
	}
}

// GAME - 0x4039C0
template<typename T>
inline void BSStringT<T>::SetLength(uint32_t auiLength) {
	usLength = auiLength > UINT16_MAX ? UINT16_MAX : auiLength;
}

// GAME - 0x4039A0
template<typename T>
inline uint16_t BSStringT<T>::GetMaxLength() const {
	return usMaxLength;
}

// GAME - 0x403A00
template<typename T>
inline void BSStringT<T>::SetMaxLength(uint32_t auiLength) {
	usMaxLength = auiLength > UINT16_MAX ? UINT16_MAX : auiLength;
}

template<typename T>
inline uint32_t BSStringT<T>::GetByteLengthWithNull() const {
	return GetLength() + sizeof(T);
}

// GAME - 0x4037F0
template<typename T>
inline bool BSStringT<T>::Set(const T* apText, uint32_t auiLength) {
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
template<typename T>
inline bool BSStringT<T>::Set(const BSStringT<T>& arSource) {
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
template<typename T>
inline int32_t BSStringT<T>::StrCmp(const T* apText, bool abNotCaseSensitive) const {
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
inline int32_t BSStringT<T>::StrCmp(const BSStringT<T>& arOther, bool abNotCaseSensitive) const {
	return StrCmp(arOther.GetString(), abNotCaseSensitive);
}

// GAME - 0x438390
template<typename T>
inline BSStringT<T>& BSStringT<T>::operator=(const T* apText) {
	Set(apText);
	return *this;
}

// GAME - 0x501C10
template<typename T>
inline BSStringT<T>& BSStringT<T>::operator=(const BSStringT<T>& arOther) {
	Set(arOther);
	return *this;
}

template<typename T>
inline BSStringT<T>& BSStringT<T>::operator=(BSStringT<T>&& arOther) {
	pString = arOther.pString;
	usLength = arOther.usLength;
	usMaxLength = arOther.usMaxLength;
	arOther.pString = nullptr;
	arOther.usLength = 0;
	arOther.usMaxLength = 0;
}

template<typename T>
inline bool BSStringT<T>::operator==(const T* apText) const {
	return StrCmp(apText, true) == 0;
}

// GAME - 0x501C60
template<typename T>
inline bool BSStringT<T>::operator==(const BSStringT<T>& arOther) const {
	return StrCmp(arOther, true) == 0;
}

// GAME - 0x404820
template<typename T>
inline BSStringT<T>& BSStringT<T>::operator+=(const T* apText) {
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
template<typename T>
inline BSStringT<T>& BSStringT<T>::operator+=(const BSStringT<T>& arOther) {
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
inline const T* BSStringT<T>::operator[](uint32_t auiIndex) {
	return &pString[pString ? auiIndex : 0];
}

template<typename T>
inline BSStringT<T>::operator const T* () {
	return GetString();
}

// GAME - 0x406F60
template<typename T>
inline void BSStringT<T>::SPrintF(const T* apFmt, ...) {
	va_list args;
	va_start(args, apFmt);
	VSPrintF(apFmt, args);
	va_end(args);
}

// GAME - 0x406F90
template<typename T>
inline void BSStringT<T>::VSPrintF(const T* apFmt, va_list args) {
	T cBuffer[1024];
	BSvsnprintf(cBuffer, _countof(cBuffer), apFmt, args);
	Set(cBuffer);
}

// GAME - 0x4AFAD0
template<typename T>
inline void BSStringT<T>::MakeLower() {
	if (pString)
		BSstrlwr(pString, usLength + 1);
}

// GAME - 0x7B52A0
template<typename T>
inline void BSStringT<T>::MakeUpper() {
	if (pString)
		BSstrupr(pString, usLength + 1);
}

template<typename T>
inline const T* BSStringT<T>::c_str() const {
	return pString ? pString : "";
}