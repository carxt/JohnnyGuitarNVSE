#pragma once

#include "BGSDestructibleObjectForm.hpp"
#include "BGSOpenCloseForm.hpp"
#include "TESBoundAnimObject.hpp"
#include "TESFullName.hpp"
#include "TESModelTextureSwap.hpp"
#include "TESScriptableForm.hpp"

class TESWaterForm;
class BGSTalkingActivator;
class TESSound;

class TESObjectACTI : public TESBoundAnimObject, public TESFullName, public TESModelTextureSwap, public TESScriptableForm, public BGSDestructibleObjectForm, public BGSOpenCloseForm {
public:
	TESObjectACTI();
	~TESObjectACTI();

	TESSound*				pSoundLoop;
	TESSound*				pSoundActivate;
	TESSound*				pRadioTemplate;
	TESWaterForm*			pWaterForm;
	BGSTalkingActivator*	pRadioStation;
	BSString				strActivationPrompt;

	TESFORM_TYPE(TESObjectACTI);

	// Getter is virtual
	void SetDangerous(bool abVal);

	bool GetNoVoiceFilter() const;
	void SetNoVoiceFilter(bool abVal);

	bool GetNonPipboyRadio() const;
	void SetNonPipboyRadio(bool abVal);

	// Getter is virtual
	void SetContinuousBroadcast(bool abVal);

	TESSound* GetLoopingSound() const;
	void SetLoopingSound(TESSound* apSound);

	TESSound* GetActivateSound() const;
	void SetActivateSound(TESSound* apSound);

	TESSound* GetRadioTemplate() const;
	void SetRadioTemplate(TESSound* apSound);

	// Getter is virtual
	void SetWaterType(TESWaterForm* apWater);

	BGSTalkingActivator* GetRadioStation() const;
	void SetRadioStation(BGSTalkingActivator* apStation);

	BSString GetActivationPrompt() const;
	void SetActivationPrompt(BSString aPrompt);
};

ASSERT_SIZE(TESObjectACTI, 0x90);