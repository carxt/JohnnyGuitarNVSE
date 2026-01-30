#pragma once

#include "BSStringT.hpp"

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
	Set(arSrc.pString);
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
	if (usLength == UINT16_MAX) {
		if constexpr (std::is_same_v<T, wchar_t>)
			return std::wcslen(pString);
		else
			return std::strlen(pString);
	}
	else {
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

// GAME - 0x4037F0
template<typename T>
inline bool BSStringT<T>::Set(const T* apText, uint32_t auiLengthgth) {
	uint32_t uiLength = 0;
	if (apText) {
		if constexpr (std::is_same_v<T, wchar_t>)
			uiLength = std::wcslen(apText);
		else
			uiLength = std::strlen(apText);
	}

	uint32_t uiAllocLength = std::max(uiLength, auiLengthgth);
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

// GAME - 0x408A80
template<typename T>
inline int32_t BSStringT<T>::StrCmp(const T* apText, bool abNotCaseSensitive) const {
	if (apText && GetString()) {
		if (abNotCaseSensitive) {
			if constexpr (std::is_same_v<T, wchar_t>)
				return std::wcscmp(GetString(), apText);
			else
				return stricmp(GetString(), apText);
		}
		else {
			if constexpr (std::is_same_v<T, wchar_t>)
				return std::wcscmp(GetString(), apText);
			else
				return std::strcmp(GetString(), apText);
		}
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
inline void BSStringT<T>::operator=(const T* apText) {
	Set(apText);
}

// GAME - 0x501C60
template<typename T>
inline bool BSStringT<T>::operator==(const BSStringT<T>& arOther) const {
	return StrCmp(arOther, true) == 0;
}

// GAME - 0x404820
template<typename T>
inline BSStringT<T>* BSStringT<T>::operator+=(const T* apText) {
	if (!apText)
		return this;

	if (GetString()) {
		uint32_t uiAppendLength = strlen(apText);
		uint32_t uiNewLength = GetLength() + uiAppendLength;
		if (uiNewLength > GetMaxLength()) {
			Set(GetString(), uiNewLength);
		}
		uint32_t uiLength = GetLength();
		memcpy(&pString[uiLength], apText, uiAppendLength + sizeof(T));
		SetLength(uiNewLength);
	}
	else {
		Set(apText);
	}
	return this;
}

// GAME - 0x7E0D80
template<typename T>
inline BSStringT<T>* BSStringT<T>::operator+=(const BSStringT<T>& arOther) {
	return operator+=(arOther.GetString());
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
	T cBuffer[1024] = {};
	if constexpr (std::is_same_v<T, wchar_t>)
		_vsnwprintf_s(cBuffer, _countof(cBuffer), apFmt, args);
	else
		our_vsnprintf(cBuffer, _countof(cBuffer), apFmt, args);
	Set(cBuffer);
}

// GAME - 0x4AFAD0
template<typename T>
inline void BSStringT<T>::ToLower() {
	if (pString) {
		if constexpr (std::is_same_v<T, wchar_t>)
			_wcslwr_s(pString, usLength + 1);
		else
			_strlwr_s(pString, usLength + 1);
	}
}

// GAME - 0x7B52A0
template<typename T>
inline void BSStringT<T>::ToUpper() {
	if (pString) {
		if constexpr (std::is_same_v<T, wchar_t>)
			_wcsupr_s(pString, usLength + 1);
		else
			_strupr_s(pString, usLength + 1);
	}
}

template<typename T>
inline const T* BSStringT<T>::c_str() const {
	return (pString && usLength) ? pString : "";
}