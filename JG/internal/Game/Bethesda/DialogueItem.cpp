#include "DialogueItem.hpp"

// GAME - 0x83C7B0
bool DialogueItem::FirstResponse() {
    return ThisCall<bool>(0x83C7B0, this);
}

// GAME - 0x83C7E0
bool DialogueItem::NextResponse() {
    return ThisCall<bool>(0x83C7E0, this);
}

// GAME - 0x83C820
DialogueResponse* DialogueItem::GetCurrentItem() const {
    return ThisCall<DialogueResponse*>(0x83C820, this);
}
