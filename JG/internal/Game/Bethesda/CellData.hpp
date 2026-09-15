#pragma once

struct ExteriorCellData {
	int32_t		iCellX;
	int32_t		iCellY;
	Bitfield8	ucLandHideFlags;
};
ASSERT_SIZE(ExteriorCellData, 0xC);

struct InteriorCellData {
	uint32_t	uiAmbientColor;
	uint32_t	uiDirectionalColor;
	uint32_t	uiFogColor;
	float		fFogNear;
	float		fFogFar;
	int32_t		iDirectionalXY;
	int32_t		iDirectionalZ;
	float		fDirectionalFade;
	float		fClipDist;
	float		fFogPower;
#ifdef GAME
	uint32_t	uiInteriorOffset;
#endif
};

#ifdef GAME
ASSERT_SIZE(InteriorCellData, 0x2C);
#else
ASSERT_SIZE(InteriorCellData, 0x28);
#endif