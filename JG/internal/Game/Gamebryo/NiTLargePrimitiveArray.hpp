#pragma once

#include "NiTLargeArray.hpp"
#include "NiTMallocInterface.hpp"

template <class T_Data>
class NiTLargePrimitiveArray : public NiTLargeArray<T_Data, NiTMallocInterface<T_Data>> {
public:
	NiTLargePrimitiveArray(uint32_t auiMaxSize = 0, uint32_t auiGrowBy = 1) : NiTLargeArray<T_Data, NiTMallocInterface<T_Data>>(auiMaxSize, auiGrowBy) {};
};

ASSERT_SIZE(NiTLargePrimitiveArray<void*>, 0x18);