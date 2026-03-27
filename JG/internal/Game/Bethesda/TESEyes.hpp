#pragma once

#include "TESForm.hpp"
#include "TESFullName.hpp"
#include "TESTexture.hpp"

class TESNPC;

class TESEyes : public TESForm, public TESFullName, public TESTexture {
public:
	TESEyes();
	~TESEyes();

	struct ALIGN1 _EyeFlags {
		enum Flags : uint8_t {
			PLAYABLE	= 1u << 0,
			NOT_MALE	= 1u << 1,
			NOT_FEMALE	= 1u << 2,
		};

		bool bPlayable	: 1;
		bool bNotMale	: 1;
		bool bNotFemale : 1;
	};
	using EyeFlags = _EyeFlags::Flags;

	Bitfield<_EyeFlags> ucEyeFlags;

	TESFORM_TYPE(TESEyes);

	bool GetPlayable() const;
	void SetPlayable(bool abVal);

	bool CanBeMale() const;
	void SetCanBeMale(bool abVal);

	bool CanBeFemale() const;
	void SetCanBeFemale(bool abVal);

	bool CanBeEyesForNPC(TESNPC* apNPC);
};

ASSERT_SIZE(TESEyes, 0x34);