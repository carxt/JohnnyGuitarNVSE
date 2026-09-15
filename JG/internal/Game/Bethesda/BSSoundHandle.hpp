#pragma once

#include "BSMemObject.hpp"
#include "Gamebryo/NiPoint3.hpp"

class NiAVObject;

class BSSoundHandle {
public:
	BSSoundHandle();
	BSSoundHandle(uint32_t auiSoundID);
	BSSoundHandle(const BSSoundHandle& arOther);
	~BSSoundHandle() = default;

	struct _AssumedState {
		enum State : uint32_t {
			INITIALIZED	= 0,
			PLAYING		= 1,
			STOPPED		= 2,
			PAUSED		= 3,
		};
	};
	using AssumedState = _AssumedState::State;

	uint32_t		uiSoundID;
	bool			bAssumeSuccess;
	AssumedState	eState;

	BSSoundHandle operator=(const BSSoundHandle& arOther);

	bool operator==(const BSSoundHandle& arOther) const;

	bool operator==(uint32_t auiOther) const;

	uint32_t GetID() const;

	void SetAssumeSuccess(bool abAssumeSuccess);

	AssumedState GetState() const;

	void Clear();

	bool IsValid() const;

	bool IsPlaying() const;

	uint32_t GetDuration() const;

	bool Play(bool abLoopPlayback);

	bool PlayAfter(uint32_t auiDelay, uint32_t auiPlayFlags);

	bool FadeInPlay(uint32_t auiMilliseconds);

	void Seek(uint32_t auiMilliseconds);

	bool Pause();

	bool Stop();

	bool Release();

	uint32_t GetSoundType() const;

	void SetPriority(uint8_t aucPriority) const;

	bool SetStaticAttenuation(uint16_t ausAttenuation);

	bool SetReverbAttenuation(uint16_t ausAttenuation);

	float GetVolume() const;
	bool SetVolume(float afVolume);

	bool SetSpeed(float afSpeed);

	bool SetPosition(float afX, float afY, float afZ);
	bool SetPosition(const NiPoint3& arPosition);

	void SetFollowsListener(bool abFollowsListener);

	void SetObjectToFollow(NiAVObject* apObject);

	void SetMinMaxDistance(float afMin, float afMax);

	void SetAttenuationCurve(uint16_t ausVal0, uint16_t ausVal1, uint16_t ausVal2, uint16_t ausVal3, uint16_t ausVal4);

	bool SetBeamEnd(float afX, float afY, float afZ);

	bool FadeOutAndRelease(uint32_t auiMilliseconds);

	void SetTimeConstraints(uint8_t aucStart, uint8_t aucStop);

	bool SetFrequency(float afFrequency);

	bool SetModFrequency(float afFrequency);

	bool SetFrequencyVariance(uint8_t aucFreqVariance);

	using pfnPlayCallback_t = void(__cdecl*)(void* apContext, int32_t aiDuration);
	void SetPlayCallback(pfnPlayCallback_t apfnCallback, void* apContext);

	using pfnCompletionCallback_t = void(__cdecl*)(void* apContext, bool abSucceeded);
	void SetCompletionCallback(pfnCompletionCallback_t apfnCallback, void* apContext);

	void SetSynchStartTime(uint32_t auiStartTime);

	void ClearSynchStartTime();
};

ASSERT_SIZE(BSSoundHandle, 0xC);