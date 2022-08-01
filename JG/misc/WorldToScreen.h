#pragma once

//Ni BULLSHIT
#define DECL_FLOAT_OP(op) \
	NiPoint3 operator op(const float n) const \
	{ \
		return NiPoint3(x op n, y op n, z op n); \
	} \
	NiPoint3 operator op##=(const float n) \
	{ \
		return *this = NiPoint3(x op n, y op n, z op n); \
	} \

#define DECL_VEC_OP(op) \
	NiPoint3 operator op(const NiPoint3 v) const \
	{ \
		return NiPoint3(x op v.x, y op v.y, z op v.z); \
	} \
	NiPoint3 operator op##=(const NiPoint3 v) \
	{ \
		return *this = NiPoint3(x op v.x, y op v.y, z op v.z); \
	}

struct NiPoint3 {
	float x, y, z;

	void Scale(float scale) {
		x *= scale;
		y *= scale;
		z *= scale;
	};

	void Init(NiPoint3* point) {
		x = point->x;
		y = point->y;
		z = point->z;
	};

	NiPoint3() : x(0.f), y(0.f), z(0.f) {};

	NiPoint3(const float x, const float y, const float z) : x(x), y(y), z(z) {};

	DECL_FLOAT_OP(*);
	DECL_FLOAT_OP(/ );

	DECL_VEC_OP(+);
	DECL_VEC_OP(-);
	DECL_VEC_OP(*);
	DECL_VEC_OP(/ );

	float length() const {
		return sqrtf(x * x + y * y + z * z);
	}

	float length_sqr() const {
		return x * x + y * y + z * z;
	}

	NiPoint3 normal() const {
		const auto len = length();
		return len == 0.F ? NiPoint3() : NiPoint3(x / len, y / len, z / len);
	}

	static float dot(const NiPoint3& v1, const NiPoint3& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	static NiPoint3 cross(const NiPoint3& v1, const NiPoint3& v2) {
		return NiPoint3(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x);
	}

	NiPoint3* Add(NiPoint3* toAdd) {
		this->x += toAdd->x;
		this->y += toAdd->y;
		this->z += toAdd->z;
		return this;
	}

	NiPoint3* Subtract(NiPoint3* point) {
		this->x -= point->x;
		this->y -= point->y;
		this->z -= point->z;
		return this;
	}

	float CalculateDistSquared(NiPoint3* to) {
		float deltaX = (x - to->x);
		float deltaY = (y - to->y);
		float deltaZ = (z - to->z);

		return deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;
	}
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

struct JGWorldToScreenMatrix {
	float			m_aafWorldToCam[4][4];	// 09C
	NiFrustum		frustum;			// 0DC
	float			minNearPlaneDist;	// 0F8
	float			maxFarNearRatio;	// 0FC
	NiViewport		m_kPort;			// 100
	float			LODAdjust;			// 110
};

struct JGCameraPosition {
	NiMatrix33				m_localRotate;			// 34
	NiVector3				m_localTranslate;		// 58
	float					m_localScale;			// 64
	NiMatrix33				m_worldRotate;			// 68
	NiVector3				m_worldTranslate;		// 8C
	float					m_worldScale;			// 98
};

struct JGCameraParams {
	JGCameraPosition* CamPos = NULL;
	JGWorldToScreenMatrix* WorldMatrx = NULL;
};
JGCameraParams JGGameCamera;

extern float __fastcall NiNodeComputeDistance(NiVector3* Vector1, NiVector3* Vector2);

bool __fastcall WorldToScreenPoint3(JGWorldToScreenMatrix* cam, NiPoint3* kPt, float& fBx, float& fBy,
	float& fBz, float fZeroTolerance, int bOffscreenHandleType) {
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

	if (!(fW > fZeroTolerance)) {
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
	if (fBx >= cam->m_kPort.l && fBx <= cam->m_kPort.r &&
		fBy >= cam->m_kPort.b && fBy <= cam->m_kPort.t && st == 0) {
		return true;
	}
	else {
		if (bOffscreenHandleType < 2) {
			float x2 = cam->m_kPort.r / 2, y2 = cam->m_kPort.t / 2;
			float d = sqrt((((fBx - x2) * (fBx - x2))) + ((fBy - y2) * (fBy - y2))); //Distance
			float r = y2 / d; //Segment ratio
			fBx = (((r * fBx + (1 - r) * x2)));//find point that divides the segment
			fBy = (((r * fBy + (1 - r) * y2)));//into the ratio (1-r):r, this yields circle coordinates
			if (!(bOffscreenHandleType)) //We get square coordinates, since the circle we got is actually a circle inside the square.
			{
				x2 = fBx - 0.5; y2 = fBy - 0.5;
				float Divider = (((y2) * (y2)) > 0.125) ? fabs(y2) : fabs(x2);
				fBx = 0.5 * (((x2) / Divider) + 1);
				fBy = 0.5 * (((y2) / Divider) + 1);
			}
			//Next two lines of code are not actually necessary at all, I'm just a paranoid fuck
			fBx = fBx > 0 ? ((fBx < 1) ? fBx : 1) : 0;
			fBy = fBy > 0 ? ((fBy < 1) ? fBy : 1) : 0;
		}
		return false;
	}
	fBz = NiNodeComputeDistance(&(((NiAVObject*)cam)->m_worldTranslate), (NiVector3*)kPt);
}

//NiPoint3* NiPointBuffer = NULL;

bool __cdecl JG_WorldToScreen(NiPoint3* posXYZ, NiPoint3& posOut, int iOffscreenHandling) {
	return WorldToScreenPoint3(JGGameCamera.WorldMatrx, posXYZ, posOut.x, posOut.y, posOut.z, 0.0000099999997, iOffscreenHandling);
}
__forceinline bool WorldToScreen(NiPoint3* p_in, float& x_out, float& y_out, float& z_out, int bHandleType, float zeroTolerance = 0.0000099999997) {
	return WorldToScreenPoint3(JGGameCamera.WorldMatrx, p_in, x_out, y_out, z_out, zeroTolerance, bHandleType);
}

ParamInfo kParamsProjectionArgsLegacy[8] =
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

ParamInfo kParamsProjectionArgs[8] =
{
	{ "X_Out", kParamType_ScriptVariable , 0 },
	{ "Y_Out", kParamType_ScriptVariable , 0 },
	{ "Z_Out", kParamType_ScriptVariable , 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "HandleMode", kParamType_Integer, 0 },
	{ "Object Ref", kParamType_ObjectRef, 1 }
};

void __stdcall CopyNiCamera(NiCameraAlt* MemoryAddressToCopy, float fov) {
	SceneGraph* sing_SceneGraph = *(SceneGraph**)0x11DEB7C;
	PlayerCharacter* g_ThePlayer = *(PlayerCharacter**)0x11DEA3C;
	if (!sing_SceneGraph || !g_ThePlayer) return;
	if ((NiCamera*)MemoryAddressToCopy != sing_SceneGraph->camera || fabs(fov - g_ThePlayer->worldFOV) > 0.0000099999997) return;
	memcpy(JGGameCamera.CamPos, &(((NiAVObject*)MemoryAddressToCopy)->m_localRotate), sizeof(JGCameraPosition));
	memcpy(JGGameCamera.WorldMatrx, &(MemoryAddressToCopy->m_aafWorldToCam[0][0]), sizeof(JGWorldToScreenMatrix));
}

__declspec(naked) void NiCameraGetAltHook() {
	__asm
	{
		push dword ptr ss : [ebp + 8]
		push dword ptr ss : [ebp - 8]
		call CopyNiCamera
		leave
		retn 0x10
	}
}