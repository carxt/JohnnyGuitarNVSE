#include "GridCellArray.hpp"

// GAME - 0x4BA490
// GECK - 0x5296F0
GridCell* GridCellArray::GetCell(int32_t aiX, int32_t aiY) {
#ifdef GAME
	return ThisCall<GridCell*>(0x4BA490, this, aiX, aiY);
#else
	return ThisCall<GridCell*>(0x5296F0, this, aiX, aiY);
#endif
}