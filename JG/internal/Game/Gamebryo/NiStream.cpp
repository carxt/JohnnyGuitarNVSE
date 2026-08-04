#include "NiStream.hpp"

// GAME - 0xA64900
// GECK - 0x81D570
void NiStream::RegisterLoader(const char* apName, void* apFunc) {
#if GAME
	CdeclCall(0xA64900, apName, apFunc);
#else
	CdeclCall(0x81D570, apName, apFunc);
#endif
}

// GAME - 0xA66150
// GECK - 0x81ED80
NiStream* NiStream::Create(NiStream* apThis) {
#if GAME
	return ThisCall<NiStream*>(0xA66150, apThis);
#else
	return ThisCall<NiStream*>(0x81ED80, apThis);
#endif
}

// GAME - 0x43B200
NiObject* NiStream::GetObjectAt(uint32_t auiIndex) {
	return m_kTopObjects.GetAt(auiIndex);
}

// GAME - 0x43B1E0
uint32_t NiStream::GetObjectCount() const {
	return m_kTopObjects.GetSize();
}

// GAME - 0xA66370
// GECK - 0x81EFA0
void NiStream::InsertObject(NiObject* apObject) {
#ifdef GAME
	ThisCall(0xA66370, this, apObject);
#else
	ThisCall(0x81EFA0, this, apObject);
#endif
}

// GAME - 0xA645B0
// GECK - 0x81D220
void NiStream::ReadLinkID() {
#ifdef GAME
	ThisCall(0xA645B0, this);
#else
	ThisCall(0x81D220, this);
#endif
}

// GAME - 0xA64670
uint32_t NiStream::ReadMultipleLinkIDs() {
    uint32_t uiCount;
    NiStreamLoadBinary(*this, uiCount);
	_MESSAGE("\n%s | Reading %i Link IDs", m_acFileName, uiCount);
    m_kLinkIDBlocks.Add(uiCount);
    for (uint32_t i = 0; i < uiCount; i++) {
        ReadLinkID();
	}
    return uiCount;
}

// GAME - 0xA63430
// GECK - 0x81C060
NiObject* NiStream::GetObjectFromLinkID() {
#ifdef GAME
	return ThisCall<NiObject*>(0xA63430, this);
#else
	return ThisCall<NiObject*>(0x81C060, this);
#endif
}

// GAME - 0xA641F0
// GECK - 0x81CE50
void NiStream::SaveFixedString(const NiFixedString& arStr) {
#ifdef GAME
	ThisCall(0xA641F0, this, &arStr);
#else
	ThisCall(0x81CE50, this, &arStr);
#endif
}

// GAME - 0xA64DF0
// GECK - 0x81DA60
void NiStream::LoadFixedString(NiFixedString& arStr) {
#ifdef GAME
	ThisCall(0xA64DF0, this, &arStr);
#else
	ThisCall(0x81DA60, this, &arStr);
#endif
}

uint32_t NiStream::GetVersion(uint32_t auiMajor, uint32_t auiMinor, uint32_t auiPatch, uint32_t auiInternal) {
    return (auiMajor << 24) | (auiMinor << 16) | (auiPatch << 8) | auiInternal;
}