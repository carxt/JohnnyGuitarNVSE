#include "DialogueItem.hpp"

// GAME - 0x83C7B0
bool DialogueItem::FirstResponse() {
    pCurrentResponse = &kResponses;
    return pCurrentResponse->GetItem() != nullptr;
}

// GAME - 0x83C7E0
bool DialogueItem::NextResponse() {
    if (pCurrentResponse)
        pCurrentResponse = pCurrentResponse->GetNext();

    return pCurrentResponse != nullptr;
}

// GAME - 0x83C820
DialogueResponse* DialogueItem::GetCurrentItem() const {
    if (pCurrentResponse)
        return pCurrentResponse->GetItem();
    return nullptr;
}
