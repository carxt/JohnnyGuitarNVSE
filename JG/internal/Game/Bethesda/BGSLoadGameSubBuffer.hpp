#pragma once

#include "BGSSaveLoadBuffer.hpp"

class TESForm;
class BGSSaveFormBuffer;
class BGSLoadFormBuffer;

class BGSLoadGameSubBuffer {
public:
	BGSLoadGameSubBuffer() = default;
	~BGSLoadGameSubBuffer() = default;

	BGSSaveLoadBuffer kBuffer;

	BGSLoadFormBuffer* CreateLoadFormBuffer(TESForm* apForm);

	void CopyBuffer(BGSSaveFormBuffer* apBuffer);
};

ASSERT_SIZE(BGSLoadGameSubBuffer, 0x4);