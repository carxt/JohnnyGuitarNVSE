#pragma once

#include "Bethesda/BSExtraData.hpp"
#include "FaceGen/FR2MatrixVTC.hpp"
#include "Gamebryo/NiNode.hpp"

class FreeformFaceControl;

class DialogExtraFreeformFaceControl : public BSExtraData {
public:
	FreeformFaceControl*	pData;
	DWORD					dword10;

	BSEXTRA_TYPE(DialogExtraFreeformFaceControl);
};

ASSERT_SIZE(DialogExtraFreeformFaceControl, 0x14);

class TESPreviewControl;

class FreeformFaceControl {
public:
	HWND					hWindow;
	DWORD					dword4;
	TESPreviewControl*		pPreviewControl;
	FaceGenCoords*			pCoordsC;
	FaceGenCoords*			pCoords10;
	float					fHairModifier;
	NiPointer<NiNode>		spNode18;
	NiPointer<NiRefObject>	spUnk1C;
	NiPointer<NiRefObject>	spUnk20;
	NiPointer<NiRefObject>	spUnk24;
	uint32_t				uiSelectedVertex;
	NiLines*				pLine2C;
	NiPoint3				kVector30;
	float					float3C;
	char					byte40;
	FaceGenCoords*			pCoords44;
	DWORD					dword48;
	DWORD					dword4C;
	char					byte50;
};

ASSERT_SIZE(FreeformFaceControl, 0x54);