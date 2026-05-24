#pragma once

class BSSemaphore {
public:
	BSSemaphore();
	BSSemaphore(uint32_t auiCount);
	BSSemaphore(uint32_t auiCount, uint32_t auiMaxCount);
	~BSSemaphore();

	uint32_t	uiCount;
	HANDLE		hSemaphore;
	uint32_t	uiMaxCount;

	void Signal();
	void Wait();
	bool Test();
};

ASSERT_SIZE(BSSemaphore, 0xC);