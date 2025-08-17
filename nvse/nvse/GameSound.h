#pragma once
#include "GameTypes.h"
#include "GameObjects.h"

class NiAVObject;
class TESSound;
class NiNode;
class BSAudioManagerThread;

// 254
class BSSoundInfo {
public:
	struct Data {
		const char* dword0;
		char		cPath04[260];
		const char* pFilePath;
		char		cFilePath[260];
		float		float210;
		float		float214;
		NiPoint3	kPosition;
		DWORD		dword224;
		float		float228;
		float		float22C;
		UInt32		uiStaticAttenuation;
		UInt32		uiDistanceAttenuation;
		UInt32		uiFaderAttenuation;
	};


	UInt32		uiID;
	float		fFrequency;
	float		fVolume;
	UInt32		uiAudioFlags;
	UInt32		uiDuration;
	bool		bIsPlaying;
	Data		kData;
};
STATIC_ASSERT(sizeof(BSSoundInfo) == 0x254);


class BSSoundHandle {
public:
	UInt32	uiSoundID;
	bool	bAssumeSuccess;
	UInt32	uiState;

	BSSoundHandle() : uiSoundID(-1), bAssumeSuccess(false), uiState(0) {}
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

	bool IsPlaying() const {
		return ThisCall<bool>(0xAD8930, this);
	}

	bool Play(bool abUnk) {
		return ThisCall<bool>(0xAD8830, this, abUnk);
	}

	bool FadeInPlay(uint32_t auiMilliseconds) {
		return ThisCall<bool>(0xAD8D60, this, auiMilliseconds);
	}

	bool Stop() {
		return ThisCall<bool>(0xAD88F0, this);
	}

	bool FadeOutAndRelease(uint32_t auiMilliseconds) {
		return ThisCall<bool>(0xAD8DA0, this, auiMilliseconds);
	}

	bool SetPosition(NiPoint3 akPosition) {
		return ThisCall<bool>(0xAD8B60, this, akPosition);
	}

	void SetObjectToFollow(NiAVObject* apObject) {
		ThisCall(0xAD8F20, this, apObject);
	}

	bool SetVolume(float afVolume) {
		return ThisCall<bool>(0xAD89E0, this, afVolume);
	}
};

STATIC_ASSERT(sizeof(BSSoundHandle) == 0xC);


// 230
class BSGameSound {
public:
	BSGameSound();
	~BSGameSound();

	virtual BSGameSound* Destroy(bool doFree);
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	SetPaused(bool doSet);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);
	virtual void	Unk_0B(void);
	virtual bool	Play(bool abLoop);
	virtual bool	Pause();
	virtual bool	Stop();
	virtual bool	SetVolume(float afVolume);
	virtual void	Unk_10(void);
	virtual bool	Unk_11(void);
	virtual void	Unk_12(void);
	virtual void	Unk_13(float arg1, float arg2, float arg3);
	virtual void	Unk_14(float arg1, float arg2, float arg3);
	virtual void	Unk_15(NiVector3& arg1);
	virtual void	Unk_16(void);
	virtual void	Unk_17(float arg1, float arg2);
	virtual void	Unk_18(UInt16 arg1, UInt16 arg2, UInt16 arg3, UInt16 arg4, UInt16 arg5);
	virtual bool	Unk_19(float arg1);
	virtual float	Unk_1A(void);
	virtual void	Seek(UInt32 timePoint);

	UInt32			mapKey;					// 004
	UInt32			soundFlags;				// 008
	UInt32			flags00C;				// 00C
	UInt32			stateFlags;				// 010
	UInt32			duration;				// 014
	UInt16			staticAttenuation;		// 018	dB * -1000
	UInt16			unk01A;					// 01A
	UInt16			unk01C;					// 01C
	UInt16			unk01E;					// 01E
	UInt16			unk020;					// 020
	UInt16			unk022;					// 022
	float			volume;					// 024	0.0 to 1.0
	float			flt028;					// 028
	float			flt02C;					// 02C
	UInt32			unk030;					// 030
	UInt16			baseSamplingFreq;		// 034
	char			filePath[254];			// 036	Originally: filePath[260]
	TESSound* sourceSound;			// 134	"Stolen" from filePath
	float			frequencyMod;			// 138	^
	float			maxAttenuationDist;		// 13C
	float			minAttenuationDist;		// 140
	UInt32			pathHashFile;			// 144
	UInt32			pathHashFolder;			// 148
	UInt32			unk14C;					// 14C
	float			flt150;					// 150
	UInt32			unk154;					// 154
	SInt8			randFrequencyShift;		// 158
	UInt8			byte159;				// 159
	UInt16			samplingFreq;			// 15A
	UInt32			unk15C;					// 15C
	UInt32			unk160;					// 160
	UInt32			unk164;					// 164
	UInt32			unk168;					// 168
	UInt32			unk16C;					// 16C
	UInt32			unk170;					// 170
	UInt32			unk174[5];				// 174
	UInt32			priority;				// 188
	UInt32			unk18C[3];				// 18C
};
STATIC_ASSERT(sizeof(BSGameSound) == 0x198);

