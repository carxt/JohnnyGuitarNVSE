#include "GameSettingCollection.hpp"

// GAME - 0x4F8A90
bool GameSettingCollection::GetSetting(const char* apName, Setting* apSettingOut) {
    return kSettingsMap.GetAt(apName, apSettingOut);
}
