#include "bhkThreadMemoryRouter.hpp"

// GAME - 0xC80130
// GECK - 0xA2C100
void bhkThreadMemoryRouter::Init(bhkThreadMemoryRouter& arRouter) {
#ifdef GAME
	CdeclCall(0xC80130, &arRouter);
#else
	CdeclCall(0xA2C100, &arRouter);
#endif
}

// GAME - 0xC80240
// GECK - 0xA2C210
void bhkThreadMemoryRouter::Quit(bhkThreadMemoryRouter& arRouter) {
#ifdef GAME
	CdeclCall(0xC80240, &arRouter);
#else
	CdeclCall(0xA2C210, &arRouter);
#endif
}
