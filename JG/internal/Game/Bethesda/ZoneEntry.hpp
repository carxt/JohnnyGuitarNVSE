#pragma once

#include "bhkTTNode.hpp"

class TESObjectREFR;
class TargetEntry;

class ZoneEntry : public bhkTTNode<TESObjectREFR> {
public:
	ZoneEntry(TESObjectREFR* apReference, hkpCollidable* apCollidable);

	virtual TargetEntry*	AddTarget(TESObjectREFR* apReference, hkpCollidable* apCollidable, uint32_t auiFlags);
	virtual void			Run();

	TargetEntry* pTargetEntries;

	ZoneEntry* GetNext() const;

	ZoneEntry* GetZoneEntry(const hkpCollidable* apCollidable);
	ZoneEntry* GetZoneEntry(const TESObjectREFR* apReference);

	TargetEntry* GetTargetEntry(const TESObjectREFR* apReference);
};

ASSERT_SIZE(ZoneEntry, 0x18);