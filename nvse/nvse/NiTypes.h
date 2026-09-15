#pragma once

#include "Utilities.h"
#include "Gamebryo/NiBound.hpp"
#include "Gamebryo/NiColor.hpp"
#include "Gamebryo/NiColorA.hpp"
#include "Gamebryo/NiFixedString.hpp"
#include "Gamebryo/NiFrustum.hpp"
#include "Gamebryo/NiPoint2.hpp"
#include "Gamebryo/NiPoint3.hpp"
#include "Gamebryo/NiPoint4.hpp"
#include "Gamebryo/NiRTTI.hpp"
#include "Gamebryo/NiSmartPointer.hpp"
#include "Gamebryo/NiTLargePrimitiveArray.hpp"
#include "Gamebryo/NiTObjectArray.hpp"
#include "Gamebryo/NiTObjectSet.hpp"
#include "Gamebryo/NiTPointerList.hpp"
#include "Gamebryo/NiTPointerMap.hpp"
#include "Gamebryo/NiTPrimitiveArray.hpp"
#include "Gamebryo/NiTPrimitiveSet.hpp"
#include "Gamebryo/NiTransform.hpp"
#include "Gamebryo/NiTStringPointerMap.hpp"

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

// 10
struct NiViewport
{
	float	l;
	float	r;
	float	t;
	float	b;
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