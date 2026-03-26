#pragma once

#include "TESBoundObject.hpp"

class TESSound;
class TESRegion;
class BSSoundHandle;

class BGSAcousticSpace : public TESBoundObject {
public:
	BGSAcousticSpace();
	~BGSAcousticSpace();

	enum TimeOfDay {
		DAWN	= 0,
		NOON	= 1,
		DUSK	= 2,
		NIGHT	= 3,
		COUNT	= 4
	};

	bool		bIsInterior;

	union {
		TESSound* pTimeOfDaySounds[TimeOfDay::COUNT];

		struct {
			TESSound* pDawnSound;
			TESSound* pNoonSound;
			TESSound* pDuskSound;
			TESSound* pNightSound;
		};
	};

	TESSound*	pWallaSound;
	TESRegion*	pRegion;
	uint32_t	eEnvironmentType;
	int32_t		iWallaPopulation;

	TESFORM_TYPE(BGSAcousticSpace);

	bool IsInterior() const;
	void SetInterior(bool abInterior);

	TESSound* GetDawnSound() const;
	void SetDawnSound(TESSound* apSound);

	TESSound* GetNoonSound() const;
	void SetNoonSound(TESSound* apSound);

	TESSound* GetDuskSound() const;
	void SetDuskSound(TESSound* apSound);

	TESSound* GetNightSound() const;
	void SetNightSound(TESSound* apSound);

	TESSound* GetWallaSound() const;
	void SetWallaSound(TESSound* apSound);

	int32_t GetWallaPopulation() const;
	void SetWallaPopulation(int32_t aiPopulation);

	TESRegion* GetRegion() const;
	void SetRegion(TESRegion* apRegion);

	uint32_t GetEnvironmentType() const;
	void SetEnvironmentType(uint32_t aeType);
};

ASSERT_SIZE(BGSAcousticSpace, 0x54);