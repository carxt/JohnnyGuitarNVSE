#pragma once

#include "BSMemObject.hpp"
#include "Gamebryo/NiPoint3.hpp"

class NiAVObject;

class BSSoundHandle {
public:
	enum State {
		NONE	= 0,
		PLAYING = 1,
		STOPPED = 2,
		PAUSED	= 3,
	};

	uint32_t	uiSoundID;
	bool		bAssumeSuccess;
	uint32_t	uiState;

	BSSoundHandle() : uiSoundID(UINT32_MAX), bAssumeSuccess(false), uiState(0) {}
	BSSoundHandle(const BSSoundHandle& arHandle) : uiSoundID(arHandle.uiSoundID), bAssumeSuccess(arHandle.bAssumeSuccess), uiState(arHandle.uiState) {}
	explicit BSSoundHandle(const BSSoundHandle* apHandle) : uiSoundID(apHandle->uiSoundID), bAssumeSuccess(apHandle->bAssumeSuccess), uiState(apHandle->uiState) {}
	~BSSoundHandle() {}

	BSSoundHandle operator=(const BSSoundHandle& arHandle) {
		uiSoundID = arHandle.uiSoundID;
		bAssumeSuccess = arHandle.bAssumeSuccess;
		uiState = arHandle.uiState;
		return *this;
	}

	BSSoundHandle operator=(const BSSoundHandle* apHandle) {
		uiSoundID = apHandle->uiSoundID;
		bAssumeSuccess = apHandle->bAssumeSuccess;
		uiState = apHandle->uiState;
		return *this;
	}

	void Clear();

	bool IsValid() const;
	bool IsInvalid() const { return uiSoundID == -1; }
	bool IsPlaying() const;

	uint32_t GetDuration() const;

	bool Play(bool abLoopPlayback);
	bool FadeInPlay(uint32_t auiMilliseconds);
	bool Stop();

	bool Release();

	void SetPriority(uint8_t aucPriority) const;

	bool SetStaticAttenuation(uint16_t ausAttenuation);
	bool SetReverbAttenuation(uint16_t ausAttenuation);
	bool SetVolume(float afVolume);
	bool SetSpeed(float afSpeed);
	bool SetPosition(NiPoint3 akPosition);
	void SetObjectToFollow(NiAVObject* apObject);
	void SetMinMax(float afMin, float afMax);
	void SetAttenuationCurve(uint16_t ausVal0, uint16_t ausVal1, uint16_t ausVal2, uint16_t ausVal3, uint16_t ausVal4);
	bool FadeOutAndRelease(uint32_t auiMilliseconds);
};

ASSERT_SIZE(BSSoundHandle, 0xC);