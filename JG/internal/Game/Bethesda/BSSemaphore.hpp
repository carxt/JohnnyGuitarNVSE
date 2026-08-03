#pragma once

class BSSemaphore {
public:
	BSSemaphore();
	BSSemaphore(int32_t aiCount);
	BSSemaphore(int32_t aiCount, int32_t aiMaxCount);
	~BSSemaphore();

	volatile int32_t	iCount;
	HANDLE				hSemaphore;
	int32_t				iMaxCount;

	int32_t GetCount() const;

	void Signal();
	void Wait();
	bool Test();
};

ASSERT_SIZE(BSSemaphore, 0xC);