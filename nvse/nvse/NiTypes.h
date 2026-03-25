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
#include "internal/Game/Gamebryo/NiPoint2.hpp"
#include "internal/Game/Gamebryo/NiPoint3.hpp"
#include "internal/Game/Gamebryo/NiPoint4.hpp"

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

// 10 - always aligned?
struct NiQuaternion
{
	float	w, x, y, z;

	NiQuaternion() {}
	NiQuaternion(float _w, float _x, float _y, float _z) : w(_w), x(_x), y(_y), z(_z) {}

	void EulerYPR(NiPoint3 &ypr);
	void RotationMatrix(NiMatrix3 &rotMatrix);
	void Dump();
};

// 34
struct NiTransform
{
	NiMatrix3	rotate;		// 00
	NiPoint3	translate;	// 24
	float		scale;		// 30
};

// 10
class NiBound
{
public:
	NiPoint3	kCenter;
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
	NiPoint3	nrm;
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