#pragma once

#include "ContainerItemExtra.hpp"

class TESBoundObject;

class ContainerObject {
public:
	int32_t				iCount;
	TESBoundObject*		pObject;
	ContainerItemExtra* pItemExtra;
};

ASSERT_SIZE(ContainerObject, 0xC);