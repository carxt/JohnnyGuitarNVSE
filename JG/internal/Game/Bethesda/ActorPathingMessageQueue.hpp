#pragma once

#include "Gamebryo/NiRefObject.hpp"
#include "ActorPathingMessage.hpp"
#include "BSTCommonLLMessageQueue.hpp"

NiSmartPointer(ActorPathingMessageQueue);

class ActorPathingMessageQueue : public BSTCommonLLMessageQueue<ActorPathingMessage>, public NiRefObject {
public:
};

ASSERT_SIZE(ActorPathingMessageQueue, 0x1C);