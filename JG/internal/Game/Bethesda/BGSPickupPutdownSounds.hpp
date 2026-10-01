#pragma once

#include "BaseFormComponent.hpp"

class TESSound;

class BGSPickupPutdownSounds : public BaseFormComponent {
public:
	BGSPickupPutdownSounds();
	~BGSPickupPutdownSounds();

	TESSound* pPickupSound;
	TESSound* pPutdownSound;

	TESSound* GetPickupSound() const;
	void SetPickupSound(TESSound* apSound);

	TESSound* GetPutdownSound() const;
	void SetPutdownSound(TESSound* apSound);
};

ASSERT_SIZE(BGSPickupPutdownSounds, 0xC);