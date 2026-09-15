#include "DialoguePackage.hpp"

// GAME - 0x9EE040
MobileObject* DialoguePackage::GetActorStartedConversation() const {
    return pActor;
}

// GAME - 0x8D80E0
MobileObject* DialoguePackage::GetTargetOfConversation() const {
    return pTargetActor;
}

// GAME - 0x4036B0
MobileObject* DialoguePackage::GetTalkingActivator() const {
    return pTalkingActivator;
}
