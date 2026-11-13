#pragma once

#include "BSTaskletData.hpp"
#include "BSNonReentrantSpinLock.hpp"

class BSWin32TaskletGroupData;

class BSWin32TaskletData : public BSTaskletData {
public:
	BSWin32TaskletData();
	virtual ~BSWin32TaskletData();

	BSWin32TaskletGroupData*	pGroupData;
	bool						bRunOnStartup;
	BSNonReentrantSpinLock		kTaskDataLock;
	BSWin32TaskletData*			pLink;
};

ASSERT_SIZE(BSWin32TaskletData, 0x18);