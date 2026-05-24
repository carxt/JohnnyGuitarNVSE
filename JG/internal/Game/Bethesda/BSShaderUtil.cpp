#include "BSShaderUtil.hpp"

// GAME - 0xB6BEE0
// GECK - 0x90A570
void BSShaderUtil::AccumulateScene(const NiCamera* apCamera, NiAVObject* apNode, BSCullingProcess* apCullingProcess) {
#ifdef GAME
	CdeclCall(0xB6BEE0, apCamera, apNode, apCullingProcess);
#else
	CdeclCall(0x90A570, apCamera, apNode, apCullingProcess);
#endif
}

// GAME - 0xB6C0D0
// GECK - 0x90A760
void BSShaderUtil::RenderScene(NiCamera* apCamera, BSShaderAccumulator* apAccumulator) {
#ifdef GAME
	CdeclCall(0xB6C0D0, apCamera, apAccumulator);
#else
	CdeclCall(0x90A760, apCamera, apAccumulator);
#endif
}