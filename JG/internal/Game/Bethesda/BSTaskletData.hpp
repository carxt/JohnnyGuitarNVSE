#pragma once

class BSTaskletData {
public:
	BSTaskletData();
	virtual ~BSTaskletData();
	virtual bool OnStartup();
	virtual void Process();
	virtual void OnComplete();

	bool bYielding;

	void TaskYield();
};

ASSERT_SIZE(BSTaskletData, 0x8);