#pragma once




class NiPoint4 {
public:
	float x;
	float y;
	float z;
	float w;

	NiPoint4() : x(0.f), y(0.f), z(0.f), w(0.f) {};
	NiPoint4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {};
	NiPoint4(const NiPoint3& src) : x(src.x), y(src.y), z(src.z), w(0.f) {};

	inline const float operator[] (uint32_t i) const { return ((float*)&x)[i]; };
	inline float operator[] (uint32_t i) { return ((float*)&x)[i]; };

	operator float* () const { return (float*)this; };


	NiPoint4 operator=(NiPoint3 pt) const {
		return NiPoint4(pt.x, pt.y, pt.z, w);
	};

	void operator=(NiPoint3* pt) {
		x = pt->x;
		y = pt->y;
		z = pt->z;
	};

	void operator=(const NiPoint3& pt) {
		x = pt.x;
		y = pt.y;
		z = pt.z;
	};

	NiPoint4 operator-(NiPoint3& pt) const {
		return NiPoint4(x - pt.x, y - pt.y, z - pt.z, w);
	};

	NiPoint4 operator-(NiPoint3* pt) const {
		return NiPoint4(x - pt->x, y - pt->y, z - pt->z, w);
	};

	NiPoint4* operator-(const NiPoint3& pt) const {
		return new NiPoint4(x - pt.x, y - pt.y, z - pt.z, w);
	};

	NiPoint4* operator-(const NiPoint3* pt) const {
		return new NiPoint4(x - pt->x, y - pt->y, z - pt->z, w);
	};

	NiPoint4 operator+ (const NiPoint4& pt) const { return NiPoint4(x + pt.x, y + pt.y, z + pt.z, w + pt.w); };
	NiPoint4& operator+= (const NiPoint4& pt) {
		x += pt.x;
		y += pt.y;
		z += pt.z;
		w += pt.w;
		return *this;
	};

	NiPoint4 operator*(const float afScalar) {
		return NiPoint4(x * afScalar, y * afScalar, z * afScalar, w * afScalar);
	}

	NiPoint4& operator*= (float afScalar) {
		x *= afScalar;
		y *= afScalar;
		z *= afScalar;
		w *= afScalar;
		return *this;
	};
};

static_assert(sizeof(NiPoint4) == 0x10);




struct NiCameraAlt //Defined here because the one in NVSE is wrong.
{
	uint8_t			undefinedDataStruct[156];
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
	NiMatrix3				m_localRotate;			// 34
	NiVector3				m_localTranslate;		// 58
	float					m_localScale;			// 64
	NiMatrix3				m_worldRotate;			// 68
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
	fBz = NiNodeComputeDistance(&(((NiAVObject*)cam)->m_world.translate), (NiVector3*)kPt);
}

//NiPoint3* NiPointBuffer = NULL;

bool __cdecl JG_WorldToScreen(NiPoint3* posXYZ, NiPoint3& posOut, int iOffscreenHandling) {
	return WorldToScreenPoint3(JGGameCamera.WorldMatrx, posXYZ, posOut.x, posOut.y, posOut.z, 0.0000099999997f, iOffscreenHandling);
}
__forceinline bool WorldToScreen(NiPoint3* p_in, float& x_out, float& y_out, float& z_out, int bHandleType, float zeroTolerance = 0.0000099999997f) {
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
	memcpy(JGGameCamera.CamPos, &(((NiAVObject*)MemoryAddressToCopy)->m_local.rotate), sizeof(JGCameraPosition));
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