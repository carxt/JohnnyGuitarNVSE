#pragma once

#include "TESForm.hpp"
#include "TESImageSpaceModifiableCountForm.hpp"
#include "ImageSpaceParameterData.hpp"
#include "TESTexture1024.hpp"
#include "TESModel.hpp"

class TESWeather : public TESForm, public TESImageSpaceModifiableCountForm {
public:
	TESWeather();
	~TESWeather();

	struct WeatherSound {
		uint32_t uiSoundID;
		uint32_t uiType;
	};

	enum FogData {
		FD_DAY_NEAR		= 0,
		FD_DAY_FAR		= 1,
		FD_NIGHT_NEAR	= 2,
		FD_NIGHT_FAR	= 3,
		FD_DAY_POWER	= 4,
		FD_NIGHT_POWER	= 5,
		FD_COUNT
	};

	enum WeatherData {
		WD_WIND_SPEED		= 0,
		WD_CLOUD_SPEEDY		= 1,
		WD_CLOUD_SPEEDX		= 2,
		WD_TRANS_DELTA		= 3,
		WD_SUN_GLARE		= 4,
		WD_SUN_DAMAGE		= 5,
		WD_BEGIN_PRECIP		= 6,
		WD_END_PRECIP		= 7,
		WD_BEGIN_THUNDER	= 8,
		WD_END_THUNDER		= 9,
		WD_THUNDER_FREQ		= 10,
		WD_FLAGS			= 11,
		WD_LIGHTNING_R		= 12,
		WD_LIGHTNING_G		= 13,
		WD_LIGHTNING_B		= 14,
		WD_COUNT,
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

	enum COLOR_TYPE : uint32_t {
		COLOR_SKY_UPPER		= 0,
		COLOR_FOG			= 1,
		COLOR_CLOUDS_LOWER	= 2,
		COLOR_AMBIENT		= 3,
		COLOR_SUNLIGHT		= 4,
		COLOR_SUN			= 5,
		COLOR_STARS			= 6,
		COLOR_SKY_LOWER		= 7,
		COLOR_HORIZON		= 8,
		COLOR_CLOUDS_UPPER	= 9,
		COLOR_COUNT,
	};

	enum COLOR_TIME : uint32_t {
		TIME_SUNRISE	= 0,
		TIME_DAY		= 1,
		TIME_SUNSET		= 2,
		TIME_NIGHT		= 3,
		TIME_HIGH_NOON	= 4,
		TIME_MIDNIGHT	= 5,
		TIME_COUNT,
	};


	TESTexture1024				kCloudTexture[4];
	uint8_t						ucCloudSpeed[4];
	uint32_t					uiCloudColorData[4][TIME_COUNT];
	TESModel					kPrecipitationModel;
	uint8_t						ucWeatherData[WD_COUNT];
	float						fFogData[FD_COUNT];
	uint32_t					uiColorData[COLOR_COUNT][TIME_COUNT];
	BSSimpleList<WeatherSound*> kWeatherSounds;
	float						fHDRData[14];
	ImageSpaceParameterData		kImageSpaceParameterMods[2];
	int32_t						iNumCloudLayers;

	TESFORM_TYPE(TESWeather);

	const Bitfield<_WeatherDataFlags>& GetWeatherFlags() const;
	Bitfield<_WeatherDataFlags>& GetWeatherFlags();

	bool IsPleasant() const;
	bool IsCloudy() const;
	bool IsRainy() const;
	bool IsSnowy() const;

	double GetWeatherData(WeatherData aeData, float afMax, float afMin) const;
	uint8_t GetWeatherDataRaw(WeatherData aeData) const;
	uint32_t GetColor(COLOR_TYPE aeColorType, COLOR_TIME aeColorTime) const;
};

ASSERT_SIZE(TESWeather, 0x36C);