enum AudioRequestTypes {
	kRequestType_Stop = 3,
	kRequestType_Stop2 = 4,
	kRequestType_Delay = 5,
	kRequestType_StopSoundFadeOutTime = 9,
	kRequestType_DialogueFadeInOrOut = 0xD,
	kRequestType_RecalculateVolumesForChangesToMasterVolume = 0xE,
	kRequestType_Volume = 0x10,
	kRequestType_FrequencyAdjustment = 0x14,
	kRequestType_FadeAllSFX = 0x18,
	kRequestType_SetState400ForSomeSounds = 0x1A,
	kRequestType_ClearState400ForSomeSounds = 0x1B,
	kRequestType_SetState400ForSomeSounds2 = 0x1C,
	kRequestType_ClearState400ForSomeSounds2 = 0x1D,
	kRequestType_SoundAtPos = 0x1E,
	kRequestType_Attenuation = 0x21,
	kRequestType_ReverbAttenuation = 0x22,
	kRequestType_PlayWithMinMaxDistance = 0x23,
	kRequestType_SetsPlayingSoundClearStateBit200 = 0x26,
	kRequestType_PlayAtNode = 0x27,
	kRequestType_NiNodeSound = 0x29,
	kRequestType_StopAllSoundsWithFlags = 0x2A,
	kRequestType_SetAudioListenerPosition = 0x38,
	kRequestType_HasCompletionCallback = 0x3A,
	kRequestType_HasSomeCallback = 0x3B,
	kRequestType_StartsAtEndsAt = 0x3E,
	kRequestType_MultiThreaded = 0x35,
	kRequestType_ToggleFirstPersonForPlayingSound = 0x40,
	kRequestType_Priority = 0x41,
	kRequestType_Speed = 0x42
};
union FunctionArg {
	void* pVal;
	float		fVal;
	UInt32		uVal;
	SInt32		iVal;

	FunctionArg& operator=(void* other) {
		pVal = other;
		return *this;
	}
	FunctionArg& operator=(float other) {
		fVal = other;
		return *this;
	}
	FunctionArg& operator=(UInt32 other) {
		uVal = other;
		return *this;
	}
	FunctionArg& operator=(SInt32 other) {
		iVal = other;
		return *this;
	}
};
// 20
struct AudioRequestData {
	UInt32				type;		// 00
	UInt32				soundKey;	// 04
	FunctionArg			value1;		// 08
	FunctionArg			value2;		// 0C
	NiNode*				niNode;	// 10
	NiVector3			pos;		// 14
};
// 188
class BSAudioManager {
public:
	virtual void				Destroy(bool doFree);

	// 10
	struct AudioRequest {
		UInt32				count;			// 00
		UInt8				byte04;			// 04
		UInt8				pad05[3];		// 05
		AudioRequestData*	requestData;	// 08
		UInt32				tickCount;		// 0C
	};
	enum AudioFlags : UInt32
	{
		kAudioFlags_2D = 0x1,
		kAudioFlags_3D = 0x2,
		kAudioFlags_IsVoice = 0x4,
		kAudioFlags_IsFootsteps = 0x8,
		kAudioFlags_Loop = 0x10,
		kAudioFlags_SystemSound = 0x20,
		kAudioFlags_RandomFrequencyShift = 0x40,
		kAudioFlags_80 = 0x80,
		kAudioFlags_100 = 0x100,
		kAudioFlags_IsMusic = 0x800,
		kAudioFlags_RegionSound_MuteWhenSubmerged = 0x1000,
		kAudioFlags_MaybeUnderwater = 0x2000,
		kAudioFlags_Impact = 0x4000,
		kAudioFlags_Cached = 0x8000,
		kAudioFlags_DontCache = 0x10000,
		kAudioFlags_20000 = 0x20000,
		kAudioFlags_FirstPerson = 0x40000,
		kAudioFlags_Modulated = 0x80000,
		kAudioFlags_IsRadio = 0x100000,
		kAudioFlags_IgnoreTimescale = 0x200000,
		kAudioFlags_Radio400000 = 0x400000,
		kAudioFlags_IsMusic2 = 0x800000,
		kAudioFlags_1000000 = 0x1000000,
		kAudioFlags_EnvelopeFast = 0x2000000,
		kAudioFlags_EnvelopeSlow = 0x4000000,
		kAudioFlags_2DRadius = 0x8000000,
		kAudioFlags_BeamEmitter = 0x10000000,
		kAudioFlags_20000000 = 0x20000000,
		kAudioFlags_AnimationDriven = 0x40000000,
	};

