#pragma once

//CMD BULLSHIT


//Ni BULLSHIT


struct NiPoint3
{

	float x, y, z;

};

class NiCamera : public NiAVObject
{
public:
	NiCamera();
	~NiCamera();

	float			m_aafWorldToCam[4][4];	// 09C
	NiFrustum		frustum;			// 0DC
	float			minNearPlaneDist;	// 0F8
	float			maxFarNearRatio;	// 0FC
	NiViewport		m_kPort;			// 100
	float			LODAdjust;			// 110
};
//STATIC_ASSERT(sizeof(NiCameraAlt) == 0x114);

struct NiCameraAF 
{
	UInt8			undefinedDataStruct[156];
	float			m_aafWorldToCam[4][4];	// 09C
	NiFrustum		frustum;			// 0DC
	float			minNearPlaneDist;	// 0F8
	float			maxFarNearRatio;	// 0FC
	NiViewport		m_kPort;			// 100
	float			LODAdjust;			// 110
};


__forceinline void FOVCorrection(float &xOut, float &yOut, float &zOut)
{
	//UInt8* p_isThirdPerson = (UInt8*)((*(UInt32*)0x11DEA3C) + 0x64A;
	//float* p_WorldFOV = (float *)((*(UInt32 *)0x11DEA3C) + 0x670;
	//float* p_1stPersonFOV = (float *)((*(UInt32 *)0x11DEA3C) + 0x674;
	float fmult = 1;
	if (((*(UInt8*)((*(UInt32*)0x11DEA3C) + 0x64A)) == 0)) {

		fmult = (fastDTan(0.5 * (*(float *)((*(UInt32 *)0x11DEA3C) + 0x674))) / (fastDTan((*(float *)((*(UInt32 *)0x11DEA3C) + 0x670)) * 0.5)));
	}
	xOut = 0.5 + ((xOut - 0.5) * fmult);
	yOut = 0.5 + ((yOut - 0.5) * fmult);
	//zOut = 0.5 + ((zOut - 0.5) * fmult);
}


__forceinline void FindPoint(float &x, float& y, float viewportWidth, float viewPortHeight, float intersection, float HandleType)
{
	float x2 = viewportWidth / 2;
	float y2 = viewPortHeight / 2;
	float d = sqrt((((x - x2)*(x - x2))) + ((y - y2)*(y - y2))); //Distance
	float Divider = 0;
	float r = intersection / d; //Segment ratio
	//Console_Print("%.2f, %.2f, %.2f, %.2f aaaa", x, y, d, r);
	x = (((r * x + (1 - r) * x2)));// - 0.5) * M_SQRT2) + 0.5; //find point that divides the segment
	y = (((r * y + (1 - r) * y2)));// - 0.5) * M_SQRT2) + 0.5; //into the ratio (1-r):r
	if (!(HandleType)) 
	{
		x2 = x - 0.5; y2 = y - 0.5;
		Divider = (((y2)* (y2)) > 0.125) ? fabs(y2) : fabs(x2);
		x = 0.5 * (((x2) / Divider) + 1);
		y = 0.5 * (((y2) / Divider) + 1);
	}
	x = x > 0 ? ((x < 1) ? x : 1) : 0;
	y = y > 0 ? ((y < 1) ? y : 1) : 0;
}



bool __fastcall W2S3AltEX(NiCameraAF* cam, NiPoint3* kPt, float &fBx, float &fBy,
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

	float fInvW;
	if (fW == 0) return false;
	if (fW > fZeroTolerance)
	{
		fInvW = 1.0f / fW;
	}
	else
	{
		st = true;
		fInvW = -1.0f / fW;
	}

		fBx = fBx * fInvW;
		fBy = fBy * fInvW;

		fBx *= (cam->m_kPort.r - cam->m_kPort.l) * 0.5f;
		fBy *= (cam->m_kPort.t - cam->m_kPort.b) * 0.5f;

		fBx += (cam->m_kPort.r + cam->m_kPort.l) * 0.5f;
		fBy += (cam->m_kPort.t + cam->m_kPort.b) * 0.5f;

		// Transform Z
		fBz = kPt->x * cam->m_aafWorldToCam[2][0] + kPt->y *
			cam->m_aafWorldToCam[2][1] + kPt->z * cam->m_aafWorldToCam[2][2] +
			cam->m_aafWorldToCam[2][3];

		fBz = fBz * fInvW;
		fBy = cam->m_kPort.t - fBy;
		FOVCorrection(fBx, fBy, fBz);
		if (fBx >= cam->m_kPort.l && fBx <= cam->m_kPort.r &&
			fBy >= cam->m_kPort.b && fBy <= cam->m_kPort.t && st == false)
		{
			return true;
		}
		else 
		{

			if (HandleType < 2) FindPoint(fBx, fBy, cam->m_kPort.r, cam->m_kPort.t, (cam->m_kPort.t)/2, HandleType);
			return false;
		}

}























