#pragma once

#include "SettingCollection.hpp"
#include "BSTCaseInsensitiveStringMap.hpp"

template<class T_Data>
class SettingCollectionMap : public SettingCollection<T_Data> {
public:
	BSTCaseInsensitiveStringMap<T_Data*> kSettingsMap;
};

ASSERT_SIZE(SettingCollection<uint32_t>, 0x10C);