#include "NiObject.hpp"

// GAME - 0x6532C0
bool NiObject::IsKindOf(const NiRTTI* const apRTTI) const {
	return GetRTTI()->IsKindOf(apRTTI);
}

// GAME - 0x45BAF0
bool NiObject::IsExactKindOf(const NiRTTI* const apRTTI) const {
	return GetRTTI()->IsExactKindOf(apRTTI);
}

// GAME - 0x45BAD0
bool NiObject::IsExactKindOf(const NiRTTI* const apRTTI, const NiObject* apObject) {
	return apObject && apObject->IsExactKindOf(apRTTI);
}

// GAME - 0xA5D680
// GECK - 0x81B4B0
NiObject* NiObject::Clone() {
#ifdef GAME
	return ThisCall<NiObject*>(0xA5D680, this);
#else
	return ThisCall<NiObject*>(0x81B4B0, this);
#endif
}

// GAME - 0xA5D2C0
// GECK - 0x81B1C0
NiObject* NiObject::CloneObject(NiCloningProcess& arCloneProc) {
#ifdef GAME
	return ThisCall<NiObject*>(0xA5D2C0, this, &arCloneProc);
#else
	return ThisCall<NiObject*>(0x81B1C0, this, &arCloneProc);
#endif
}
