#include "NiFixedString.hpp"
#include "NiGlobalStringTable.hpp"

NiFixedString::NiFixedString() {
	m_kHandle = nullptr;
}

// GAME - 0x438170
// GECK - 0x43D6B0
NiFixedString::NiFixedString(const char* apcString) {
	if (apcString)
		m_kHandle = NiGlobalStringTable::AddString(apcString);
	else
		m_kHandle = nullptr;
}

NiFixedString::NiFixedString(const NiFixedString& arString) {
	NiGlobalStringTable::IncRefCount(const_cast<NiGlobalStringTable::GlobalStringHandle&>(arString.m_kHandle));
	m_kHandle = arString.m_kHandle;
}

// GAME - 0x4381B0
// GECK - 0x43D6E0
NiFixedString::~NiFixedString() {
	NiGlobalStringTable::DecRefCount(m_kHandle);
}

// GAME - 0xA2E750
// GECK - 0x7D8020
NiFixedString& NiFixedString::operator=(const char* apcString) {
	if (m_kHandle != apcString) {
		NiGlobalStringTable::GlobalStringHandle kHandle = m_kHandle;
		m_kHandle = NiGlobalStringTable::AddString(apcString);
		NiGlobalStringTable::DecRefCount(kHandle);
	}
	return *this;
}

NiFixedString& NiFixedString::operator=(const NiFixedString& arString) {
	if (m_kHandle != arString.m_kHandle) {
		NiGlobalStringTable::GlobalStringHandle kHandle = arString.m_kHandle;
		NiGlobalStringTable::IncRefCount(kHandle);
		NiGlobalStringTable::DecRefCount(m_kHandle);
		m_kHandle = kHandle;
	}
	return *this;
}

NiFixedString::operator const char* () const {
	return m_kHandle;
}

NiFixedString::operator bool() const {
	return m_kHandle != nullptr;
}

const char* NiFixedString::c_str() const {
	return m_kHandle;
}

NiFixedString::operator std::basic_string_view<char>() const noexcept { 
	return { m_kHandle, GetLength() }; 
}

uint32_t NiFixedString::GetLength() const {
	return NiGlobalStringTable::GetLength(m_kHandle);
}

bool NiFixedString::Includes(const char* apToFind) const {
	if (!m_kHandle || !apToFind)
		return false;

	return strstr(m_kHandle, apToFind) != nullptr;
}

bool operator==(const NiFixedString& arString1, const NiFixedString& arString2) {
	return arString1.m_kHandle == arString2.m_kHandle;
}

bool operator==(const NiFixedString& arString, const char* apcString) {
	if (arString.m_kHandle == apcString)
		return true;

	if (!arString.m_kHandle || !apcString)
		return false;

	return !strcmp(arString.m_kHandle, apcString);
}

bool operator==(const char* apcString, const NiFixedString& arString) {
	if (arString.m_kHandle == apcString)
		return true;

	if (!arString.m_kHandle || !apcString)
		return false;

	return !strcmp(arString.m_kHandle, apcString);
}
