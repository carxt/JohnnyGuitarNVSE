#include "NiCullingProcess.hpp"

// GAME - 0x41FD00
void NiCullingProcess::SetCamera(const NiCamera* apCamera) {
	m_pkCamera = const_cast<NiCamera*>(apCamera);
}

// GAME - 0x84E3A0
NiCamera* NiCullingProcess::GetCamera() const {
	return m_pkCamera;
}

// GAME - 0xA694A0
// GECK - 0x81A3B0
void NiCullingProcess::SetFrustum(const NiFrustum& arFrustum) {
#ifdef GAME
	ThisCall(0xA694A0, this, &arFrustum);
#else
	ThisCall(0x81A3B0, this, &arFrustum);
#endif
};