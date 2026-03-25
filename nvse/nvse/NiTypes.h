#pragma once

#include "Utilities.h"
#include "internal/Game/Gamebryo/NiFixedString.hpp"
#include "internal/Game/Gamebryo/NiSmartPointer.hpp"
#include "internal/Game/Gamebryo/NiTObjectArray.hpp"
#include "internal/Game/Gamebryo/NiTPrimitiveArray.hpp"
#include "internal/Game/Gamebryo/NiTLargePrimitiveArray.hpp"
#include "internal/Game/Gamebryo/NiTPointerList.hpp"
#include "internal/Game/Gamebryo/NiTPointerMap.hpp"
#include "internal/Game/Gamebryo/NiTStringPointerMap.hpp"
#include "internal/Game/Gamebryo/NiTPrimitiveSet.hpp"
#include "internal/Game/Gamebryo/NiTObjectSet.hpp"
#include "internal/Game/Gamebryo/NiRTTI.hpp"

// 24
struct NiMatrix3
{
	float	cr[3][3];

	NiMatrix3() {}
	NiMatrix3(float m00, float m10, float m20, float m01, float m11, float m21, float m02, float m12, float m22)
	{
		cr[0][0] = m00;
		cr[0][1] = m10;
		cr[0][2] = m20;
		cr[1][0] = m01;
		cr[1][1] = m11;
		cr[1][2] = m21;
		cr[2][0] = m02;
		cr[2][1] = m12;
		cr[2][2] = m22;
	}

	void ExtractAngles(float &rotX, float &rotY, float &rotZ);
	void RotationMatrix(float rotX, float rotY, float rotZ);
	void Rotate(float rotX, float rotY, float rotZ);
	void MultiplyMatrices(NiMatrix3 &matA, NiMatrix3 &matB);
	void Dump(const char *title = NULL);

	void MakeXRotation(float fAngle);

	void MakeYRotation(float fAngle);

	void MakeZRotation(float fAngle);

	NiMatrix3 operator*(const NiMatrix3& mat) const;

	static const NiMatrix3 IDENTITY;
};

struct NiQuaternion;

// 0C
struct NiVector3
{
	float	x, y, z;

	NiVector3() {}
	NiVector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	void operator +=(const NiVector3 &rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
	}
	void operator -=(const NiVector3 &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
	}

	void ToQuaternion(NiQuaternion &quaternion);
	void MultiplyMatrixVector(NiMatrix3 &mat, NiVector3 &vec);
	bool RayCastCoords(NiVector3 &maxRange, NiVector3 &posVector, NiMatrix3 &rotMatrix);
};

// 10 - always aligned?
struct NiVector4
{
	float	x, y, z, w;

	NiVector4() {}
	NiVector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
};

struct NiPoint2 {
	float x;
	float y;

	NiPoint2() : x(0.f), y(0.f) {};

	NiPoint2(float _x, float _y) : x(_x), y(_y) {};
};

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

class NiPoint3 {
public:
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
	inline float Distance(const NiPoint3& pt) const {
		return (*this - pt).length();
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
	static float Sign(NiPoint3 p1, NiPoint3 p2, NiPoint3 p3) {
		return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
	}

	static bool PointInTriangle(NiPoint3 pt, NiPoint3 v1, NiPoint3 v2, NiPoint3 v3) {
		bool b1 = Sign(pt, v1, v2) < 0.0;
		bool b2 = Sign(pt, v2, v3) < 0.0;
		bool b3 = Sign(pt, v3, v1) < 0.0;

		return (b1 == b2) && (b2 == b3);
	}

	static NiPoint3 GetTriangleCenter(NiPoint3 v1, NiPoint3 v2, NiPoint3 v3) {
		return NiPoint3((v1.x + v2.x + v3.x) / 3.0f, (v1.y + v2.y + v3.y) / 3.0f, (v1.z + v2.z + v3.z) / 3.0f);
	}

};

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

// 10 - always aligned?
struct NiQuaternion
{
	float	w, x, y, z;

	NiQuaternion() {}
	NiQuaternion(float _w, float _x, float _y, float _z) : w(_w), x(_x), y(_y), z(_z) {}

	void EulerYPR(NiVector3 &ypr);
	void RotationMatrix(NiMatrix3 &rotMatrix);
	void Dump();
};

// 34
struct NiTransform
{
	NiMatrix3	rotate;		// 00
	NiVector3	translate;	// 24
	float		scale;		// 30
};

// 10
class NiBound
{
public:
	NiVector3	kCenter;
	union {
		float	fRadius;
		int		iRadius;
	};
};

// 1C
struct NiFrustum
{
	float	l;			// 00
	float	r;			// 04
	float	t;			// 08
	float	b;			// 0C
	float	n;			// 10
	float	f;			// 14
	uint8_t	o;			// 18
	uint8_t	pad19[3];	// 19
};

// 10
struct NiViewport
{
	float	l;
	float	r;
	float	t;
	float	b;
};

// C
class NiColor
{
public:
	float	r;
	float	g;
	float	b;
};

// 10
class NiColorA
{
public:
	float	r;
	float	g;
	float	b;
	float	a;
};

// 10
struct NiPlane
{
	NiVector3	nrm;
	float		offset;
};

// 14
template <typename T>
class BSTPersistentList
{
public:
	BSTPersistentList();
	~BSTPersistentList();

	virtual void	Destroy(bool destroy);

//	void	** _vtbl;	// 00
	uint32_t	unk04;		// 04
	uint32_t	unk08;		// 08
	uint32_t	unk0C;		// 0C
	uint32_t	unk10;		// 10
};