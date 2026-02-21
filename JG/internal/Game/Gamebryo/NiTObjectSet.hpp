#pragma once

#include "NiTSet.hpp"

template <class T_Data> class NiTObjectSet : public NiTSet<T_Data, NiTNewInterface<T_Data>> {
public:
	NiTObjectSet(uint32_t auiInitialSize = 0) : NiTSet<T_Data, NiTNewInterface<T_Data>>(auiInitialSize) {};
};