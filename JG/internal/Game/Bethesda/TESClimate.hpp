#pragma once

#include "TESForm.hpp"
#include "TESModel.hpp"
#include "TESTexture.hpp"
#include "TESWeatherList.hpp"

struct WeatherEntry;

class TESClimate : public TESForm {
public:
	TESClimate();
	~TESClimate();

	struct _TextureType {
		enum Type {
			SUN			= 0,
			SUN_GLARE	= 1,
			COUNT,
		};
	};
	using TextureType = _TextureType::Type;

	struct _TransTime {
		enum Time {
			SUNRISE_BEGIN	= 0,
			SUNRISE_END		= 1,
			SUNSET_BEGIN	= 2,
			SUNSET_END		= 3,
			COUNT,
		};
	};
	using TransTime = _TransTime::Time;

	struct _Data {
		enum Data {
			VOLATILITY = TransTime::COUNT,
			MOON_DATA,
			COUNT,
		};
	};
	using Data = _Data::Data;

	struct ALIGN1 _MoonData {
		enum Data {
			MOON_PHASE_DAYS_MASK	= 0x3F,
			USES_SECUNDA			= 1u << 6,
			USES_MASSER				= 1u << 7,
		};

		uint8_t ucDays			: 6;
		bool	bUsesSecunda	: 1;
		bool	bUsesMasser		: 1;
	};
	using MoonData = _MoonData::Data;

	TESModel		kNightSky;
	TESWeatherList	kWeatherList;
	TESTexture		kSkyObjects[TextureType::COUNT];
	union {
		uint8_t		ucData[Data::COUNT];
		struct {
			uint8_t				ucSunriseBegin;
			uint8_t				ucSunriseEnd;
			uint8_t				ucSunsetBegin;
			uint8_t				ucSunsetEnd;
			uint8_t				ucVolatility;
			Bitfield<_MoonData> ucMoonData;
		};
	};
	
	TESFORM_TYPE(TESClimate);	

	const char* GetNightSkyModel() const;
	void SetNightSkyModel(const char* apPath);

	const TESTexture* GetTexture(TextureType aeType) const;
	TESTexture* GetTexture(TextureType aeType);

	uint8_t GetTransTime(TransTime aeType) const;
	void SetTransTime(TransTime aeType, uint8_t aucVal);

	uint8_t GetVolatilityIndex() const;
	void SetVolatilityIndex(uint8_t aucVal);

	uint8_t GetMoonPhaseDays() const;
	void SetMoonPhaseDays(uint32_t auiDays);

	bool GetUsesSecunda() const;
	void SetUsesSecunda(bool abVal);

	bool GetUsesMasser() const;
	void SetUsesMasser(bool abVal);

	TESWeather* GetRandomWeather() const;
};

#ifdef GAME
ASSERT_SIZE(TESClimate, 0x58);
#else
ASSERT_SIZE(TESClimate, 0xB4);
#endif