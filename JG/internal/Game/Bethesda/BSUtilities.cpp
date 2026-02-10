#include "BSUtilities.hpp"

// GAME - 0x4ADE00
// GECK - N/A
NiAVObject* BSUtilities::GetObjectByName(const NiAVObject* apScene, const NiFixedString& arName) {
	return GetObjectByName(apScene, arName, true);
}

// GAME - 0xC4B470
// GECK - 0x9D2160
NiAVObject* BSUtilities::GetObjectByName(const NiAVObject* apScene, const NiFixedString& arName, bool abTestScenegraph) {
#ifdef GAME
	return CdeclCall<NiAVObject*>(0xC4B470, apScene, &arName, abTestScenegraph);
#else
	return CdeclCall<NiAVObject*>(0x9D2160, apScene, &arName, abTestScenegraph);
#endif
}
