#pragma once

#include "BaseFormComponent.hpp"

class TESIdleForm;

class BGSIdleCollection : public BaseFormComponent {
public:
	enum PickType : uint8_t {
		RANDOM		= 0,
		SEQUENCE	= 1,
	};

	struct ALIGN1 _IdleCollectionFlags {
		enum Flags : uint8_t {
			PICK_TYPE	= 1u << 0,
			DO_ONCE		= 1u << 2,
		};

		PickType ePickType	: 1;
		bool				: 1;
		bool bDoOnce		: 1;
	};
	using IdleCollectionFlags = _IdleCollectionFlags::Flags;

	Bitfield<_IdleCollectionFlags>	ucIdleFlags;
	uint8_t							ucIdleCount;
	TESIdleForm**					ppIdles;
	float							fTimerCheckForIdle;
};

ASSERT_SIZE(BGSIdleCollection, 0x10);