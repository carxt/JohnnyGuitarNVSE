#pragma once
#include <GameForms.h>

struct JGWorldToScreenMatrix {
	float			m_aafWorldToCam[4][4];	// 09C
	NiFrustum		frustum;			// 0DC
	float			minNearPlaneDist;	// 0F8
	float			maxFarNearRatio;	// 0FC
	NiViewport		m_kPort;			// 100
	float			LODAdjust;			// 110
};

struct JGCameraPosition {
	NiMatrix3				m_localRotate;			// 34
	NiPoint3				m_localTranslate;		// 58
	float					m_localScale;			// 64
	NiMatrix3				m_worldRotate;			// 68
	NiPoint3				m_worldTranslate;		// 8C
	float					m_worldScale;			// 98
};

struct JGCameraParams {
	JGCameraPosition* CamPos = NULL;
	JGWorldToScreenMatrix* WorldMatrx = NULL;
};
extern JGCameraParams JGGameCamera;

bool __fastcall WorldToScreenPoint3(JGWorldToScreenMatrix* cam, NiPoint3* kPt, float& fBx, float& fBy,
	float& fBz, float fZeroTolerance, int bOffscreenHandleType);


bool WorldToScreen(NiPoint3* p_in, float& x_out, float& y_out, float& z_out, int bHandleType, float zeroTolerance = 0.0000099999997f);