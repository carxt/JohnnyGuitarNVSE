#pragma once

#include "TESForm.hpp"
#include "TESFullName.hpp"
#include "TESDescription.hpp"
#include "TESTexture.hpp"
#include "TESAttributes.hpp"

class TESClass : public TESForm, public TESFullName, public TESDescription, public TESTexture, public TESAttributes {
public:
	TESClass();
	~TESClass();

	struct ALIGN1 _ClassFlags {
		enum Flags : uint8_t{
			PLAYABLE = 1u << 0,
			GUARD	 = 1u << 1,
		};

		bool bPlayable	: 1;
		bool bGuard		: 1;
	};
	using ClassFlags = _ClassFlags::Flags;

	struct Data {
		ActorValue::Index		eTagSkills[4];
		Bitfield<_ClassFlags>	ucFlags;
		Bitfield<_ServiceFlags>	uiServices;
		uint8_t					ucTrainingSkill;
		uint8_t					ucTrainingLevel;
	};

	Data kData;

	TESFORM_TYPE(TESClass);

	ActorValue::Index GetTagSkill(uint32_t auiIndex) const;
	void SetTagSkill(uint32_t auiIndex, ActorValue::Index aeSkill);
	bool IsTagSkill(ActorValue::Index aeSkill) const;

	bool IsPlayable() const;
	void SetPlayable(bool abVal);

	bool IsGuard() const;
	void SetGuard(bool abVal);

	ActorValue::Index GetTrainingSkill() const;
	void SetTrainingSkill(ActorValue::Index aeSkill);

	uint32_t GetTrainingSkillLevel() const;
	void SetTrainingSkillLevel(uint8_t aucLevel);

	static uint32_t GetTagSkillCount();
};

#ifdef GAME
ASSERT_SIZE(TESClass, 0x60);
#else
ASSERT_SIZE(TESClass, 0x8C);
#endif