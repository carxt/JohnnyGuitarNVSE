#include "MenuTopic.hpp"

// GAME - 0x83E170
DialogueResponse* MenuTopic::GetCurrentResponse() const {
    if (pFirstResponse)
        return pFirstResponse->GetItem();
    return nullptr;
}

// GAME - 0x83E110
bool MenuTopic::NextResponse() {
    if (pFirstResponse)
        pFirstResponse = pFirstResponse->GetNext();
    return pFirstResponse && pFirstResponse->GetItem() != nullptr;
}
