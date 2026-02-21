#pragma once

enum BS_TASK_STATE {
	BS_TASK_STATE_PENDING			= 0,
	BS_TASK_STATE_QUEUED			= 1,
	BS_TASK_STATE_MOVING			= 2,
	BS_TASK_STATE_RUNNING			= 3,
	BS_TASK_STATE_FINISHED			= 4,
	BS_TASK_STATE_COMPLETED			= 5,
	BS_TASK_STATE_CANCELED			= 6,
	BS_TASK_STATE_POST_PROCESSING	= 7,
};

template <typename T>
class BSTask {
public:
	BSTask();
	virtual ~BSTask();
	virtual void Run() = 0;
	virtual void Finish() = 0;
	virtual void Cancel(BS_TASK_STATE aeState, BSTask<T>* apParent);
	virtual bool GetDescription(const char* apDescription, size_t aiBufferSize);

	alignas(alignof(T)) uint32_t	uiRefCount;
	BS_TASK_STATE					eState;
#pragma pack(push, 4)
	mutable T						iKey;
#pragma pack(pop)

	static constexpr AddressPtr<uint32_t, 0x11C3B38> uiTotalTaskCount;

	// GAME - 0x92C870
	void IncRefCount() {
		InterlockedIncrement(&uiRefCount);
	}

	// GAME - 0x44DD60
	// GECK - 0x4BBB60
	void DecRefCount() {
		if (!InterlockedDecrement(&uiRefCount))
			delete this;
	}

	// GAME - 0x449190
	bool SwitchState(BS_TASK_STATE aeCurrentState, BS_TASK_STATE aeNewState) {
		return InterlockedCompareExchange(reinterpret_cast<LONG*>(&eState), LONG(aeNewState), LONG(aeCurrentState)) == aeCurrentState;
	}

	bool IsCancelled() const {
		return eState == BS_TASK_STATE_CANCELED;
	}

	bool IsPending() const {
		return eState == BS_TASK_STATE_PENDING;
	}

	// GAME - 0x44E0D0
	T GetKey() const {
		return iKey;
	}

	uint8_t GetFileIndexFromKey() const {
		return (iKey >> 56) & 0xFF;
	}
};

ASSERT_SIZE(BSTask<int64_t>, 0x18);

#include "BSTask.inl"