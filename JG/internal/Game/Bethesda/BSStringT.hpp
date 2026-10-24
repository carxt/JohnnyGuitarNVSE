#pragma once

#include "BSMemObject.hpp"

template <typename T>
class SPEC_EMPTY_BASES BSStringT : public BSMemObject {
public:
	BSStringT() noexcept;
	BSStringT(const T* apText) noexcept;
	BSStringT(const BSStringT& arSrc) noexcept;
	BSStringT(BSStringT&& arSrc) noexcept;
	~BSStringT() noexcept;

	T*			pString		= nullptr;
	uint16_t	usLength	= 0;
	uint16_t	usMaxLength = 0;

	void				Init() noexcept;

	const T*			GetString() const noexcept;
	
	uint32_t			GetLength() const noexcept;
	void				SetLength(uint32_t auiLength) noexcept;

	uint16_t			GetMaxLength() const noexcept;
	void				SetMaxLength(uint32_t auiLength) noexcept;

	uint32_t			GetByteLengthWithNull() const noexcept;

	bool				Set(const T* apText, uint32_t auiLength = 0) noexcept;
	bool				Set(const BSStringT& arSource) noexcept;

	int32_t				StrCmp(const T* apText, bool abNotCaseSensitive) const noexcept;
	int32_t				StrCmp(const BSStringT& arOther, bool abNotCaseSensitive) const noexcept;

	BSStringT&			operator=(const T* apText) noexcept;
	BSStringT&			operator=(const BSStringT& arOther) noexcept;

	BSStringT&			operator=(BSStringT&& arOther) noexcept;

	bool				operator==(const T* apText) const noexcept;
	bool				operator==(const BSStringT& arOther) const noexcept;

	BSStringT&			operator+=(const T* apText) noexcept;
	BSStringT&			operator+=(const BSStringT& arOther) noexcept;

	const T*			operator[](uint32_t auiIndex) noexcept;
						operator const T* () noexcept;

	void				SPrintF(const T* apFmt, ...) noexcept;
	void				VSPrintF(const T* apFmt, va_list args) noexcept;

	void				MakeLower() noexcept;
	void				MakeUpper() noexcept;

	const T*			c_str() const noexcept;
};

#include "BSStringT.inl"

using BSString		= BSStringT<char>;
using BSWideString	= BSStringT<wchar_t>;

ASSERT_SIZE(BSString, 0x8);
ASSERT_SIZE(BSWideString, 0x8);