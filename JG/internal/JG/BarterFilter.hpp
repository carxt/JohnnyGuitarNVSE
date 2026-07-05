#pragma once

namespace BarterFilter {

	void Install();
	void Reset();

	bool __fastcall Add(uint32_t auiItemFormID, uint32_t auiFlags, uint32_t auiSellerFormID);
	bool __fastcall Remove(uint32_t auiItemFormID, uint32_t auiFlags, uint32_t auiSellerFormID);
	uint32_t __fastcall IsHidden(uint32_t auiItemFormID, uint32_t auiSellerFormID);

}