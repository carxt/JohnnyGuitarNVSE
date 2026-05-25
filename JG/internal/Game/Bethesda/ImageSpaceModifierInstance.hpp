#pragma once

#include "Gamebryo/NiObject.hpp"

class ImageSpaceModifierInstanceForm;

class ImageSpaceModifierInstance : public NiObject {
public:
	virtual bool							IsExpired() const;
	virtual void							Apply();
	virtual ImageSpaceModifierInstanceForm*	IsForm() const;
	virtual void							PrintInfo(const char* apBuffer) const;

	enum Flags {
		PERMANENT = 1,
	};

	bool			bIsWeather;
	float			fStrength;
	NiObjectPtr		spTarget;
	float			fStartTime;
	Bitfield32		uiFlags;

	bool GetPermanent() const;
	void SetPermanent(bool abPermanent);

	float GetStrength() const;
	void SetStrength(float afStrength);

	float GetStartTime() const;
	void SetStartTime(float afTime);
};

ASSERT_SIZE(ImageSpaceModifierInstance, 0x1C);