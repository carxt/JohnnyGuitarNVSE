#pragma once

#include "BSTaskletGroupData.hpp"

class BSTasklet;

class BSTaskletGroup {
public:
	BSTaskletGroup();
	BSTaskletGroup(BSTaskletGroupData* apData);
	~BSTaskletGroup();

	BSTaskletGroupData* pData;

	BSTaskletGroupData* GetGroupData() const;
	void SetGroupData(BSTaskletGroupData* apData);

	bool Open();
	bool AttachTask(BSTasklet& arTask, bool abLastTask);
	bool Close();
	void WaitForCompletion(bool abPoll);
	void SetMaxConcurrent(uint32_t auiMaxConcurrent);
};

ASSERT_SIZE(BSTaskletGroup, 0x4);