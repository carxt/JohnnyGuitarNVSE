#pragma once

#include "TESForm.hpp"
#include "TESImageSpaceModifiableCountForm.hpp"
#include "ImageSpaceParameterData.hpp"
#include "TESTexture1024.hpp"
#include "TESModel.hpp"

class TESWeather : public TESForm, public TESImageSpaceModifiableCountForm<6> {
public:
	TESWeather();
	~TESWeather();

	struct _SoundType {
		enum Type {
			DEFAULT	= 0,
			PRECIP	= 1,
			WIND	= 2,
			THUNDER	= 3,
			COUNT,
		};
	};
	using SoundType = _SoundType::Type;

	struct _FogData {
		enum Data {
			DAY_NEAR	= 0,
			DAY_FAR		= 1,
			NIGHT_NEAR	= 2,
			NIGHT_FAR	= 3,
			DAY_POWER	= 4,
			NIGHT_POWER	= 5,
			COUNT
		};
	};
	using FogData = _FogData::Data;

	struct _WeatherData {
		enum Data {
			WIND_SPEED		= 0,
			CLOUD_SPEED_Y	= 1,
			CLOUD_SPEED_X	= 2,
			TRANS_DELTA		= 3,
			SUN_GLARE		= 4,
			SUN_DAMAGE		= 5,
			BEGIN_PRECIP	= 6,
			END_PRECIP		= 7,
			BEGIN_THUNDER	= 8,
			END_THUNDER		= 9,
			THUNDER_FREQ	= 10,
			FLAGS			= 11,
			LIGHTNING_R		= 12,
			LIGHTNING_G		= 13,
			LIGHTNING_B		= 14,
			COUNT,
		};
	};
	using WeatherData = _WeatherData::Data;

	struct _ColorType {
		enum Type {
			SKY_UPPER		= 0,
			FOG				= 1,
			CLOUDS_LOWER	= 2,
			AMBIENT			= 3,
			SUNLIGHT		= 4,
			SUN				= 5,
			STARS			= 6,
			SKY_LOWER		= 7,
			HORIZON			= 8,
			CLOUDS_UPPER	= 9,
			COUNT,
		};
	};
	using ColorType = _ColorType::Type;

	struct _ColorTime {
		enum Time {
			SUNRISE		= 0,
			DAY			= 1,
			SUNSET		= 2,
			NIGHT		= 3,
			HIGH_NOON	= 4,
			MIDNIGHT	= 5,
			COUNT,
		};
	};
	using ColorTime = _ColorTime::Time;

	struct _HDRData {
		enum Data {
			EYE_ADAPT_SPEED	= 0,
			BLUR_RADIUS		= 1,
			BLUR_PASSES		= 2,
			EMISSIVE_MULT	= 3,
			TARGET_LUM		= 4,
			UPPER_LUM_CLAMP	= 5,
			BRIGHT_SCALE	= 6,
			BRIGHT_CLAMP	= 7,
			LUM_RAMP_NO_TEX	= 8,
			LUM_RAMP_MIN	= 9,
			LUM_RAMP_MAX	= 10,
			SUNLIGHT_DIMMER	= 11,
			GRASS_DIMMER	= 12,
			TREE_DIMMER		= 13,
			COUNT,
		};
	};
	using HDRData = _HDRData::Data;

	static constexpr uint32_t MAX_CLOUD_LAYERS = 4;

	struct WeatherSound {
		uint32_t	uiSoundID;
		SoundType	eType;
	};

	struct ALIGN1 _WeatherDataFlags {
		enum Flags : uint8_t {
			WDF_PLEASANT	= 1u << 0,
			WDF_CLOUDY		= 1u << 1,
			WDF_RAINY		= 1u << 2,
			WDF_SNOW		= 1u << 3,
		};

		bool bPleasant	: 1;
		bool bCloudy	: 1;
		bool bRainy		: 1;
		bool bSnowy		: 1;
	};
	using WeatherDataFlags = _WeatherDataFlags::Flags;

	TESTexture1024				kCloudTexture[MAX_CLOUD_LAYERS];
	uint8_t						ucCloudSpeed[MAX_CLOUD_LAYERS];
	uint32_t					uiCloudColorData[MAX_CLOUD_LAYERS][ColorTime::COUNT];
	TESModel					kPrecipitationModel;
	uint8_t						ucWeatherData[WeatherData::COUNT];
	float						fFogData[FogData::COUNT];
	uint32_t					uiColorData[ColorType::COUNT][ColorTime::COUNT];
	BSSimpleList<WeatherSound*> kWeatherSounds;
	float						fHDRData[HDRData::COUNT];
	ImageSpaceParameterData		kImageSpaceParameterMods[2];
	int32_t						iNumCloudLayers;
#ifdef EDITOR
	uint32_t					uiSelectedCloud;
#endif

	TESFORM_TYPE(TESWeather);

	const Bitfield<_WeatherDataFlags>& GetWeatherFlags() const;
	Bitfield<_WeatherDataFlags>& GetWeatherFlags();

	const TESTexture1024* GetCloudTexture(uint32_t auiLayer) const;
	TESTexture1024* GetCloudTexture(uint32_t auiLayer);

	float GetCloudLayerSpeed(uint32_t auiLayer, float afMax, float afMin) const;

	uint32_t GetCloudColor(uint32_t auiLayer, ColorTime aeTime) const;

	const TESModel* GetPrecipitationModel() const;
	TESModel* GetPrecipitationModel();

	float GetWeatherData(WeatherData aeData, float afMax, float afMin) const;

	uint8_t GetWeatherDataRaw(WeatherData aeData) const;

	bool IsPleasant() const;

	bool IsCloudy() const;

	bool IsRainy() const;

	bool IsSnowy() const;

	float GetFogData(FogData aeData) const;

	uint32_t GetColor(ColorType aeColorType, ColorTime aeColorTime) const;
};

#ifdef GAME
ASSERT_SIZE(TESWeather, 0x36C);
#else
ASSERT_SIZE(TESWeather, 0x3D0);
#endif