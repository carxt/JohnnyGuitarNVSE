#pragma once

class BGSSaveLoadBuffer {
public:
	BGSSaveLoadBuffer() = default;
	~BGSSaveLoadBuffer() = default;

	char* pBuffer;
};

ASSERT_SIZE(BGSSaveLoadBuffer, 0x4);