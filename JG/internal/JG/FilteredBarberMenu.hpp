#pragma once

class BGSListForm;

namespace FilteredBarberMenu {

	struct _Flags {
		enum Flags {
			WHITELIST_HAIR  = 1u << 0,
			WHITELIST_BEARD = 1u << 1,
		};
	};
	using Flags = _Flags::Flags;

	void Install();
	void Reset();

	void __fastcall ShowMenu(Bitfield32 auiFlags, const BGSListForm* apFilterList);

};
