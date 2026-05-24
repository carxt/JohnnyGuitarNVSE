#pragma once

#include "NiGlobalStringTable.hpp"
#include <string_view>

class SPEC_EMPTY_BASES NiFixedString : public NiMemObject {
public:
	NiFixedString() noexcept;
	NiFixedString(const char* apString) noexcept;
	NiFixedString(const NiFixedString& arString) noexcept;
	~NiFixedString() noexcept;

	NiGlobalStringTable::GlobalStringHandle m_kHandle;

	NiFixedString& operator=(const char* apString) noexcept;
	NiFixedString& operator=(const NiFixedString& arString) noexcept;
	friend bool operator==(const NiFixedString& arString1, const NiFixedString& arString2) noexcept;
	friend bool operator==(const NiFixedString& arString, const char* apString) noexcept;
	friend bool operator==(const char* apString, const NiFixedString& arString) noexcept;

	operator const char*() const noexcept;

	operator bool() const noexcept;

	const char* c_str() const noexcept;

	operator std::basic_string_view<char>() const noexcept;

	uint32_t GetLength() const noexcept;

	bool Includes(const char* apToFind) const noexcept;
};

ASSERT_SIZE(NiFixedString, 0x4)