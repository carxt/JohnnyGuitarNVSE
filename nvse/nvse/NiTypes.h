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
#include "internal/Game/Gamebryo/NiTransform.hpp"
#include "internal/Game/Gamebryo/NiFrustum.hpp"
#include "internal/Game/Gamebryo/NiColor.hpp"
#include "internal/Game/Gamebryo/NiColorA.hpp"
#include "internal/Game/Gamebryo/NiBound.hpp"

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