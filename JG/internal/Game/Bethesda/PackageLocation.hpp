#pragma once

#include "PackageObject.hpp"
#include "BSEnums.hpp"

class PackageLocation {
public:
	PackageLocation();
	~PackageLocation();

	int8_t			eLocationType;
	uint32_t		uiRadius;
#ifdef EDITOR
	Bitfield32		uiSelectionFilter;
#endif
	PackageObject	uObject;

	void SetLocType(PACKAGE_LOCATION_TYPE aeType);
	PACKAGE_LOCATION_TYPE GetLocType() const;

	void SetLocReference(TESObjectREFR* apReference);

	void SetRadius(uint32_t auiRadius);
	uint32_t GetRadius() const;
};

#ifdef GAME
ASSERT_SIZE(PackageLocation, 0xC);
#else
ASSERT_SIZE(PackageLocation, 0x10);
#endif