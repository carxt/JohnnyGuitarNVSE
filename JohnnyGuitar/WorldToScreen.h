#pragma once

//Ni BULLSHIT


struct NiPoint3
{

	float x, y, z;

};


struct NiCameraAlt //Defined here because the one in NVSE is wrong.
{
	UInt8			undefinedDataStruct[156];
	float			m_aafWorldToCam[4][4];	// 09C
	NiFrustum		frustum;			// 0DC
	float			minNearPlaneDist;	// 0F8
	float			maxFarNearRatio;	// 0FC
	NiViewport		m_kPort;			// 100
	float			LODAdjust;			// 110
};

//I hate my code to be honest.

__forceinline void FOVCorrection(float &xOut, float &yOut, float &zOut)
{

	UInt32 PlayerAddress = *(UInt32 *)0x11DEA3C;
	float fmult = 1;
	if (((*(UInt8*)(PlayerAddress + 0x64A)) == 0) || !(*(0x11F91AC) + 0x2B4)) { // this should solve it in the meantime, until I properly fix it

		fmult = (fastDTan(0.5 * (*(float *)(PlayerAddress + 0x674))) / (fastDTan((*(float *)(PlayerAddress + 0x670)) * 0.5)));
	}
	xOut = 0.5 + ((xOut - 0.5) * fmult);
	yOut = 0.5 + ((yOut - 0.5) * fmult);
	zOut = 0.5 + ((zOut - 0.5) * fmult);
}


bool __fastcall WorldToScreenPoint3(NiCameraAlt* cam, NiPoint3* kPt, float &fBx, float &fBy,
	float &fBz, float fZeroTolerance, float HandleType)
{
	bool st = false;
	// project a world space point to screen space
	float fW = kPt->x * cam->m_aafWorldToCam[3][0] +
		kPt->y * cam->m_aafWorldToCam[3][1] + kPt->z * cam->m_aafWorldToCam[3][2] +
		cam->m_aafWorldToCam[3][3];

	fBx = kPt->x * cam->m_aafWorldToCam[0][0] + kPt->y * cam->m_aafWorldToCam[0][1] +
		kPt->z * cam->m_aafWorldToCam[0][2] + cam->m_aafWorldToCam[0][3];
	fBy = kPt->x * cam->m_aafWorldToCam[1][0] + kPt->y * cam->m_aafWorldToCam[1][1] +
		kPt->z * cam->m_aafWorldToCam[1][2] + cam->m_aafWorldToCam[1][3];
	if (fW == 0) return false;

	float fInvW = 1.0f / fW;
	// Transform Z, not entirely sure if it works. This indicates whether you're in front or behind the camera.
	fBz = kPt->x * cam->m_aafWorldToCam[2][0] + kPt->y *
	cam->m_aafWorldToCam[2][1] + kPt->z * cam->m_aafWorldToCam[2][2] +
	cam->m_aafWorldToCam[2][3];
	fBz = fBz * fInvW;

	if (!(fW > fZeroTolerance))
	{
		st = true;
		fInvW *= -1.0f;
	}

	fBx = fBx * fInvW;
	fBy = fBy * fInvW;

	fBx *= (cam->m_kPort.r - cam->m_kPort.l) * 0.5f;
	fBy *= (cam->m_kPort.t - cam->m_kPort.b) * 0.5f;

	fBx += (cam->m_kPort.r + cam->m_kPort.l) * 0.5f;
	fBy += (cam->m_kPort.t + cam->m_kPort.b) * 0.5f;

	fBy = cam->m_kPort.t - fBy;
	FOVCorrection(fBx, fBy, fBz);
	if (fBx >= cam->m_kPort.l && fBx <= cam->m_kPort.r &&
		fBy >= cam->m_kPort.b && fBy <= cam->m_kPort.t && st == 0)
	{
		return true;
	}
	else
	{
		if (HandleType < 2)
		{
			float x2 = cam->m_kPort.r / 2, y2 = cam->m_kPort.t / 2;
			float d = sqrt((((fBx - x2)*(fBx - x2))) + ((fBy - y2)*(fBy - y2))); //Distance
			float r = y2 / d; //Segment ratio
			fBx = (((r * fBx + (1 - r) * x2)));//find point that divides the segment
			fBy = (((r * fBy + (1 - r) * y2)));//into the ratio (1-r):r, this yields circle coordinates
			if (!(HandleType)) //We get square coordinates, since the circle we got is actually a circle inside the square.
			{	x2 = fBx - 0.5; y2 = fBy - 0.5;
				float Divider = (((y2)* (y2)) > 0.125) ? fabs(y2) : fabs(x2);
				fBx = 0.5 * (((x2) / Divider) + 1);
				fBy = 0.5 * (((y2) / Divider) + 1);}
			//Next two lines of code are not actually necessary at all, I'm just a paranoid fuck
			fBx = fBx > 0 ? ((fBx < 1) ? fBx : 1) : 0; 
			fBy = fBy > 0 ? ((fBy < 1) ? fBy : 1) : 0;
		} 
		return false;
	}

}















NiPoint3* NiPointBuffer = NULL;

__forceinline bool WorldToScreen(NiPoint3* p_in, float& x_out, float& y_out, float& z_out, float HandleType, float zeroTolerance = 0.0000099999997)
{
	return WorldToScreenPoint3((NiCameraAlt*)(*(UInt32*)((*(UInt32*)0x11DEB7C) + 0xAC)), p_in, x_out, y_out, z_out, zeroTolerance, HandleType);

}

ParamInfo kParamsProjectionArgs[8] =
{
	{ "X_Out", kParamType_String, 0 },
	{ "Y_Out", kParamType_String, 0 },
	{ "Z_Out", kParamType_String, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "HandleMode", kParamType_Integer, 0 },
	{ "Object Ref", kParamType_ObjectRef, 1 }

};








