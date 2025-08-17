#pragma once
#include "BSStringT.hpp"

// 0x4037F0
template<typename T>
inline bool BSStringT<T>::Set(const T* apText, uint32_t auiLength) {
	uint32_t uiLength = 0;
	if (apText) {
		uiLength = strlen(apText);
	}

	uint32_t uiAllocLength = std::max(uiLength, auiLength);
	if (uiAllocLength > GetMaxLength()) {
		T* pOrgStr = pString;
		pString = BSNew<T>(uiAllocLength + sizeof(T));
		if (apText)
			memcpy(pString, apText, uiLength + sizeof(T));
		else
			pString[0] = 0;

		if (pOrgStr)
			BSFree(pOrgStr);

		SetMaxLength(uiAllocLength);
	}
	else if (uiAllocLength) {
		if (apText)
			memcpy(pString, apText, uiLength + sizeof(T));
		else
			pString[0] = 0;
	}
	else {
		if (pString)
			BSFree(pString);

		pString = nullptr;
		SetMaxLength(0);
	}
	SetLength(uiLength);
	return uiLength != 0;
}

// 0x404820
template<typename T>
inline BSStringT<T>* BSStringT<T>::operator+=(const T* apText) {
	if (!apText)
		return this;

	if (pString) {
		uint32_t uiAppendLength = strlen(apText);
		uint32_t uiNewLength = GetLength() + uiAppendLength;
		if (uiNewLength > GetMaxLength()) {
			Set(pString, uiNewLength);
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

// 0x406F60
template<typename T>
inline void BSStringT<T>::Format(const T* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	ApplyFormat(fmt, args);
	va_end(args);
}

// 0x406F90
template<typename T>
inline void BSStringT<T>::ApplyFormat(const T* fmt, va_list args) {
	char cBuffer[1024] = {};
	our_vsnprintf(cBuffer, _countof(cBuffer), fmt, args);
	Set(cBuffer);
}

template<typename T>
inline bool BSStringT<T>::Includes(const char* toFind) const {
	if (!pString || !toFind)
		return false;

	return strstr(pString, toFind) != nullptr;
}

template<typename T>
inline bool BSStringT<T>::Replace(const char* _toReplace, const char* _replaceWith) {
	if (!pString || !_toReplace || !_replaceWith)
		return false;

	std::string_view toReplace(_toReplace);
	std::string_view replaceWith(_replaceWith);
	std::string_view str(pString, sLen);

	size_t pos = str.find(toReplace);
	if (pos == std::string_view::npos)
		return false;

	str.replace(pos, toReplace.length(), replaceWith);
	Set(str.c_str());
	return true;
}

template<typename T>
inline BSStringT<T>::~BSStringT() {
	if (pString) {
		BSFree(pString);
		pString = nullptr;
	}
	sMaxLen = sLen = 0;
}

// 0x4048E0
template<typename T>
inline uint32_t BSStringT<T>::GetLength() const {
	return sLen == UINT16_MAX ? strlen(pString) : sLen;
}

template<typename T>
inline void BSStringT<T>::SetLength(uint32_t auiLen) {
	sLen = auiLen > UINT16_MAX ? UINT16_MAX : auiLen;
}

template<typename T>
inline const T* BSStringT<T>::c_str() const {
	return (pString && sLen) ? pString : "";
}

template<typename T>
inline BSStringT<T>::operator std::basic_string_view<T>() const noexcept {
	return { pString, GetLength() };
}