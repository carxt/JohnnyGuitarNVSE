#pragma once

#include "NiTLargeArray.hpp"
#include "NiTNewInterface.hpp"

template <class T_Data>
class NiTLargeObjectArray : public NiTLargeArray<T_Data, NiTNewInterface<T_Data>> {
public:
	NiTLargeObjectArray(uint32_t auiMaxSize = 0, uint32_t auiGrowBy = 1) : NiTLargeArray<T_Data, NiTNewInterface<T_Data>>(auiMaxSize, auiGrowBy) {};
};

ASSERT_SIZE(NiTLargeObjectArray<void*>, 0x18);