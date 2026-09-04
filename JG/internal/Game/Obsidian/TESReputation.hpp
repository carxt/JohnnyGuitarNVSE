#pragma once

#include "Bethesda/BGSMessageIcon.hpp"
#include "Bethesda/TESForm.hpp"
#include "Bethesda/TESFullName.hpp"
#include "Bethesda/TESIcon.hpp"

class TESReputation : public TESForm, public TESFullName, public TESIcon, public BGSMessageIcon {
public:
	TESReputation();
	~TESReputation();

	struct _Type {
		enum Type : uint32_t {
			NEGATIVE = 0,
			POSITIVE = 1,
		};
	};
	using Type = _Type::Type;

	struct Data {
		float	fMaxReputation;
	};

	Data	kData;
	float	fPositiveReputation;
	float	fNegativeReputation;
	Type	eSoundType;

	TESFORM_TYPE(TESReputation);

	const char* GetReputationMainIcon() const;
	void SetReputationMainIcon(const char* apPath);

	float GetReputationValue(Type aeType) const;
	void SetReputationValue(Type aeType, float afValue);

	void AddReputationValue(Type aeType, float afValue);
	void RemoveReputationValue(Type aeType, float afValue);

	void AddReputationValueByLevel(Type aeType, int32_t aiValue);
	void RemoveReputationValueByLevel(Type aeType, int32_t aiValue);

	void CommitCrime(bool abMajor);

	uint8_t GetReputationLevel(Type aeType) const;

	float GetReputationPercent(Type aeType) const;

	uint8_t GetThreshold(Type aeType) const;

	float GetPositiveRatio() const;
	float GetNegativeRatio() const;

	const char* GetReputationTitle() const;

	const char* GetReputationDesc() const;

	const char* GetReputationIcon() const;
};

using TESReputationType = TESReputation::Type;

#ifdef GAME
ASSERT_SIZE(TESReputation, 0x50);
#else
ASSERT_SIZE(TESReputation, 0x84);
#endif