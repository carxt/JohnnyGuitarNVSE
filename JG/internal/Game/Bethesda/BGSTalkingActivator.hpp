#pragma once

#include "TESObjectACTI.hpp"

class BGSVoiceType;
class MobileObject;

class BGSTalkingActivator : public TESObjectACTI {
public:
	// Bethesda failed to override TESForm's methods lol
	virtual bool GetDangerous() const;
	virtual bool GetReflectedByAutoWater() const;

	TESObjectREFR*	pTempRef;
	BGSVoiceType*	pVoiceType;

	static constexpr AddressPtr<BSSimpleList<TESObjectREFR*>, 0x11C8264> kAllRadioStations;

	bool IsRadioStation() const;
	bool IsNonPipboyRadioStation() const;

	TESObjectREFR* GetTempRef() const;
	void SetTempRef(TESObjectREFR* apRef);

	BGSVoiceType* GetVoiceType() const;
	void SetVoiceType(BGSVoiceType* apVoiceType);
	
	MobileObject* AddMobileObjectExtra(TESObjectREFR* apRef);

	static void AddRadioStation(TESObjectREFR* apRef);

	static void GetRadioStationsInRangeOfRef(TESObjectREFR* apListener, BSSimpleList<TESObjectREFR*>* apRadioStations, BSSimpleList<float>* apDistances);

	static bool IsRadioStation(const TESForm* apForm, int32_t aiData = 0);
	static bool IsNonPipboyRadioStation(const TESForm* apForm, int32_t aiData = 0);
};

ASSERT_SIZE(BGSTalkingActivator, 0x98);