#pragma once

#include "BSEnums.hpp"
#include "Gamebryo/NiTPrimitiveArray.hpp"

class MobileObject;

class ProcessArray {
public:
	NiTPrimitiveArray<MobileObject*>	kMobileObjects;
	uint32_t							uiHeads[PROCESS_LEVEL::COUNT];
	uint32_t							uiTails[PROCESS_LEVEL::COUNT];
	uint32_t							uiNextUpdatePos[PROCESS_LEVEL::COUNT];

	MobileObject* GetItem(uint32_t auiIndex) const;
	uint32_t GetHead(PROCESS_LEVEL aeLevel) const;
	uint32_t GetTail(PROCESS_LEVEL aeLevel) const;
	uint32_t GetSize() const;

	PROCESS_LEVEL GetProcessLevelFromIndex(uint32_t auiIndex) const;

	uint32_t GetIndexFromObject(MobileObject* apObject, PROCESS_LEVEL aeLevel) const;
};

ASSERT_SIZE(ProcessArray, 0x40);