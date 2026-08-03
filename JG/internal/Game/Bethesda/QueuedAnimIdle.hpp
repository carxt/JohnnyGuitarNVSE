#pragma once

#include "QueuedKF.hpp"
#include "Gamebryo/NiObject.hpp"

class Actor;

NiSmartPointer(QueuedAnimIdle);
NiSmartPointer(AnimIdle);

class QueuedAnimIdle : public QueuedKF {
public:
	QueuedAnimIdle();
	~QueuedAnimIdle();

	TESObjectREFR*	pRequester;
	AnimIdlePtr		spAnimation;
};

ASSERT_SIZE(QueuedAnimIdle, 0x40)