NiPoint3* NiPointBuffer = NULL;

__forceinline bool WorldPtToScreenPt3Alt(NiPoint3* p_in, float& x_out, float& y_out, float& z_out, float HandleType, float zeroTolerance = 0.0000099999997)
{
	return W2S3AltEX((NiCameraAF*)(*(UInt32*)((*(UInt32*)0x11DEB7C) + 0xAC)), p_in, x_out, y_out, z_out, zeroTolerance, HandleType);

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
















































bool  WorldPtToScreenPt(NiCamera* cam, const NiPoint3& kPt, float &fBx, float &fBy, float& OutofX, float& OutofY,
	float fZeroTolerance = 0.0000099999997)
{

	fZeroTolerance = max(fZeroTolerance, 0.0f);

	// project a world space point to screen space

	float fW = kPt.x * cam->m_aafWorldToCam[3][0] +
		kPt.y * cam->m_aafWorldToCam[3][1] + kPt.z * cam->m_aafWorldToCam[3][2] +
		cam->m_aafWorldToCam[3][3];

	if (fW > fZeroTolerance)
	{
		float fInvW = 1.0f / fW;

		fBx = kPt.x *  cam->m_aafWorldToCam[0][0] + kPt.y *  cam->m_aafWorldToCam[0][1] +
			kPt.z *  cam->m_aafWorldToCam[0][2] + cam->m_aafWorldToCam[0][3];
		fBy = kPt.x *  cam->m_aafWorldToCam[1][0] + kPt.y *  cam->m_aafWorldToCam[1][1] +
			kPt.z *  cam->m_aafWorldToCam[1][2] + cam->m_aafWorldToCam[1][3];

		fBx = fBx * fInvW;
		fBy = fBy * fInvW;

		fBx *= (cam->m_kPort.r - cam->m_kPort.l) * 0.5f;
		fBy *= (cam->m_kPort.t - cam->m_kPort.b) * 0.5f;

		fBx += (cam->m_kPort.r + cam->m_kPort.l) * 0.5f;
		fBy += (cam->m_kPort.t + cam->m_kPort.b) * 0.5f;

		// If on screen return true. Otherwise, we fall through to false.

		OutofX = (fBx <= cam->m_kPort.l) ? -1 : (fBx >= cam->m_kPort.r);
		OutofY = (fBy <= cam->m_kPort.b) ? -1 : (fBy >= cam->m_kPort.t);

		if (OutofX == 0 && OutofY == 0) return true;

	}
	return false;
}




bool __fastcall W2S3Alt(NiCameraAF* cam, NiPoint3* kPt, float &fBx, float &fBy,
	float &fBz, float fZeroTolerance)
{
	// Same as previous function, except Z is also transformed

	// Make sure we have a valid near plane test value. If not, we could
	// generate a divide by zero.
	//fZeroTolerance = max(fZeroTolerance, 0.0f);

	// project a world space point to screen space
	float fW = kPt->x * cam->m_aafWorldToCam[3][0] +
		kPt->y * cam->m_aafWorldToCam[3][1] + kPt->z * cam->m_aafWorldToCam[3][2] +
		cam->m_aafWorldToCam[3][3];

	// Check to see if we're on the appropriate side of the camera.
	//fW = fabs(fW);

	if (fabs(fW) > fZeroTolerance)
	{
		float fInvW = 1.0f / fW;

		fBx = kPt->x * cam->m_aafWorldToCam[0][0] + kPt->y * cam->m_aafWorldToCam[0][1] +
			kPt->z * cam->m_aafWorldToCam[0][2] + cam->m_aafWorldToCam[0][3];
		fBy = kPt->x * cam->m_aafWorldToCam[1][0] + kPt->y * cam->m_aafWorldToCam[1][1] +
			kPt->z * cam->m_aafWorldToCam[1][2] + cam->m_aafWorldToCam[1][3];

		fBx = fBx * fInvW;
		fBy = fBy * fInvW;

		fBx *= (cam->m_kPort.r - cam->m_kPort.l) * 0.5f;
		fBy *= (cam->m_kPort.t - cam->m_kPort.b) * 0.5f;

		fBx += (cam->m_kPort.r + cam->m_kPort.l) * 0.5f;
		fBy += (cam->m_kPort.t + cam->m_kPort.b) * 0.5f;

		// Transform Z
		fBz = kPt->x * cam->m_aafWorldToCam[2][0] + kPt->y *
			cam->m_aafWorldToCam[2][1] + kPt->z * cam->m_aafWorldToCam[2][2] +
			cam->m_aafWorldToCam[2][3];

		fBz = fBz * fabs(fInvW);
		fBy = cam->m_kPort.t - fBy;
		FOVCorrection(fBx, fBy, fBz);
		if (fBx >= cam->m_kPort.l && fBx <= cam->m_kPort.r &&
			fBy >= cam->m_kPort.b && fBy <= cam->m_kPort.t)
		{
			return true;
		}


		//FOVCorrection(fBx, fBy, fBz);
	}
	else
	{
		fBx = 0;
		fBy = 0;
		fBz = 0;
	}
}








bool WorldPtToScreenPt3(NiPoint3& p_in, float& x_out, float& y_out, float& z_out, float zeroTolerance = 0.0000099999997)
{
	return (bool)(ThisStdCall(0x00A6FDB0, (void*)(*(UInt32*)((*(UInt32*)0x11DEB7C) + 0xAC)), &p_in, &x_out, &y_out, &z_out, zeroTolerance));

}


inline bool W2S(NiPoint3* p_in, float& x_out, float& y_out, float zeroTolerance = 0.0000099999997)
{
	return (bool)(ThisStdCall(0x00A6FC50, (void*)(*(UInt32*)((*(UInt32*)0x11DEB7C) + 0xAC)), p_in, &x_out, &y_out, zeroTolerance));
}




bool W2SAlt(NiPoint3* p_in, float& x_out, float& y_out, float& outofX, float& outofY, float zeroTolerance = 0.0000099999997)
{

	return  WorldPtToScreenPt((NiCamera*)(*(UInt32*)((*(UInt32*)0x011DEB7C) + 0xAC)), *p_in, x_out, y_out, outofX, outofY, zeroTolerance);
}






/*bool __fastcall W2S3Alt(NiCameraAF* cam, NiPoint3* kPt, float &fBx, float &fBy,
float &fBz, float fZeroTolerance)
{
// Same as previous function, except Z is also transformed

// Make sure we have a valid near plane test value. If not, we could
// generate a divide by zero.
//fZeroTolerance = max(fZeroTolerance, 0.0f);

// project a world space point to screen space
float fW = kPt->x * cam->m_aafWorldToCam[3][0] +
kPt->y * cam->m_aafWorldToCam[3][1] + kPt->z * cam->m_aafWorldToCam[3][2] +
cam->m_aafWorldToCam[3][3];

// Check to see if we're on the appropriate side of the camera.
//fW = fabs(fW);

if (fabs(fW) > fZeroTolerance)
{
float fInvW = 1.0f / fW;

fBx = kPt->x * cam->m_aafWorldToCam[0][0] + kPt->y * cam->m_aafWorldToCam[0][1] +
kPt->z * cam->m_aafWorldToCam[0][2] + cam->m_aafWorldToCam[0][3];
fBy = kPt->x * cam->m_aafWorldToCam[1][0] + kPt->y * cam->m_aafWorldToCam[1][1] +
kPt->z * cam->m_aafWorldToCam[1][2] + cam->m_aafWorldToCam[1][3];

fBx = fBx * fInvW;
fBy = fBy * fInvW;

fBx *= (cam->m_kPort.r - cam->m_kPort.l) * 0.5f;
fBy *= (cam->m_kPort.t - cam->m_kPort.b) * 0.5f;

fBx += (cam->m_kPort.r + cam->m_kPort.l) * 0.5f;
fBy += (cam->m_kPort.t + cam->m_kPort.b) * 0.5f;

// Transform Z
fBz = kPt->x * cam->m_aafWorldToCam[2][0] + kPt->y *
cam->m_aafWorldToCam[2][1] + kPt->z * cam->m_aafWorldToCam[2][2] +
cam->m_aafWorldToCam[2][3];

fBz = fBz * fabs(fInvW);

//Console_Print("X: %.2f, Y: %.2f", fBx, fBy);
//	C	onsole_Print("L: %.2f, R:%.2f, T:%.2f, B:%.2f", cam->m_kPort.l, cam->m_kPort.r, cam->m_kPort.t, cam->m_kPort.b);
// If on screen, then return true.
FOVCorrection(fBx, fBy, fBz);
if (fBx >= cam->m_kPort.l && fBx <= cam->m_kPort.r &&
fBy >= cam->m_kPort.b && fBy <= cam->m_kPort.t)
{
return true;
}


//FOVCorrection(fBx, fBy, fBz);
}
else
{
fBx = 0;
fBy = 0;
fBz = 0;
}
return false;
}*/
//#define M_SQRT2 1.41421356237309504880
//#define MATHPI 3.14159265358979323846  

/*double FastArcTan(double x)
{
return 0.78539816339744830962*x - x*(fabs(x) - 1)*(0.2447 + 0.0663*fabs(x));
}*/


/*__forceinline void FindPoint(float &x, float& y, float viewportWidth, float viewPortHeight, float intersection)
{
float x2 = viewportWidth / 2;
float y2 = viewPortHeight / 2;
float d = sqrt((((x - x2)*(x - x2))) + ((y - y2)*(y - y2))); //Distance
//float hypotenuseSQ = sqrtf(x*x + y*y);
float r = intersection / d; //Segment ratio
//Console_Print("%.2f, %.2f, %.2f, %.2f aaaa", x, y, d, r);
//x = (((r * x + (1 - r) * x2))); // - 0.5) * M_SQRT2) + 0.5; //find point that divides the segment
//y = (((r * y + (1 - r) * y2)));
//y -= y2;
//x -= x2;
/*x = (((r * x + (1 - r) * x2))); // - 0.5) * M_SQRT2) + 0.5; //find point that divides the segment
y = (((r * y + (1 - r) * y2)));

x *= r;
y *= r;
Console_Print("%.2f, %.2f, %.2f, %.2f aaaa", x, y, d, r);
//DiagonalizationTest(x, y);
//x *= xMath; y *= yMath;

//x = (x/2) + 0.5 , y = (y / 2) + 0.5;
//	Console_Print("m %.2f, %.2f", xMath, yMath);

// - 0.5); //* M_SQRT2) + 0.5; //into the ratio (1-r):r
//Converted to square
x = x > 0 ? ((x < 1) ? x : 1) : 0;
y = y > 0 ? ((y < 1) ? y : 1) : 0;
}*/

/*class NiPoint3
{
public:

float x, y, z;

};
*/

/*__forceinline void FOVCorrection(float &xOut, float &yOut, float &zOut)
{
UInt8* p_isThirdPerson = (UInt8*)((*(UInt32*)0x11DEA3C) + 0x64A);;
if (((*p_isThirdPerson) == 0)) {
float* p_WorldFOV = (float *)((*(UInt32 *)0x11DEA3C) + 0x670);
float* p_1stPersonFOV = (float *)((*(UInt32 *)0x11DEA3C) + 0x674);
yOut = 1 - yOut;
float fmult = 1;
fmult = (fastDTan(0.5 * (*p_1stPersonFOV)) / (fastDTan(*p_WorldFOV * 0.5)));
xOut = 0.5 + ((xOut - 0.5) * fmult);
yOut = 0.5 + ((yOut - 0.5) * fmult);
zOut = 0.5 + ((zOut - 0.5) * fmult);
}
}*/






/*bool __fastcall W2S3Alt(NiCameraAF* cam, NiPoint3* kPt, float &fBx, float &fBy,
float &fBz, float fZeroTolerance)
{
// Same as previous function, except Z is also transformed

// Make sure we have a valid near plane test value. If not, we could
// generate a divide by zero.
//fZeroTolerance = max(fZeroTolerance, 0.0f);

// project a world space point to screen space
float fW = kPt->x * cam->m_aafWorldToCam[3][0] +
kPt->y * cam->m_aafWorldToCam[3][1] + kPt->z * cam->m_aafWorldToCam[3][2] +
cam->m_aafWorldToCam[3][3];

// Check to see if we're on the appropriate side of the camera.
//fW = fabs(fW);

if (fabs(fW) > fZeroTolerance)
{
float fInvW = 1.0f / fW;

fBx = kPt->x * cam->m_aafWorldToCam[0][0] + kPt->y * cam->m_aafWorldToCam[0][1] +
kPt->z * cam->m_aafWorldToCam[0][2] + cam->m_aafWorldToCam[0][3];
fBy = kPt->x * cam->m_aafWorldToCam[1][0] + kPt->y * cam->m_aafWorldToCam[1][1] +
kPt->z * cam->m_aafWorldToCam[1][2] + cam->m_aafWorldToCam[1][3];

fBx = fBx * fInvW;
fBy = fBy * fInvW;

fBx *= (cam->m_kPort.r - cam->m_kPort.l) * 0.5f;
fBy *= (cam->m_kPort.t - cam->m_kPort.b) * 0.5f;

fBx += (cam->m_kPort.r + cam->m_kPort.l) * 0.5f;
fBy += (cam->m_kPort.t + cam->m_kPort.b) * 0.5f;

// Transform Z
fBz = kPt->x * cam->m_aafWorldToCam[2][0] + kPt->y *
cam->m_aafWorldToCam[2][1] + kPt->z * cam->m_aafWorldToCam[2][2] +
cam->m_aafWorldToCam[2][3];

fBz = fBz * fabs(fInvW);
//Console_Print("X: %.2f, Y: %.2f", fBx, fBy);
//	C	onsole_Print("L: %.2f, R:%.2f, T:%.2f, B:%.2f", cam->m_kPort.l, cam->m_kPort.r, cam->m_kPort.t, cam->m_kPort.b);
// If on screen, then return true.
FOVCorrection(fBx, fBy, fBz);
if (fBx >= cam->m_kPort.l && fBx <= cam->m_kPort.r &&
fBy >= cam->m_kPort.b && fBy <= cam->m_kPort.t)
{
return true;
}
//FOVCorrection(fBx, fBy, fBz);
}
else
{
fBx = 0;
fBy = 0;
fBz = 0;
}
return false;
}*/


/*bool __fastcall W2S3Alt2(NiCameraAF* cam, NiPoint3* kPt, float &fBx, float &fBy,
float &fBz, float fZeroTolerance)
{
// Same as previous function, except Z is also transformed

// Make sure we have a valid near plane test value. If not, we could
// generate a divide by zero.
//fZeroTolerance = max(fZeroTolerance, 0.0f);

// project a world space point to screen space
float fW = kPt->x * cam->m_aafWorldToCam[3][0] +
kPt->y * cam->m_aafWorldToCam[3][1] + kPt->z * cam->m_aafWorldToCam[3][2] +
cam->m_aafWorldToCam[3][3];

// Check to see if we're on the appropriate side of the camera.
//fW = fabs(fW);
if (fW > fZeroTolerance)
{
float fInvW = 1.0f / fW;

fBx = kPt->x * cam->m_aafWorldToCam[0][0] + kPt->y * cam->m_aafWorldToCam[0][1] +
kPt->z * cam->m_aafWorldToCam[0][2] + cam->m_aafWorldToCam[0][3];
fBy = kPt->x * cam->m_aafWorldToCam[1][0] + kPt->y * cam->m_aafWorldToCam[1][1] +
kPt->z * cam->m_aafWorldToCam[1][2] + cam->m_aafWorldToCam[1][3];

fBx = fBx * fInvW;
fBy = fBy * fInvW;

fBx *= (cam->m_kPort.r - cam->m_kPort.l) * 0.5f;
fBy *= (cam->m_kPort.t - cam->m_kPort.b) * 0.5f;

fBx += (cam->m_kPort.r + cam->m_kPort.l) * 0.5f;
fBy += (cam->m_kPort.t + cam->m_kPort.b) * 0.5f;

// Transform Z
fBz = kPt->x * cam->m_aafWorldToCam[2][0] + kPt->y *
cam->m_aafWorldToCam[2][1] + kPt->z * cam->m_aafWorldToCam[2][2] +
cam->m_aafWorldToCam[2][3];

fBz = fBz * fInvW;
//Console_Print("X: %.2f, Y: %.2f", fBx, fBy);
//	C	onsole_Print("L: %.2f, R:%.2f, T:%.2f, B:%.2f", cam->m_kPort.l, cam->m_kPort.r, cam->m_kPort.t, cam->m_kPort.b);
// If on screen, then return true.
if (fBx >= cam->m_kPort.l && fBx <= cam->m_kPort.r &&
fBy >= cam->m_kPort.b && fBy <= cam->m_kPort.t)
{

return true;
}
}
else
{
fBx = 0;
fBy = 0;
fBz = 0;
}
return false;
}*/