#pragma once

#include "Gamebryo/NiColor.hpp"
#include "Sun.hpp"
#include "Clouds.hpp"
#include "Moon.hpp"
#include "BSSimpleList.hpp"
#include "BSMultiBoundNode.hpp"
#include "Atmosphere.hpp"
#include "Stars.hpp"
#include "Precipitation.hpp"
#include "BSSoundHandle.hpp"
#include "SkyTextureManager.hpp"

class TESClimate;
class TESWeather;
class ImageSpaceModifierInstanceForm;

struct SPEC_EMPTY_BASES SkySound : public BSMemObject {
	BSSoundHandle	kHandle;
	TESWeather*		pWeather;
	uint32_t		eType;
	FormID			uiFormID;
	uint32_t		uiData;

	static constexpr AddressPtr<uint8_t, 0x11CCB74> ucThunderCount;
};

class Sky {
public:
	Sky();
	virtual ~Sky();

		struct _SkyObjectType {
		enum Type {
			SUNGLARE	= 1,
			CLOUDS		= 3,
			STARS		= 5,
			MOON		= 7,
		};
	};
	using SkyObjectType = _SkyObjectType::Type;

	struct _SkyColor {
		enum Color {
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
	using SkyColor = _SkyColor::Color;

	struct _FogDistance {
		enum Distance {
			FOG_NEAR		= 0,
			FOG_FAR			= 1,
			FOG_WATER_NEAR	= 2,
			FOG_WATER_FAR	= 3,
			COUNT			= 4,
		};
	};
	using FogDistance = _FogDistance::Distance;

	struct _Mode {
		enum Mode {
			NONE			= 0,
			INTERIOR		= 1,
			FAKE_EXTERIOR	= 2,
			FULL			= 3,
			COUNT,
		};
	};
	using Mode = _Mode::Mode;

	struct ALIGN4 _Flags {
		enum Flags : uint32_t {
			REFRESH_WEATHER			= 1u << 0,
			FORCED_UPDATE			= 1u << 1,
			UNDERWATER				= 1u << 2,
			REFRESH_ACCELERATION	= 1u << 3,
			FAST_TRAVEL				= 1u << 4,
			REFRESH_MOON			= 1u << 5,
			REFRESH_CLIMATE			= 1u << 6,
			//								7
			REFRESH_SUNRISE_BEGIN	= 1u << 8,
			REFRESH_SUNRISE_END		= 1u << 9,
			REFRESH_SUNSET_BEGIN	= 1u << 10,
			REFRESH_SUNSET_END		= 1u << 11,
			REFRESH_SUNRISE_COLOR	= 1u << 12,
			REFRESH_SUNSET_COLOR	= 1u << 13,
		};

		bool bRefreshWeather		: 1;
		bool bForcedUpdate			: 1;
		bool bUnderwater			: 1;
		bool bRefreshAcceleration	: 1;
		bool bFastTravel			: 1;
		bool bRefreshMoon			: 1;
		bool bRefreshClimate		: 1;
		bool bHideSky				: 1;
		bool bRefreshSunriseBegin	: 1;
		bool bRefreshSunriseEnd		: 1;
		bool bRefreshSunsetBegin	: 1;
		bool bRefreshSunsetEnd		: 1;
		bool bRefreshSunsetColor	: 1;
	};
	using Flags = _Flags::Flags;

#ifdef EDITOR
	void*							unk;
	NiPointer<BSMultiBoundNode>		spRoot;
	NiPointer<NiNode>				spMoonsRoot;
	NiRefObjectPtr					spUnk2;
#else
	NiPointer<BSMultiBoundNode>		spRoot;
	NiPointer<NiNode>				spMoonsRoot;
#endif
	TESClimate*						pCurrentClimate;
	TESWeather*						pCurrentWeather;
	TESWeather*						pLastWeather;
	TESWeather*						pDefaultWeather;
	TESWeather*						pOverrideWeather;
	Atmosphere*						pAtmosphere;
	Stars*							pStars;
	Sun*							pSun;
	Clouds*							pClouds;
	Moon*							pMasser;
	Moon*							pSecunda;
	Precipitation*					pPrecipitation;
	NiColor							kColors[SkyColor::COUNT];
	NiColor							kWaterFogColor;
	NiColor							kSunSpecularColor;
	float							fWindSpeed;
	float							fWindAngle;
	float							fFogDistances[FogDistance::COUNT];
	float							fFogHeight;
	float							fFogPower;
	float							fCurrentGameHour;
	float							fLastWeatherUpdate;
	float							fCurrentWeatherPct;
	Mode							eMode;
	BSSimpleList<SkySound*>*		pSkySoundList;
	float							fFlash;
	uint32_t						uiFlashTime;
	uint32_t						uiLastMoonPhaseUpdate;
	float							fWindowReflectionTimer;
	float							fAccelBeginPct;
	SkyTextureManager				kTextureManager;
	Bitfield<_Flags>				uiFlags;
	ImageSpaceModifierInstanceForm* pFadeInIMODCurrent;
	ImageSpaceModifierInstanceForm* pFadeOutIMODCurrent;
	ImageSpaceModifierInstanceForm* pFadeInIMODLast;
	ImageSpaceModifierInstanceForm* pFadeOutIMODLast;
	float							fHighNoon;
	float							fMidnightWax;
	float							fMidnightWane;

	static Sky* GetSingleton();

	Sun* GetSun() const;

#ifdef GAME
	bool IsRaining() const;

	bool IsSnowing() const;
#endif

	void ForceWeather(TESWeather* apWeather, bool abOverride);

	void SetCurrentClimate(TESClimate* apClimate, bool abForce);

	float GetSunriseBegin();
	float GetSunriseEnd();

	float GetSunsetBegin();
	float GetSunsetEnd();

	void ResetWeather();

	float CalculateMoonPhase(float afDayPassed) const;

#ifdef GAME
	void ActivateWeatherSounds(TESWeather* apWeather);
#endif

	void ReloadAllTextures();

	void UnloadAllTextures();

	void Update(float afDelta);

	void UpdateHDRValues();

	static const NiColorA& GetBlendColor(uint32_t auiID);

protected:
#ifdef GAME
	static constexpr AddressPtr<float, 0x11CA9E8>  fSunriseBegin;
	static constexpr AddressPtr<float, 0x11CA9EC>  fSunRiseEnd;
	static constexpr AddressPtr<float, 0x11CA9F0>  fSunsetBegin;
	static constexpr AddressPtr<float, 0x11CA9F4>  fSunsetEnd;
	static constexpr AddressPtr<NiColorA, 0x11FF8E0, 3> kBlendColors;
#else
	static constexpr AddressPtr<float, 0xEDF69C>  fSunriseBegin;
	static constexpr AddressPtr<float, 0xEDF6A0>  fSunRiseEnd;
	static constexpr AddressPtr<float, 0xEDF6A4>  fSunsetBegin;
	static constexpr AddressPtr<float, 0xEDF6A8>  fSunsetEnd;
	static constexpr AddressPtr<NiColorA, 0xF24338, 3> kBlendColors;
#endif
};

#ifdef GAME
ASSERT_SIZE(Sky, 0x138);
#else
ASSERT_SIZE(Sky, 0x140);
#endif