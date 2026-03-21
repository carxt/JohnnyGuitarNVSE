#pragma once
#include <GameForms.h>

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
extern JGCameraParams JGGameCamera;

extern float __fastcall NiNodeComputeDistance(NiVector3* Vector1, NiVector3* Vector2);


bool __fastcall WorldToScreenPoint3(JGWorldToScreenMatrix* cam, NiPoint3* kPt, float& fBx, float& fBy,
	float& fBz, float fZeroTolerance, int bOffscreenHandleType);

void NiCameraGetAltHook();

bool WorldToScreen(NiPoint3* p_in, float& x_out, float& y_out, float& z_out, int bHandleType, float zeroTolerance = 0.0000099999997f);