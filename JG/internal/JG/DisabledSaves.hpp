#pragma once

namespace DisabledSaves {

	struct _SaveTypeBits {
		enum Bits {
			NORMAL	= 0,
			AUTO	= 1,
			SYSTEM	= 2,
			FORCED	= 3,
			QUICK	= 4,
		};
	};
	using SaveTypeBits = _SaveTypeBits::Bits;

	struct _SaveTypeFlags {
		enum Flags {
			NORMAL	= 1 << SaveTypeBits::NORMAL,
			AUTO	= 1 << SaveTypeBits::AUTO,
			SYSTEM	= 1 << SaveTypeBits::SYSTEM,
			FORCED	= 1 << SaveTypeBits::FORCED,
			QUICK	= 1 << SaveTypeBits::QUICK,

			ALL		= NORMAL | AUTO | SYSTEM | FORCED | QUICK,
		};
	};
	using SaveTypeFlags = _SaveTypeFlags::Flags;

	void Init();
	void Install();
	void Reset();
	void Toggle(uint8_t aucMod, bool abToggle, uint32_t auiTypeFlags);
}