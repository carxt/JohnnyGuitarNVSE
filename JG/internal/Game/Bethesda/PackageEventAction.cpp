#include "PackageEventAction.hpp"

// GAME - 0x67DA40
// GECK - 0x49CBF0
PackageEventAction::PackageEventAction() {
#ifdef GAME
	ThisCall(0x67DA40, this);
#else
	ThisCall(0x49CBF0, this);
#endif
}

// GAME - 0x67DA80
// GECK - 0x49CC70
PackageEventAction::~PackageEventAction() {
#ifdef GAME
	ThisCall(0x67DA80, this);
#else
	ThisCall(0x49CC70, this);
#endif
}