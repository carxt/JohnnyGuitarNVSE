#pragma once

#include "NiMemObject.hpp"
#include "NiSmartPointer.hpp"

NiSmartPointer(NiRefObject);

class SPEC_EMPTY_BASES NiRefObject : public NiMemObject {
public:
	NiRefObject();

	virtual			~NiRefObject(); // 00 | Destructor
	virtual void	DeleteThis();   // 01 | Deletes the object

	uint32_t m_uiRefCount;

	// GAME - 0x40F6E0
	inline void IncRefCount() {
		InterlockedIncrement(&m_uiRefCount);
	}

	// GAME - 0x401970
	// GECK - 0x4011B0
	inline void DecRefCount() {
		if (!InterlockedDecrement(&m_uiRefCount))
			DeleteThis();
	}
};

ASSERT_SIZE(NiRefObject, 0x8);