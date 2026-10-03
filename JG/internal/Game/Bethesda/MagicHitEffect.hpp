#pragma once

#include "BSTempEffect.hpp"

class ActiveEffect;
class TESObjectREFR;

NiSmartPointer(MagicHitEffect);

class MagicHitEffect : public BSTempEffect {
public:
	MagicHitEffect();
	~MagicHitEffect();

	virtual bool		Init();
	virtual void		ClearTarget();
	virtual void		UpdatePosition();
	virtual uint16_t	GetSaveSizeAlt(ActiveEffect* apEffect, TESObjectREFR* apRef) const;
	virtual void		SaveGame(ActiveEffect* apEffect, TESObjectREFR* apRef);
	virtual void		LoadGame(ActiveEffect* apEffect, TESObjectREFR* apRef);
	virtual void		InitLoadGame(ActiveEffect* apEffect, TESObjectREFR* apRef);
	virtual void		FinishInitLoadGame(ActiveEffect* apEffect, TESObjectREFR* apRef, void*);

	ActiveEffect*	pActiveEffect;
	TESObjectREFR*	pTarget;
	float			fElapsedTime;
	bool			bFinished;

	NIRTTI_ADDRESS(0x11DC6B4);

	ActiveEffect* GetActiveEffect() const;

	TESObjectREFR* GetTarget() const;
	
	bool GetFinished() const;
};

ASSERT_SIZE(MagicHitEffect, 0x28);