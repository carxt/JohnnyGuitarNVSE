#pragma once

#include "LockFreeMap.hpp"
#include "Gamebryo/NiSmartPointer.hpp"
#include "BSTask.hpp"

template <typename T>
class BSTaskManagerIterator : public LockFreeMap<T, NiPointer<BSTask<T>>>::LockFreeMapIterator {
public:
};

ASSERT_SIZE(BSTaskManagerIterator<int64_t>, 0x20);