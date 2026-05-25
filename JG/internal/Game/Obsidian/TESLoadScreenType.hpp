#pragma once

#include "Bethesda/TESForm.hpp"
#include "Gamebryo/NiColor.hpp"

class TESLoadScreenType : public TESForm {
public:
	TESLoadScreenType();
	~TESLoadScreenType();

	enum Type : uint32_t {
		NONE		= 0,
		XP_PROGRESS	= 1,
		OBJECTIVE	= 2,
		TIP			= 3,
		STATS		= 4,
	};

	struct Data {
		struct DisplayData {
			uint32_t	uiPosX;
			uint32_t	uiPosY;
			uint32_t	uiWidth;
			uint32_t	uiHeight;
			float		fOrientation;
			uint32_t	eFont;
			NiColor		kFontColor;
			uint32_t	uiJustification;
		};

		Type		eType;
		DisplayData	kDisplayData1;
		DisplayData	kDisplayData2;
		uint32_t	uiStatsCount;
	};

	Data kData;

	TESFORM_TYPE(TESLoadScreenType);
};

ASSERT_SIZE(TESLoadScreenType, 0x70);