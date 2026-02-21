#pragma once

#include "SettingCollection.hpp"
#include "BSSimpleList.hpp"

template<class T>
class SettingCollectionList : public SettingCollection<T> {
public:
	BSSimpleList<T*>	kSettings;

	BSSimpleList<T*>& GetSettings() {
		return kSettings;
	}
};

ASSERT_SIZE(SettingCollectionList<uint32_t>, 0x114);