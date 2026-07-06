#pragma once

#include "BGSDestructibleObjectForm.hpp"
#include "BGSMessageIcon.hpp"
#include "Gamebryo/NiColor.hpp"
#include "TESBoundAnimObject.hpp"
#include "TESFullName.hpp"
#include "TESIcon.hpp"
#include "TESModelTextureSwap.hpp"
#include "TESScriptableForm.hpp"
#include "TESValueForm.hpp"
#include "TESWeightForm.hpp"

class TESSound;

class TESObjectLIGH : public TESBoundAnimObject, public TESFullName, public TESModelTextureSwap, public TESIcon, 
						public BGSMessageIcon, public TESScriptableForm, public TESWeightForm, public TESValueForm, public BGSDestructibleObjectForm {
public:
	TESObjectLIGH();
	~TESObjectLIGH();

	struct ALIGN4 _LightFlags {
		enum Flags : uint32_t {
			DYNAMIC				= 1u << 0,
			CAN_CARRY			= 1u << 1,
			NEGATIVE			= 1u << 2,
			FLICKER				= 1u << 3,
			DEEP_COPY			= 1u << 4,
			OFF_BY_DEFAULT		= 1u << 5,
			FLICKER_SLOW		= 1u << 6,
			PULSE				= 1u << 7,
			PULSE_SLOW			= 1u << 8,
			SPOTLIGHT			= 1u << 9,
			SPOTSHADOW			= 1u << 10,
#if USE_MODDED_CHANGES
			COLOR_SHIFT			= 1u << 11,
			COLOR_SHIFT_SLOW	= 1u << 12,
#endif
		};

		bool bDynamic			: 1;
		bool bCanCarry			: 1;
		bool bNegative			: 1;
		bool bFlicker			: 1;
		bool bDeepCopy			: 1;
		bool bOffByDefault		: 1;
		bool bFlickerSlow		: 1;
		bool bPulse				: 1;
		bool bPulseSlow			: 1;
		bool bSpotlight			: 1;
		bool bSpotShadow		: 1;
#if USE_MODDED_CHANGES
		bool bColorShift		: 1;
		bool bColorShiftSlow	: 1;
#endif
	};
	using LightFlags = _LightFlags::Flags;

	struct Data {
		int32_t					iTime;
		uint32_t				uiRadius;
		union {
			struct {
				uint8_t	ucRed;
				uint8_t	ucGreen;
				uint8_t	ucBlue;
				uint8_t	ucAlpha;
			};
			uint32_t uiColor;
		};
		Bitfield<_LightFlags>	uiFlags;
		float					fFalloffExp;
		float					fFOV;
	};

	Data			kData;
	float			fFadeValue;
	TESSound*		pSound;
	NiColor         kEmittanceColor;

	TESFORM_TYPE(TESObjectLIGH);

	bool GetDynamic() const;
	bool GetCanCarry() const;
	bool GetNegative() const;
	bool GetFlicker() const;
	bool GetDeepCopy() const;
	bool GetOffByDefault() const;
	bool GetFlickerSlow() const;
	bool GetPulse() const;
	bool GetPulseSlow() const;
	bool GetSpotlight() const;
	bool GetSpotShadow() const;

#if USE_MODDED_CHANGES
	bool GetColorShift() const;
	bool GetColorShiftSlow() const;
#endif
};

ASSERT_SIZE(TESObjectLIGH, 0xC8);