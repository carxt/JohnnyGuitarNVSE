#pragma once

#include "TESBoundAnimObject.hpp"
#include "TESSoundFile.hpp"

class BSSoundHandle;

class TESSound : public TESBoundAnimObject, public TESSoundFile {
public:
	TESSound();
	~TESSound();

	struct ALIGN4 _TypeFlags {
		enum Flags : uint32_t {
			VARIABLE_FREQUENCY			= 1u << 0,
			PLAY_AT_RANDOM				= 1u << 1,
			ENVIRONMENT_IGNORED			= 1u << 2,
			RANDOM_LOCATION				= 1u << 3,
			LOOP						= 1u << 4,
			MENU_SOUND					= 1u << 5,
			IS_2D						= 1u << 6,
			IS_360_LFE					= 1u << 7,
			DIALOGUE_SOUND				= 1u << 8,
			ENVELOPE_FAST				= 1u << 9,
			ENVELOPE_SLOW				= 1u << 10,
			IS_2D_RADIUS				= 1u << 11,
			MUTE_WHEN_SUBMERGED			= 1u << 12,
			START_AT_RANDOM_POSITION	= 1u << 13,
		};

		bool bVariableFrequency		: 1;
		bool bPlayAtRandom			: 1;
		bool bEnvironmentIgnored	: 1;
		bool bRandomLocation		: 1;
		bool bLoop					: 1;
		bool bMenuSound				: 1;
		bool b2D					: 1;
		bool b360LFE				: 1;
		bool bDialogueSound			: 1;
		bool bEnvelopeFast			: 1;
		bool bEnvelopeSlow			: 1;
		bool b2DRadius				: 1;
		bool bMuteWhenSubmerged		: 1;
		bool bStartAtRandomPosition : 1;
	};
	using TypeFlags = _TypeFlags::Flags;

	struct Data {
		uint8_t					ucMinDistance;
		uint8_t					ucMaxDistance;
		uint8_t					ucFrequencyAdj;
		Bitfield<_TypeFlags>	uiFlags;
		uint16_t				usStaticAttenuation;
		union {
			uint16_t usStartEnd;
			struct {
				uint8_t	ucEndTime;
				uint8_t	ucStartTime;
			};
		};
		uint16_t				usAttenuationCurve[5];
		uint16_t				usReverbAttenuation;
		uint32_t				uiPriority;
		uint32_t				uiLoopPointBegin;
		uint32_t				uiLoopPointEnd;
	};

#ifdef GAME
	BSString	strEditorID;
#endif
	Data		kData;
	int8_t		cRandomPercentChance;

	TESFORM_TYPE(TESSound);

	uint8_t GetMinDistance() const;
	void SetMinDistance(uint8_t aucVal);

	uint8_t GetMaxDistance() const;
	void SetMaxDistance(uint8_t aucVal);

	bool GetFlag(uint32_t auiFlag) const;
	void SetFlag(uint32_t auiFlag, bool abSet);

	uint8_t GetStartTime() const;
	void SetStartTime(uint8_t aucTime);

	uint8_t GetEndTime() const;
	void SetEndTime(uint8_t aucTime);

	uint16_t GetStaticAttenuation() const;
	void SetStaticAttenuation(uint16_t ausVal);

	uint16_t GetAttenuationCurveValue(int32_t aiIndex) const;
	void SetAttenuationCurveValue(int32_t aiIndex, uint16_t ausVal);

	uint16_t GetReverbAttenuation() const;
	void SetReverbAttenuation(uint16_t ausVal);

	uint32_t GetPriority() const;
	void SetPriority(uint32_t auiPriority);

	TESSound::Data GetData() const;

	int8_t GetRandomPercentChance() const;

	const char* GetFilename() const;

	static TESSound* FindSoundByFilename(const char* apName);
};

#ifdef GAME
ASSERT_SIZE(TESSound, 0x6C);
#else
ASSERT_SIZE(TESSound, 0x88);
#endif