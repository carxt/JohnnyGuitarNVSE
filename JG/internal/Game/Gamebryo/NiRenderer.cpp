#include "NiRenderer.hpp"

NiRenderer* NiRenderer::GetRenderer() {
#ifdef GAME
	return *reinterpret_cast<NiRenderer**>(0x11F4748);
#else
	return *reinterpret_cast<NiRenderer**>(0xF20148);
#endif
}

NiAccumulator* NiRenderer::GetSorter() const {
	return m_spAccum;
}

void NiRenderer::SetSorter(NiAccumulator* apAccumulator) {
	m_spAccum = apAccumulator;
}

// GAME - 0x4E9530
NiRenderer::FrameState NiRenderer::GetFrameState() const {
	return m_eFrameState;
}

// GAME - 0x4A0E50
bool NiRenderer::GetInsideFrameState() const {
#ifdef GAME
	return ThisCall<bool>(0x4A0E50, this);
#else
	return m_eFrameState == FrameState::INSIDE_FRAME || m_eFrameState == FrameState::INSIDE_OFFSCREEN_FRAME;
#endif
}

// GAME - 0x4A0370
void NiRenderer::LockRenderer() {
#ifdef GAME
	ThisCall(0x4A0370, this);
#else
	m_kRendererLock.Lock();
#endif
}

// GAME - 0x4A03C0
void NiRenderer::UnlockRenderer() {
#ifdef GAME
	ThisCall(0x4A03C0, this);
#else
	m_kRendererLock.Unlock();
#endif
}

// GAME - 0x4E9BB0
// GECK - 0x531B50
void NiRenderer::SetCameraData(const NiCamera* apCamera) {
#ifdef GAME
	ThisCall(0x4E9BB0, this, apCamera);
#else
	ThisCall(0x531B50, this, apCamera);
#endif
}

// GAME - 0x4E9C90
// GECK - INLINED
void NiRenderer::SetCameraData(const NiPoint3& arWorldLoc, const NiPoint3& arWorldDir, const NiPoint3& arWorldUp, const NiPoint3& arWorldRight, const NiFrustum& arFrustum, const NiRect<float>& arPort) {
#ifdef GAME
	ThisCall(0x4E9BB0, this, &arWorldLoc, &arWorldDir, &arWorldUp, &arWorldRight, &arFrustum, &arPort);
#endif
}