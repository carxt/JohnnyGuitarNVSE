#pragma once

#include "BSTaskletData.hpp"

class BSTasklet {
public:
	BSTasklet();
	BSTasklet(BSTaskletData* apData);
	virtual ~BSTasklet();

	BSTaskletData* pData;

	BSTaskletData* GetTaskData() const;
	void SetTaskData(BSTaskletData* apData);
};

ASSERT_SIZE(BSTasklet, 0x8);