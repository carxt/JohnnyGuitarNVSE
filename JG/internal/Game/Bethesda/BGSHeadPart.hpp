#pragma once

#include "TESForm.hpp"
#include "TESFullName.hpp"
#include "TESModelTextureSwap.hpp"
#include "BSSimpleList.hpp"

class BGSHeadPart : public TESForm, public TESFullName, public TESModelTextureSwap {
public:
	BGSHeadPart();
	~BGSHeadPart();

	struct ALIGN1 _HeadPartFlags {
		enum Flags : uint8_t {
			PLAYABLE = 1u << 0,
		};

		bool bPlayable : 1;
	};
	using HeadPartFlags = _HeadPartFlags::Flags;

	Bitfield<_HeadPartFlags>	ucHeadFlags;
	BSSimpleList<BGSHeadPart*>	kExtraParts;

	TESFORM_TYPE(BGSHeadPart);

	bool GetPlayable() const;
	void SetPlayable(bool abVal);

	const BSSimpleList<BGSHeadPart*>* GetExtraPartList() const;
	BSSimpleList<BGSHeadPart*>* GetExtraPartList();
};

ASSERT_SIZE(BGSHeadPart, 0x50);