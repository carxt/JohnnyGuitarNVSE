#pragma once

#include "BSEnums.hpp"

class AutoMemContext {
public:
	AutoMemContext(MEM_CONTEXT aeMemContext, bool abOverridable = true, const char* apFile = nullptr, uint32_t auiLine = 0);
	~AutoMemContext();

private:
	MEM_CONTEXT eOldMemContext;

	void Enter(MEM_CONTEXT aeMemContext, bool abOverridable, const char* apFile, uint32_t auiLine);

	void Leave() const;
};

ASSERT_SIZE(AutoMemContext, 0x4);

#define AUTO_MEM_CONTEXT(aeMemContext) AutoMemContext _HELPER_COMBINE(context, __LINE__)(aeMemContext, true, __FILE__, __LINE__);
MEM_CONTEXT GetMemContext();
void SetMemContext(MEM_CONTEXT aeMemContext);