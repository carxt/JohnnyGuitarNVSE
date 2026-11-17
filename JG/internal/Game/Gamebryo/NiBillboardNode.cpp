#include "NiBillboardNode.hpp"

NiBillboardNode::FaceMode NiBillboardNode::GetMode() const {
	return static_cast<FaceMode>(m_usFlags.eFaceMode);
}

void NiBillboardNode::SetMode(FaceMode aeMode) {
	m_usFlags.eFaceMode = aeMode;
}

// GAME - 0xA7DE40
// GECK - 0x82F170
void NiBillboardNode::RotateToCamera(NiCamera* apCamera) {
#ifdef GAME
	ThisCall(0xA7DE40, this, apCamera);
#else
	ThisCall(0x82F170, this, apCamera);
#endif
}
