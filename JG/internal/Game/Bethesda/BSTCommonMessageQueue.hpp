#pragma once

#include "BSTMessageQueue.hpp"
#include "BSNonReentrantSpinLock.hpp"

template <class T> 
class BSTCommonMessageQueue : public BSTMessageQueue<T> {
public:
	BSTCommonMessageQueue();
	~BSTCommonMessageQueue() override;

	BSNonReentrantSpinLock kLock;

	bool Push(const T& arMessage) override;
	bool TryPush(const T& arMessage) override;
	bool Pop(T& arMessage) override;
	bool TryPop(T& arMessage) override;
	bool DoTryPush(const T& arMessage) override;
	bool DoTryPop(T& arMessage) override;
};

#include "BSTCommonMessageQueue.inl"

ASSERT_SIZE(BSTCommonMessageQueue<uint32_t>, 0x8);