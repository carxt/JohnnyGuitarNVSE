#pragma once

#include "NiTArray.hpp"
#include "NiTMallocInterface.hpp"

template <class T_Data>
class NiTPrimitiveArray : public NiTArray<T_Data, NiTMallocInterface<T_Data>> {
public:
	NiTPrimitiveArray(uint32_t auiMaxSize = 0, uint32_t auiGrowBy = 1) : NiTArray<T_Data, NiTMallocInterface<T_Data>>(auiMaxSize, auiGrowBy) {};
};

ASSERT_SIZE(NiTPrimitiveArray<void*>, 0x10);

typedef NiTPrimitiveArray<const char*> NiViewerStringsArray;