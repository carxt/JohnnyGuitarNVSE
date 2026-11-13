#pragma once

class BSTaskletGroupData {
public:
	virtual ~BSTaskletGroupData();
	virtual void WaitForCompletion(bool abPoll);
	virtual void SetMaxConcurrent(uint32_t auiMaxConcurrent);

	bool bComplete;

	bool IsComplete() const;
};

ASSERT_SIZE(BSTaskletGroupData, 0x8);