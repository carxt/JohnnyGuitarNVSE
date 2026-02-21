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

#if RUNTIME

#if 1
const uint32_t kNiTMapLookupAddr = 0x853130;
#else
#error
#endif

#else
const uint32_t _NiTMap_Lookup = 0;
#endif

// 08
struct NiRTTI
{
	const char		*name;
	NiRTTI			*parent;
};

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
struct NIBound
{
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