#include "netimmerse.h"

// GAME - 0xA59D30
NiProperty* NiAVObject::GetProperty(uint32_t auiType) const {
	return ThisCall<NiProperty*>(0xA59D30, this, auiType);
}
