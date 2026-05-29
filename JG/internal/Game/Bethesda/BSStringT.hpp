#pragma once

#include "BSMemObject.hpp"

template <typename T>
class SPEC_EMPTY_BASES BSStringT : public BSMemObject {
public:
	BSStringT();
	BSStringT(const T* apText);
	BSStringT(const BSStringT& arSrc);
	BSStringT(BSStringT&& arSrc);
	~BSStringT();

	T*			pString		= nullptr;
	uint16_t	usLength	= 0;
	uint16_t	usMaxLength = 0;

	void				Init();

	const T*			GetString() const;
	
	uint32_t			GetLength() const;
	void				SetLength(uint32_t auiLength);

	uint16_t			GetMaxLength() const;
	void				SetMaxLength(uint32_t auiLength);

	uint32_t			GetByteLengthWithNull() const;

	bool				Set(const T* apText, uint32_t auiLength = 0);
	bool				Set(const BSStringT& arSource);

	int32_t				StrCmp(const T* apText, bool abNotCaseSensitive) const;
	int32_t				StrCmp(const BSStringT& arOther, bool abNotCaseSensitive) const;

	BSStringT&			operator=(const T* apText);
	BSStringT&			operator=(const BSStringT& arOther);

	BSStringT&			operator=(BSStringT&& arOther);

	bool				operator==(const T* apText) const;
	bool				operator==(const BSStringT& arOther) const;

	BSStringT&			operator+=(const T* apText);
	BSStringT&			operator+=(const BSStringT& arOther);
	const T*			operator[](uint32_t auiIndex);
						operator const T* ();

	void				SPrintF(const T* apFmt, ...);
	void				VSPrintF(const T* apFmt, va_list args);

	void				ToLower();
	void				ToUpper();

	const T*			c_str() const;
};

#include "BSStringT.inl"

typedef BSStringT<char>		BSString;
typedef BSStringT<wchar_t>	BSWideString;