#pragma once

#include "NiTSet.hpp"

template <class T_Data> class NiTPrimitiveSet : public NiTSet<T_Data, NiTMallocInterface<T_Data>> {
public:
	NiTPrimitiveSet(uint32_t auiInitialSize = 0) : NiTSet<T_Data, NiTMallocInterface<T_Data>>(auiInitialSize) {};
};