#pragma once

#include "BSMemObject.hpp"
#include <string_view>

template <typename T>
class BSStringT : public BSMemObject {
public:
	BSStringT() {};
	BSStringT(const T* apText) { Set(apText); }
	BSStringT(const BSStringT& aSrc) { Set(aSrc.c_str()); }
	~BSStringT();

	T*			pString = nullptr;
	uint16_t	sLen = 0;
	uint16_t	sMaxLen = 0;

	inline uint32_t			GetLength()		const;
	inline void				SetLength(uint32_t auiLen);
	inline uint16_t			GetMaxLength()	const { return sMaxLen; }
	inline void				SetMaxLength(uint16_t auiLen) { sMaxLen = auiLen; }

	inline bool				Set(const T* apText, uint32_t auiLength = 0);
	inline BSStringT<T>* operator+=(const T* apText);

	inline void				Format(const T* fmt, ...);
	inline void				ApplyFormat(const T* fmt, va_list args);

	inline bool				Includes(const char* toFind) const;
	inline bool				Replace(const char* toReplace, const char* replaceWith); // replaces instance of toReplace with replaceWith

	inline const T* c_str() const;

	operator std::basic_string_view<T>() const noexcept;
};

#include "BSStringT.inl"

typedef BSStringT<char>		BSString;
typedef BSStringT<wchar_t>	BSWideString;