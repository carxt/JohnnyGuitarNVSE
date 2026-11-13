#pragma once

using FormID = uint32_t;

namespace BarterFilter {

	void Install();
	void Reset();

	bool __fastcall Add(FormID auiItemFormID, uint32_t auiFlags, FormID auiSellerFormID);
	bool __fastcall Remove(FormID auiItemFormID, uint32_t auiFlags, FormID auiSellerFormID);
	uint32_t __fastcall IsHidden(FormID auiItemFormID, FormID auiSellerFormID);

}