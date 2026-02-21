#pragma once

#include "Gamebryo/NiTStringMap.hpp"

template<class T>
class BSTCaseInsensitiveStringMap : public NiTStringMap<T> {
public:
	BSTCaseInsensitiveStringMap(uint32_t auiHashSize = 37, bool abCopy = true) : NiTStringMap<T>(auiHashSize, abCopy) {};
	uint32_t	KeyToHashIndex(const char* apKey) const override;
	bool		IsKeysEqual(const char* apKey1, const char* apKey2) const override;
};

template<class T>
inline uint32_t BSTCaseInsensitiveStringMap<T>::KeyToHashIndex(const char* apKey) const {
	uint32_t uiKey = 0;
	while (*apKey) {
		char cCharacter = tolower(*apKey);
		uiKey = cCharacter + 33 * uiKey;
		++apKey;
	}
	return uiKey % NiTStringMap<T>::m_uiHashSize;
}

template<class T>
inline bool BSTCaseInsensitiveStringMap<T>::IsKeysEqual(const char* apKey1, const char* apKey2) const {
	return _stricmp(apKey1, apKey2) == 0;
}
