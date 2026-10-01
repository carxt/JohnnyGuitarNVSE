#include "MenuTopic.hpp"

// GAME - 0x83E170
DialogueResponse* MenuTopic::GetCurrentResponse() const {
    return ThisCall<DialogueResponse*>(0x83E170, this);
}

// GAME - 0x83E110
bool MenuTopic::NextResponse() {
    return ThisCall<bool>(0x83E110, this);
}
