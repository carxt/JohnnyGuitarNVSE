#pragma once

#include "PackageObject.hpp"
#include "BSEnums.hpp"

class PackageTarget {
public:
	PackageTarget();
	~PackageTarget();

	int8_t			eTargetType;
	PackageObject	uObject;
	int32_t			iValue;
	float			fAcquireRadius;
#ifdef EDITOR
	Bitfield32		uiSelectionFilter;
	uint32_t		unk14;
#endif

	void SetTargType(PACKAGE_TARGET_TYPE aeType);
	PACKAGE_TARGET_TYPE GetTargType() const;

	void SetTargReference(TESObjectREFR* apReference);
	TESObjectREFR* GetTargReference() const;
};

#ifdef GAME
ASSERT_SIZE(PackageTarget, 0x10);
#else
ASSERT_SIZE(PackageTarget, 0x18);
#endif