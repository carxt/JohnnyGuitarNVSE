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

#ifdef GAME
	static constexpr AddressPtr<BSSimpleList<TESObjectREFR*>, 0x11C8264> kAllRadioStations;
#endif

	bool IsRadioStation() const;
	bool IsNonPipboyRadioStation() const;

	TESObjectREFR* GetTempRef() const;
	void SetTempRef(TESObjectREFR* apRef);

	BGSVoiceType* GetVoiceType() const;
	void SetVoiceType(BGSVoiceType* apVoiceType);

#ifdef GAME
	MobileObject* AddMobileObjectExtra(TESObjectREFR* apRef);

	static void AddRadioStation(TESObjectREFR* apRef);

	static void GetRadioStationsInRangeOfRef(TESObjectREFR* apListener, BSSimpleList<TESObjectREFR*>* apRadioStations, BSSimpleList<float>* apDistances);
#endif

	static bool IsRadioStation(const TESForm* apForm, int32_t aiData = 0);
	static bool IsNonPipboyRadioStation(const TESForm* apForm, int32_t aiData = 0);
};

#ifdef GAME
ASSERT_SIZE(BGSTalkingActivator, 0x98);
#else
ASSERT_SIZE(BGSTalkingActivator, 0xCC);
#endif