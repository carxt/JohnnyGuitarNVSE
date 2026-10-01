#pragma once

class GridArray {
public:
	virtual		 ~GridArray();
	virtual void Init();
	virtual void DetachAll();
	virtual void KillAll();
	virtual void SetCenter(uint32_t aiX, uint32_t aiY);
	virtual void Shift(int32_t aiCols, int32_t aiRows);
	virtual void Detach(uint32_t aiX, uint32_t aiY);
	virtual void ClearItem(uint32_t aiX, uint32_t aiY);
	virtual void MoveItem(uint32_t aiX1, uint32_t aiY1, uint32_t aiX2, uint32_t aiY2);
	virtual void SwapItem(uint32_t aiX1, uint32_t aiY1, uint32_t aiX2, uint32_t aiY2);

	int32_t iWorldX;
	int32_t iWorldY;
};

ASSERT_SIZE(GridArray, 0xC);