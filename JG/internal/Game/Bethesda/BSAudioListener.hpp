#pragma once

#include "BSMemObject.hpp"
#include "Gamebryo/NiPoint3.hpp"

class BSAudioListener {
public:
	BSAudioListener();
	virtual					~BSAudioListener();
	virtual void			Init();
	virtual void			SetPosition(const NiPoint3& arPos);
	virtual const NiPoint3&	GetPosition() const;
	virtual void			Update();
	virtual void			SetOrientation(const NiPoint3& arFront, const NiPoint3& arTop);
	virtual const NiPoint3& GetFrontOrientation() const;
	virtual const NiPoint3&	GetTopOrientation() const;
	virtual void			SetVelocity(const NiPoint3& arVelocity);
	virtual void			SetGain(float afValue);
	virtual void			SetEnvironmentType(uint32_t aeType);
	virtual uint32_t		GetEnvironmentType() const;
	virtual void			SetRolloffFactor(float afValue);

	NiPoint3	kListenerPosition;
	NiPoint3	kFrontOrientation;
	NiPoint3	kTopOrientation;
	NiPoint3	kVelocity;
	uint32_t	uiTimeLastUpdated;
	float		fVelocity;
	float		fRollOffFactor;
	float		fGain;
	uint32_t	eEnvironmentType;
};

ASSERT_SIZE(BSAudioListener, 0x48)