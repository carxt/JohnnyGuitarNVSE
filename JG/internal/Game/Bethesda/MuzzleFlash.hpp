#pragma once

#include "Gamebryo/NiSmartPointer.hpp"

class NiAVObject;
class NiPointLight;
class BGSProjectile;
class Projectile;
class TESObjectWEAP;
class TESObjectREFR;
class TESModel;

class MuzzleFlash {
public:
	bool					bEnabled;
	bool					bMPSEnabled;
	bool					bUpdateLight;
	float					fEnableTimer;
	float					fDurationTimer;
	NiPointer<NiAVObject>	sp3D;
	NiPointer<NiPointLight> spLight;
	BGSProjectile*			pProjectile;
	TESObjectWEAP*			pSourceWeapon;
	TESObjectREFR*			pParentRef;

	bool GetEnabled() const;

	void SetDurationTimer(float afVal);

	NiAVObject* Get3D() const;

	BGSProjectile* GetProjectile() const;

	TESObjectWEAP* GetWeaponSource() const;

	TESObjectREFR* GetParentRef() const;

	TESModel* GetMuzzleFlashModel() const;

	void AttachLight();
	void DetachLight();

	void Enable();

	void Update(float afTimeDelta, TESObjectREFR* apParentRef);

	static void SpawnMuzzleFlash(TESObjectREFR* apParentRef, Projectile* apProjectile);
};

ASSERT_SIZE(MuzzleFlash, 0x20);