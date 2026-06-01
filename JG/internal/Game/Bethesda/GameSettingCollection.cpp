#include "GameSettingCollection.hpp"

// GAME - 0x4F8A90
bool GameSettingCollection::GetSetting(const char* apName, Setting*& apSettingOut) {
    return ThisCall<bool>(0x4F8A90, this, apName, &apSettingOut);
}
