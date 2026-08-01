#pragma once

#include "TESCondition.hpp"
#include "TeleportPath.hpp"

class TESQuestTarget {
public:
	struct ALIGN1 _QuestTargetFlags {
		enum Flags : uint8_t {
			IGNORE_LOCKS = 1u << 0,
		};

		bool bIgnoreLocks : 1;
	};
	using QuestTargetFlags = _QuestTargetFlags::Flags;

	Bitfield<_QuestTargetFlags>	ucFlags;
	TESCondition				kConditions;
	TESObjectREFR*				pTarget;
	TeleportPath				kTeleportPath;

	bool GetIgnoreLocks() const;
	void SetIgnoreLocks(bool abVal);

	const TESCondition* GetConditions() const;
	TESCondition* GetConditions();

	TESObjectREFR* GetReference(bool abAllowPickUpActor) const;
	
	TESObjectREFR* GetTrackingRef() const;

	const TeleportPath* GetTargetPath() const;
	TeleportPath* GetTargetPath();
};

ASSERT_SIZE(TESQuestTarget, 0x48);