	UInt32						unk004[8];			// 004
	AudioRequest				request024;			// 024
	AudioRequest				request034;			// 034
	AudioRequest				request044;			// 044
	NiTPointerMap<BSGameSound>	playingSounds;		// 054
	NiTPointerMap<BSSoundInfo>	playingSoundInfos1;	// 064
	NiTPointerMap<BSSoundInfo>	playingSoundInfos2;	// 074
	NiTPointerMap<NiAVObject>	soundPlayingObjects;// 084
	DList<BSGameSound>			cachedSounds;		// 094
	UInt32						unk0A0;				// 0A0
	UInt32						unk0A4;				// 0A4
	float						flt0A8;				// 0A8
	CRITICAL_SECTION			kMessageCS;
	CRITICAL_SECTION			kSoundInfosCS;
	CRITICAL_SECTION			kCacheListCS;
	CRITICAL_SECTION			kMessageProcessingCS;
	CRITICAL_SECTION			kTaskCS;
	DList<void>					list124;			// 124
	UInt32						lastTickCount;		// 130
	UInt8						byte134;			// 134
	UInt8						byte135;			// 135
	UInt8						pad136[2];			// 136
	UInt32						unk138;				// 138
	BSAudioManagerThread* audioMgrThread;	// 13C
	float						volumes[12];		// 140
	//	0	Master
	//	1	Foot
	//	2	Voice
	//	3	Effects
	//	4	Music
	//	5	Radio
	UInt32						unk170;				// 170
	UInt8						byte174;			// 174
	UInt8						byte175;			// 175
	UInt8						pad176[2];			// 176
	UInt32						unk178;				// 178
	UInt32						unk17C;				// 17C
	UInt32						nextMapKey;			// 180
	UInt8						byte184;			// 184
	UInt8						pad185[3];			// 185

	__forceinline static BSAudioManager* Get() { return (BSAudioManager*)0x11F6EF0; }
};
STATIC_ASSERT(sizeof(BSAudioManager) == 0x188);

class BSAudioListener {
public:
	BSAudioListener();
	~BSAudioListener();

	virtual BSAudioListener* Destroy(bool doFree);
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);
	virtual void	Unk_0B(void);
	virtual void	Unk_0C(void);
};

// 64
class BSWin32AudioListener : public BSAudioListener {
public:
	BSWin32AudioListener();
	~BSWin32AudioListener();

	UInt32			unk04[14];		// 04
	float			flt3C;			// 3C
	UInt32			unk40[9];		// 40
};

class BSWin32Audio {
public:
	BSWin32Audio();
	~BSWin32Audio();

	virtual void	Destroy(bool doFree);
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual BSGameSound* CreateGameSound(const char* filePath);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);

	UInt32					unk004[3];		// 004
	BSWin32AudioListener* listener;		// 010
	UInt32					unk014[3];		// 014
	bool(*sub_82D150)(UInt32*, UInt32*, UInt32*, UInt32*);	// 020
	bool(*sub_82D280)(UInt32*, UInt32*, UInt32*, UInt32*);	// 024
	bool(*sub_5E3630)(UInt32*);	// 028
	UInt32(*sub_82D400)(UInt32*, TESSound*, UInt32*);	// 02C
	void(*sub_832C40)(void);	// 030
	void(*sub_832C80)(void);	// 034

	static BSWin32Audio* GetSingleton() { return *(BSWin32Audio**)0x11F6D98; };

	BSSoundHandle GetSoundHandleByFilePath(const char* apFileName, uint32_t aeAudioFlags, TESSound* apSound) {
		BSSoundHandle kHandle;
		ThisCall(0xAD7480, this, &kHandle, apFileName, aeAudioFlags, apSound);
		return kHandle;
	}

	BSSoundHandle GetSoundHandleByFormID(UInt32 auiFormID, uint32_t aeAudioFlags) {
		BSSoundHandle kHandle;
		ThisCall(0xAD73B0, this, &kHandle, auiFormID, aeAudioFlags);
		return kHandle;
	}

	BSSoundHandle BSWin32Audio::GetSoundHandleByEditorName(const char* apEditorID, uint32_t aeAudioFlags) {
		BSSoundHandle kHandle;
		ThisCall(0xAD7550, this, &kHandle, apEditorID, aeAudioFlags);
		return kHandle;
	}

};

struct SoundList
{
	BSSoundHandle data;
	SoundList* next;

	void Append(BSSoundHandle* sound)
	{
		ThisCall(0x7A19A0, this, sound);
	}

	void FreeAll() {
		ThisCall(0x76B7A0, this);
	}
};