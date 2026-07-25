#pragma once

#include "NiMemObject.hpp"

class SPEC_EMPTY_BASES NiRTTI : public NiMemObject {
public:
	NiRTTI() { m_pcName = nullptr; m_pkBaseRTTI = nullptr; }
	NiRTTI(const char* apName, const NiRTTI* const apBase) { m_pcName = apName; m_pkBaseRTTI = apBase; }
	NiRTTI(const char* apName, const NiRTTI& apBase) { m_pcName = apName; m_pkBaseRTTI = &apBase; }

	const char* m_pcName;
	const NiRTTI* m_pkBaseRTTI;

	const char* GetName() const { return m_pcName; }
	const NiRTTI* GetBase() const { return m_pkBaseRTTI; }

	bool IsKindOf(const NiRTTI* const apRTTI) const {
		for (const NiRTTI* i = this; i; i = i->GetBase()) {
			if (i == apRTTI)
				return true;
		}
		return false;
	}

	template <typename T_RTTI>
	bool IsKindOf() const {
		return IsKindOf(&T_RTTI::ms_RTTI);
	}

	bool IsExactKindOf(const NiRTTI* const apRTTI) const {
		return this == apRTTI;
	}

	template <typename T_RTTI>
	bool IsExactKindOf() const {
		return IsExactKindOf(&T_RTTI::ms_RTTI);
	}
};

ASSERT_SIZE(NiRTTI, 0x8);

#define NiImplementRootRTTI(rootclassname) \
    NiRTTI rootclassname::ms_RTTI(#rootclassname, 0);

#define NiImplementRTTI(classname, baseclassname) \
    static inline const NiRTTI ms_RTTI = NiRTTI(#classname, baseclassname##::ms_RTTI);

#define NiImplementGetRTTI(classname) \
	inline const NiRTTI* _GetRTTI() {return &classname##::ms_RTTI;}

#define NiNewRTTI(classname, baseclassname) \
	NiImplementRTTI(classname, baseclassname) \
	NiImplementGetRTTI(classname)

#define NIRTTI_ADDRESS(address) \
	static constexpr AddressPtr<NiRTTI, address> const ms_RTTI;