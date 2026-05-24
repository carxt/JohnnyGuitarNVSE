#include "NiFixedString.hpp"
#include "NiGlobalStringTable.hpp"

NiFixedString::NiFixedString() noexcept {
	m_kHandle = nullptr;
}

// GAME - 0x438170
// GECK - 0x43D6B0
NiFixedString::NiFixedString(const char* apString) noexcept {
	if (apString)
		m_kHandle = NiGlobalStringTable::AddString(apString);
	else
		m_kHandle = nullptr;
}

NiFixedString::NiFixedString(const NiFixedString& arString) noexcept {
	NiGlobalStringTable::IncRefCount(const_cast<NiGlobalStringTable::GlobalStringHandle&>(arString.m_kHandle));
	m_kHandle = arString.m_kHandle;
}

// GAME - 0x4381B0
// GECK - 0x43D6E0
NiFixedString::~NiFixedString() noexcept {
	NiGlobalStringTable::DecRefCount(m_kHandle);
}

// GAME - 0xA2E750
// GECK - 0x7D8020
NiFixedString& NiFixedString::operator=(const char* apString) noexcept {
	if (m_kHandle != apString) {
		NiGlobalStringTable::GlobalStringHandle kHandle = m_kHandle;
		m_kHandle = NiGlobalStringTable::AddString(apString);
		NiGlobalStringTable::DecRefCount(kHandle);
	}
	return *this;
}

// GAME - 0x43BA10
NiFixedString& NiFixedString::operator=(const NiFixedString& arString) noexcept {
	if (m_kHandle != arString.m_kHandle) {
		NiGlobalStringTable::GlobalStringHandle kHandle = arString.m_kHandle;
		NiGlobalStringTable::IncRefCount(kHandle);
		NiGlobalStringTable::DecRefCount(m_kHandle);
		m_kHandle = kHandle;
	}
	return *this;
}

// GAME - 0x43B1B0
NiFixedString::operator const char* () const noexcept {
	return m_kHandle;
}

// GAME - 0x48AF70
NiFixedString::operator bool() const noexcept {
	return m_kHandle != nullptr;
}

const char* NiFixedString::c_str() const noexcept {
	return m_kHandle;
}

NiFixedString::operator std::basic_string_view<char>() const noexcept { 
	return { m_kHandle, GetLength() }; 
}

uint32_t NiFixedString::GetLength() const noexcept {
	return NiGlobalStringTable::GetLength(m_kHandle);
}

bool NiFixedString::Includes(const char* apToFind) const noexcept {
	if (!m_kHandle || !apToFind)
		return false;

	return strstr(m_kHandle, apToFind) != nullptr;
}

bool operator==(const NiFixedString& arString1, const NiFixedString& arString2) noexcept {
	return arString1.m_kHandle == arString2.m_kHandle;
}

// GAME - 0xA305E0
// GECK - 0x7D8060
bool operator==(const NiFixedString& arString, const char* apString) noexcept {
	if (arString.m_kHandle == apString)
		return true;

	if (!arString.m_kHandle || !apString)
		return false;

	return !strcmp(arString.m_kHandle, apString);
}

bool operator==(const char* apString, const NiFixedString& arString) noexcept {
	if (arString.m_kHandle == apString)
		return true;

	if (!arString.m_kHandle || !apString)
		return false;

	return !strcmp(arString.m_kHandle, apString);
}
