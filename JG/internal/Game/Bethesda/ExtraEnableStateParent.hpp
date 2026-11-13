#pragma once

#include "BSExtraData.hpp"

class TESObjectREFR;

class ExtraEnableStateParent : public BSExtraData {
public:
	ExtraEnableStateParent();
	~ExtraEnableStateParent();

	struct ALIGN1 _Flags {
		enum Flags : uint32_t {
			INVERSE = 1 << 0,
			POP_IN	= 1 << 1,
			POP_OUT	= 1 << 2,
		};

		bool bInverse	: 1;
		bool bPopIn		: 1;
		bool bPopOut	: 1;
	};
	using Flags = _Flags::Flags;

	TESObjectREFR*		pParent;
	Bitfield<_Flags>	ucFlags;

	BSEXTRA_TYPE(ExtraEnableStateParent);
};

ASSERT_SIZE(ExtraEnableStateParent, 0x14);