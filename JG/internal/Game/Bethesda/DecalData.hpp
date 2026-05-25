#pragma once

class DecalData {
public:
	struct ALIGN1 _Flags {
		enum Flags : uint8_t {
			PARALLAX	= 1u << 0,
			ALPHA_BLEND = 1u << 1,
			ALPHA_TEST	= 1u << 2
		};

		bool bParallax		: 1;
		bool bAlphaBlend	: 1;
		bool bAlphaTest		: 1;
	};
	using Flags = _Flags::Flags;

	struct Data {
		float				fDecalMinWidth;
		float				fDecalMaxWidth;
		float				fDecalMinHeight;
		float				fDecalMaxHeight;
		float				fDepth;
		float				fShininess;
		float				fParallaxScale;
		uint8_t				ucParallaxPasses;
		Bitfield<_Flags>	ucFlags;
		uint32_t			uiColor;
	};

	Data kData;
};

ASSERT_SIZE(DecalData, 0x24);