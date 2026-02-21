#pragma once

#include "NiTArray.hpp"
#include "NiTNewInterface.hpp"

template <class T_Data>
class NiTObjectArray : public NiTArray<T_Data, NiTNewInterface<T_Data>> {
public:
	NiTObjectArray(uint32_t auiMaxSize = 0, uint32_t auiGrowBy = 1) : NiTArray<T_Data, NiTNewInterface<T_Data>>(auiMaxSize, auiGrowBy) {};
};

ASSERT_SIZE(NiTObjectArray<void*>, 0x10);