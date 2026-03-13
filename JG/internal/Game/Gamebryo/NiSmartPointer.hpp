#pragma once

#include "NiMemObject.hpp"

template <class T>
class SPEC_EMPTY_BASES NiPointer : public NiMemObject {
public:
	// GAME - 0x6694E0
	__forceinline NiPointer() : m_pObject(nullptr) {}

	// GAME - 0x559A40
	__forceinline NiPointer(T* apObject) : m_pObject(apObject) { if (m_pObject) m_pObject->IncRefCount(); }
	__forceinline NiPointer(const NiPointer& arOther) : m_pObject(arOther.m_pObject) { if (m_pObject) m_pObject->IncRefCount(); }
	
	// GAME - 0x45CEC0
	__forceinline ~NiPointer() { if (m_pObject) m_pObject->DecRefCount(); }

	T* m_pObject;

	// GAME - 0x559450
	__forceinline operator T* () const { return m_pObject; }
	__forceinline T& operator*() const { return *m_pObject; }
	__forceinline T* operator->() const { return m_pObject; }

	// GAME - 0xC46270, 0xA5F860
	__forceinline NiPointer<T>& operator =(const NiPointer& arOther) {
		if (m_pObject != arOther.m_pObject) {
			if (m_pObject)
				m_pObject->DecRefCount();
			m_pObject = arOther.m_pObject;
			if (m_pObject)
				m_pObject->IncRefCount();
		}
		return *this;
	}

	// GAME - 0x66B0D0
	__forceinline NiPointer<T>& operator =(T* apObject) {
		if (m_pObject != apObject) {
			if (m_pObject)
				m_pObject->DecRefCount();
			m_pObject = apObject;
			if (m_pObject)
				m_pObject->IncRefCount();
		}
		return *this;
	}

	// GAME - 0x822510
	__forceinline bool operator==(T* apObject) const { return (m_pObject == apObject); }

	__forceinline bool operator==(const NiPointer& ptr) const { return (m_pObject == ptr.m_pObject); }

	// GAME - 0x52AA80
	__forceinline operator bool() const { return m_pObject != nullptr; }
};

#define NiSmartPointer(className) \
    class className; \
    typedef NiPointer<className> className##Ptr;