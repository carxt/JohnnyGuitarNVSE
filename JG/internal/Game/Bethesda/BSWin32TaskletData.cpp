#include "BSWin32TaskletData.hpp"

BSWin32TaskletData::BSWin32TaskletData() {
	pGroupData = nullptr;
	bRunOnStartup = true;
}

BSWin32TaskletData::~BSWin32TaskletData() {
	kTaskDataLock.Lock();
	if (pGroupData)
		pGroupData = nullptr;
	kTaskDataLock.Unlock();
}
