#pragma once

#include "Gamebryo/NiPoint3.hpp"
#include "Gamebryo/NiSmartPointer.hpp"
#include "GridArray.hpp"

class BSRenderedTexture;
class TESObjectCELL;

struct GridCell {
	TESObjectCELL* pCell;
};

class GridCellArray : public GridArray {
public:
	int32_t							iDimension;
	GridCell*						pGridCells;
	NiPoint3						kWorldCenter;
	bool							bLandAttached;
	NiPointer<BSRenderedTexture>	spShadowMask;

	GridCell* GetCell(int32_t aiX, int32_t aiY);
};

ASSERT_SIZE(GridCellArray, 0x28);