#pragma once

#include "NiTPointerListBase.hpp"
#include "NiTDefaultAllocator.hpp"

template <class T>
class NiTList : public NiTPointerListBase<NiTDefaultAllocator<NiTListItem<T>>, T> {
};