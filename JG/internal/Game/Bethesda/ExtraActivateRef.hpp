#pragma once

#include "BSExtraData.hpp"
#include "BSStringT.hpp"
#include "BSSimpleList.hpp"
#include "RefActivateData.hpp"

class ExtraActivateRef : public BSExtraData {
public:
	ExtraActivateRef();
	~ExtraActivateRef();

	struct ALIGN4 _Flags {
		enum Flags : uint32_t {
			PARENT_ONLY = 1 << 0,
		};

		bool bParentOnly : 1;
	};
	using Flags = _Flags::Flags;

	BSSimpleList<RefActivateData*>	kParents;
	Bitfield<_Flags>				uiFlags;
	BSString						strActivationPrompt;

	BSEXTRA_TYPE(ExtraActivateRef);
};

ASSERT_SIZE(ExtraActivateRef, 0x20);