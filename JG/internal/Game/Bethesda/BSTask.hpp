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
	virtual void Run();
	virtual void Finish();
	virtual void Cancel(BS_TASK_STATE aeState, BSTask<T>* apParent);
	virtual bool GetDescription(const char* apDescription, uint32_t auiBufferSize);

	alignas(alignof(T)) uint32_t	uiRefCount;
	BS_TASK_STATE					eState;
#pragma pack(push, 4)
	mutable T						iKey;
#pragma pack(pop)

#ifdef GAME
	static constexpr AddressPtr<uint32_t, 0x11C3B38> uiTotalTaskCount;
#else
	static constexpr AddressPtr<uint32_t, 0xEDCDE8> uiTotalTaskCount;
#endif

	void IncRefCount();
	void DecRefCount();

	bool SwitchState(BS_TASK_STATE aeCurrentState, BS_TASK_STATE aeNewState);

	bool IsPending() const;

	bool IsCompleted() const;

	bool IsCancelled() const;

	T GetKey() const;

	uint8_t GetFileIndexFromKey() const;
};

ASSERT_SIZE(BSTask<int64_t>, 0x18);

#include "BSTask.inl"