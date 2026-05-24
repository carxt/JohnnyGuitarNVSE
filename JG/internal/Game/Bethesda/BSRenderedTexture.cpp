#include "BSRenderedTexture.hpp"

// GAME - 0xB6B260
// GECK - 0x902710
NiRenderTargetGroup* BSRenderedTexture::GetGroup() const {
#ifdef GAME
	return ThisCall<NiRenderTargetGroup*>(0xB6B260, this);
#else
	return ThisCall<NiRenderTargetGroup*>(0x902710, this);
#endif
}

// GAME - 0x4E9510
bool BSRenderedTexture::IsOutsideFrame() {
	return CdeclCall<bool>(0x4E9510);
}

// GAME - 0xB6B890
// GECK - 0x902C60
void BSRenderedTexture::Start(uint32_t auiClearMode, NiRenderTargetGroup* apGroup) {
#ifdef GAME
	CdeclCall(0xB6B890, auiClearMode, apGroup);
#else
	CdeclCall(0x902C60, auiClearMode, apGroup);
#endif
}

// GAME - 0xB6B8D0
// GECK - 0x902CA0
void BSRenderedTexture::StartOffscreen(uint32_t auiClearMode, NiRenderTargetGroup* apGroup) {
#ifdef GAME
	CdeclCall(0xB6B8D0, auiClearMode, apGroup);
#else
	CdeclCall(0x902CA0, auiClearMode, apGroup);
#endif
}

// GAME - 0xB6B730
// GECK - 0x902B00
void BSRenderedTexture::Stop() {
#ifdef GAME
	CdeclCall(0xB6B730);
#else
	CdeclCall(0x902B00);
#endif
}

// GAME - 0xB6B790
// GECK - 0x902B60
void BSRenderedTexture::StopOffscreen() {
#ifdef GAME
	CdeclCall(0xB6B790);
#else
	CdeclCall(0x902B60);
#endif
}

// GAME - 0xB6B7D0
// GECK - 0x902BA0
void BSRenderedTexture::Begin(NiRenderTargetGroup* apGroup, uint32_t uiClearMode) {
#ifdef GAME
	CdeclCall(0xB6B7D0, apGroup, uiClearMode);
#else
	CdeclCall(0x902BA0, apGroup, uiClearMode);
#endif
}

// GAME - 0x54EDE0
// GECK - None
void BSRenderedTexture::BeginTexture(BSRenderedTexture* apTexture, uint32_t auiClearMode) {
	CdeclCall(0x54EDE0, apTexture, auiClearMode);
}

// GAME - 0xB6B840
// GECK - 0x902C10
void BSRenderedTexture::End() {
#ifdef GAME
	CdeclCall(0xB6B840);
#else
	CdeclCall(0x902C10);
#endif
}

// GAME - 0xB6B6C0
// GECK - 0x902A90
void BSRenderedTexture::EndAll() {
#ifdef GAME
	CdeclCall(0xB6B6C0);
#else
	CdeclCall(0x902A90);
#endif
}