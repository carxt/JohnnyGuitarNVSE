#pragma once

class NiProcessorAffinity {
public:
	uint32_t m_eIdealProcessor;
	uint32_t m_uiAffinityMask;
};

ASSERT_SIZE(NiProcessorAffinity, 0x8);