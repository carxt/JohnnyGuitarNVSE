#include "BSSoundMessage.hpp"

// GAME - 0xAE8650
// GECK - 0x896470
BSSoundMessage::BSSoundMessage() {
#ifdef GAME
	ThisCall(0xAE8650, this);
#else
	ThisCall(0x896470, this);
#endif
}

// GAME - 0xAE86D0
// GECK - 0x8964F0
BSSoundMessage::~BSSoundMessage() {
#ifdef GAME
	ThisCall(0xAE86D0, this);
#else
	ThisCall(0x8964F0, this);
#endif
}

// GAME - 0xAE7990
// GECK - 0x895490
BSSoundMessage& BSSoundMessage::operator=(const BSSoundMessage& arOther) {
#ifdef GAME
	ThisCall(0xAE7990, this, &arOther);
#else
	ThisCall(0x895490, this, &arOther);
#endif
	return *this;
}