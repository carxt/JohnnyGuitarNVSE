#pragma once

#include "TESForm.hpp"
#include "TESFullName.hpp"
#include "TESModel.hpp"
#include "TESTexture.hpp"

class TESNPC;

class TESHair : public TESForm, public TESFullName, public TESModel, public TESTexture {
public:
	TESHair();
	~TESHair();

	struct ALIGN1 _HairFlags {
		enum Flags : uint8_t {
			PLAYABLE	= 1u << 0,
			NOT_MALE	= 1u << 1,
			NOT_FEMALE	= 1u << 2,
			FIXED_COLOR	= 1u << 3,
		};

		bool bPlayable		: 1;
		bool bNotMale		: 1;
		bool bNotFemale		: 1;
		bool bFixedColor	: 1;
	};
	using HairFlags = _HairFlags::Flags;

	Bitfield<_HairFlags> ucHairFlags;

	TESFORM_TYPE(TESHair);

	bool GetPlayable() const;
	void SetPlayable(bool abVal);

	bool CanBeMale() const;
	void SetCanBeMale(bool abVal);

	bool CanBeFemale() const;
	void SetCanBeFemale(bool abVal);

	bool GetFixedColor() const;
	void SetFixedColor(bool abVal);

	bool CanBeHairForNPC(TESNPC* apNPC);
};

ASSERT_SIZE(TESHair, 0x4C);