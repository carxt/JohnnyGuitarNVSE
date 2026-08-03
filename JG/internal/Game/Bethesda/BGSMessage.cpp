#include "BGSMessage.hpp"

// GAME - 0x590D00
bool BGSMessage::GetIsMessageBox() const {
    return uiMessageFlags.bMessageBox;
}

// GAME - 0x590E80
void BGSMessage::SetIsMessageBox(bool abVal) {
    uiMessageFlags.bMessageBox = abVal;
}

// GAME - 0x590ED0
bool BGSMessage::GetAutoDisplay() const {
    return uiMessageFlags.bAutoDisplay;
}

// GAME - 0x590EF0
void BGSMessage::SetAutoDisplay(bool abVal) {
    uiMessageFlags.bAutoDisplay = abVal;
}

// GAME - 0x55B980
BGSMenuIcon* BGSMessage::GetIcon() const {
    return pIcon;
}

// GAME - 0x86CF00
void BGSMessage::SetIcon(BGSMenuIcon* apIcon) {
    pIcon = apIcon;
}

// GAME - 0x436AA0
const BSSimpleList<BGSMessage::Button*>* BGSMessage::GetButtonList() const {
    return &kButtons;
}

// GAME - 0x436AA0
BSSimpleList<BGSMessage::Button*>* BGSMessage::GetButtonList() {
    return &kButtons;
}

// GAME - 0x5911D0
void BGSMessage::AddButton(Button* apButton) {
    ThisCall(0x5911D0, this, apButton);
}

// GAME - 0x639B40
uint32_t BGSMessage::GetDisplayTime() const {
    return uiDisplayTime;
}

// GAME - 0x409480
void BGSMessage::SetDisplayTime(uint32_t auiTime) {
    uiDisplayTime = auiTime;
}