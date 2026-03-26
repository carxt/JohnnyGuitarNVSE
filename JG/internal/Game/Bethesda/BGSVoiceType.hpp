#pragma once

#include "TESForm.hpp"

class BGSVoiceType : public TESForm {
public:
	BGSVoiceType();
	~BGSVoiceType();

	struct ALIGN1 _VoiceTypeFlags {
		enum Flags : uint8_t {
			ALLOW_DEFAULT_DIALOG	= 1u << 0,
			FEMALE					= 1u << 1,
		};

		bool bAllowDefaultDialog	: 1;
		bool bFemale				: 1;
	};
	using VoiceTypeFlags = _VoiceTypeFlags::Flags;

	BSString					strEditorID;
	Bitfield<_VoiceTypeFlags>	ucFlags;

	TESFORM_TYPE(BGSVoiceType);
};

ASSERT_SIZE(BGSVoiceType, 0x24);