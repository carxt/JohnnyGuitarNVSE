#include "NiRenderer.hpp"
#include "NiDX9Renderer.hpp"
#include "NiCamera.hpp"
#include "NiAccumulator.hpp"

#define LOCK_RENDERER_ON_PRECACHE 1

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

// GAME - 0x4A0E50
bool NiRenderer::GetInsideFrameState() const {
	return m_eFrameState == FRAMESTATE_INSIDE_FRAME || m_eFrameState == FRAMESTATE_INSIDE_OFFSCREEN_FRAME;
}

// GAME - 0x4A0E10
bool NiRenderer::Check_RenderTargetGroupActive(bool abExpectedValue) const {
	return NiRenderer::GetInsideFrameState() && m_bRenderTargetGroupActive == abExpectedValue;
}

// GAME - 0x86BA60
bool NiRenderer::Check_FrameState(const char* apCallingFunction, EFrameState aeExpectedValue) const {
	return m_eFrameState == aeExpectedValue;
}

// GAME - 0x4A0370
void NiRenderer::LockRenderer() {
	ZoneScoped;
	m_kRendererLock.Lock();
}

bool NiRenderer::TryLockRenderer() {
	ZoneScoped;
	return m_kRendererLock.TryLock();
}

// GAME - 0x4A03C0
void NiRenderer::UnlockRenderer() {
	ZoneScoped;
	m_kRendererLock.Unlock();
}

void NiRenderer::LockPrecacheCriticalSection() {
	ZoneScoped;
#if LOCK_RENDERER_ON_PRECACHE
	LockRenderer();
#endif
	m_kPrecacheCriticalSection.Lock();
}

bool NiRenderer::TryLockPrecacheCriticalSection() {
	ZoneScoped;
	if (!TryLockRenderer())
		return false;

	m_kPrecacheCriticalSection.Lock();
	return true;
}

void NiRenderer::UnlockPrecacheCriticalSection() {
	ZoneScoped;
	m_kPrecacheCriticalSection.Unlock();
#if LOCK_RENDERER_ON_PRECACHE
	UnlockRenderer();
#endif
}

void NiRenderer::LockSourceDataCriticalSection() {
	ZoneScoped;
	m_kSourceDataCriticalSection.Lock();
}

bool NiRenderer::TryLockSourceDataCriticalSection() {
	ZoneScoped;
	return m_kSourceDataCriticalSection.TryLock();
}

void NiRenderer::UnlockSourceDataCriticalSection() {
	ZoneScoped;
	m_kSourceDataCriticalSection.Unlock();
}

bool NiRenderer::BeginFrame() {
	if (!Check_FrameState("BeginFrame", FRAMESTATE_OUTSIDE_FRAME))
		return false;

	if (!static_cast<NiDX9Renderer*>(this)->Do_BeginFrame())
		return false;

	m_eFrameState = FRAMESTATE_INSIDE_FRAME;
	return true;
}

// GAME - 0x86BA10
bool NiRenderer::BeginOffScreenFrame() {
	if (!Check_FrameState("BeginOffScreenFrame", FRAMESTATE_OUTSIDE_FRAME))
		return false;

	if (!static_cast<NiDX9Renderer*>(this)->Do_BeginFrame())
		return false;

	m_eFrameState = FRAMESTATE_INSIDE_OFFSCREEN_FRAME;
	return true;
}

bool NiRenderer::EndOffScreenFrame() {
	if (!Check_FrameState("EndOffScreenFrame", FRAMESTATE_INSIDE_OFFSCREEN_FRAME))
		return false;

	if (!static_cast<NiDX9Renderer*>(this)->Do_EndFrame())
		return false;

	m_eFrameState = FRAMESTATE_OUTSIDE_FRAME;
	return true;
}

bool NiRenderer::EndFrame() {
	if (!Check_FrameState("EndFrame", FRAMESTATE_INSIDE_FRAME))
		return false;

	if (!static_cast<NiDX9Renderer*>(this)->Do_EndFrame())
		return false;

	m_eFrameState = FRAMESTATE_WAITING_FOR_DISPLAY;
	return true;
}

bool NiRenderer::DisplayFrame() {
	if (!Check_FrameState("DisplayFrame", FRAMESTATE_WAITING_FOR_DISPLAY))
		return false;

	if (!static_cast<NiDX9Renderer*>(this)->Do_DisplayFrame())
		return false;

	m_eFrameState = FRAMESTATE_OUTSIDE_FRAME;
	m_uiFrameID++;
	return true;
}

// GAME - 0x4E9BB0
// GECK - 0x531B50
void NiRenderer::SetCameraData(const NiCamera* apCamera) {
	const NiPoint3& kUp = apCamera->GetWorldUpVector();
	const NiPoint3& kRight = apCamera->GetWorldRightVector();
	const NiPoint3& kDir = apCamera->GetWorldDirection();
	SetCameraData(apCamera->GetWorldTranslate(), kDir, kUp, kRight, apCamera->m_kViewFrustum, apCamera->m_kPort);
}

// GAME - 0x4E9C90
// GECK - INLINED
void NiRenderer::SetCameraData(const NiPoint3& arWorldLoc, const NiPoint3& arWorldDir, const NiPoint3& arWorldUp, const NiPoint3& arWorldRight, const NiFrustum& arFrustum, const NiRect<float>& arPort) {
	if (Check_RenderTargetGroupActive(true))
		static_cast<NiDX9Renderer*>(this)->Do_SetCameraData(arWorldLoc, arWorldDir, arWorldUp, arWorldRight, arFrustum, arPort);
}