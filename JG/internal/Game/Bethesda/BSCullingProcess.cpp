#include "BSCullingProcess.hpp"

// GAME - 0x4FB0B0
void BSCullingProcess::SetCullMode(BS_CULLING_TYPE aeType) {
	eCullMode = aeType;
}

// GAME - 0xC4F270
void BSCullingProcess::PushCullMode(BS_CULLING_TYPE aeType) {
	eTypeStack[uiStackIndex++] = eCullMode;
	eCullMode = aeType;
}

// GAME - 0xC4F2D0
void BSCullingProcess::PopCullMode() {
	eCullMode = eTypeStack[--uiStackIndex];
}

// GAME - 0x4A0FD0
void BSCullingProcess::SetAccumulator(NiAccumulator* apAccumulator) {
	spAccumulator = apAccumulator;
}

NiAccumulator* BSCullingProcess::GetAccumulator() const {
	return spAccumulator;
}