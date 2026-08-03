#pragma once

#include "BSMemObject.hpp"
#include "ThreadSafeStructures.hpp"

class InterfacedClass {
public:
	InterfacedClass() {};
	virtual			~InterfacedClass() {};
	virtual void*	AllocateInterface(uint32_t auiThread) = 0;
};

ASSERT_SIZE(InterfacedClass, 0x4);