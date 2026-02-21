#pragma once

#include "NiTPointerListBase.hpp"
#include "NiTPointerAllocator.hpp"

template <class T_Data>
class NiTPointerList : public NiTPointerListBase<NiTPointerAllocator<size_t>, T_Data> {
};

ASSERT_SIZE(NiTPointerList<void*>, 0xC);