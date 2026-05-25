#pragma once

template <class T>
class BSTMessageQueue {
public:
	BSTMessageQueue() {};
	virtual		 ~BSTMessageQueue() {};
	virtual bool Push(const T& arMessage) = 0;
	virtual bool TryPush(const T& arMessage) = 0;
	virtual bool Pop(T& arMessage) = 0;
	virtual bool TryPop(T& arMessage) = 0;
	virtual bool DoTryPush(const T& arMessage) = 0;
	virtual bool DoTryPop(T& arMessage) = 0;
};

ASSERT_SIZE(BSTMessageQueue<uint32_t>, 0x4);