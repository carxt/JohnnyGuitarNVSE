#pragma once

#include "Bethesda/BGSMessageIcon.hpp"
#include "Bethesda/TESForm.hpp"
#include "Bethesda/TESFullName.hpp"
#include "Bethesda/TESIcon.hpp"

class TESReputation : public TESForm, public TESFullName, public TESIcon, public BGSMessageIcon {
public:
	TESReputation();
	~TESReputation();

	float		fMaxReputation;
	float		fPositiveReputation;
	float		fNegativeReputation;
	uint32_t	uiReputationChangedWasPositive;

	TESFORM_TYPE(TESReputation);

	float GetReputation(bool abPositive) const;
	float GetReputationPercent(bool abPositive) const;
	uint8_t GetThreshold(bool abPositive) const;

private:
	float GetPositiveRatio() const;
	float GetNegativeRatio() const;
};

ASSERT_SIZE(TESReputation, 0x50);