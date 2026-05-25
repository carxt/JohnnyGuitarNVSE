#pragma once

#include "Gamebryo/NiCullingProcess.hpp"
#include "Gamebryo/NiAccumulator.hpp"
#include "BSEnums.hpp"

class BSCompoundFrustum;
class NiAccumulator;

class BSCullingProcess : public NiCullingProcess {
public:
	BS_CULLING_TYPE					eCullMode;
	BS_CULLING_TYPE					eTypeStack[10];
	uint32_t						uiStackIndex;
	BSCompoundFrustum*				pCompoundFrustum;
	NiPointer<NiAccumulator>		spAccumulator;

	NIRTTI_ADDRESS(0x12030A8);

	void SetCullMode(BS_CULLING_TYPE aeType);
	void PushCullMode(BS_CULLING_TYPE aeType);
	void PopCullMode();

	void SetAccumulator(NiAccumulator* apAccumulator);
	NiAccumulator* GetAccumulator() const;
};

ASSERT_SIZE(BSCullingProcess, 0xC8)