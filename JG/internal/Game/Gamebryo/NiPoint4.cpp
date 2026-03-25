#include "NiPoint4.hpp"
#include "NiPoint2.hpp"
#include "NiPoint3.hpp"

const NiPoint4 NiPoint4::UNIT_X		= { 1.f, 0.f, 0.f, 0.f};
const NiPoint4 NiPoint4::UNIT_Y		= { 0.f, 1.f, 0.f, 0.f};
const NiPoint4 NiPoint4::UNIT_Z		= { 0.f, 0.f, 1.f, 0.f};
const NiPoint4 NiPoint4::UNIT_W		= { 0.f, 0.f, 0.f, 1.f};
const NiPoint4 NiPoint4::UNIT_ALL	= { 1.f, 1.f, 1.f, 1.f};
const NiPoint4 NiPoint4::ZERO		= { 0.f, 0.f, 0.f, 0.f};

NiPoint4::NiPoint4(const NiPoint2& arOther) noexcept : x(arOther.x), y(arOther.y), z(0.f), w(0.f) {}

NiPoint4::NiPoint4(const NiPoint3& arOther) noexcept : x(arOther.x), y(arOther.y), z(arOther.z), w(0.f) {}

NiPoint4::NiPoint4(const NiPoint3& arOther, float afW) noexcept : x(arOther.x), y(arOther.y), z(arOther.z), w(afW) {}

void NiPoint4::operator=(const NiPoint2& arOther) noexcept {
	x = arOther.x;
	y = arOther.y;
}

void NiPoint4::operator=(const NiPoint3& arOther) noexcept {
	x = arOther.x;
	y = arOther.y;
	z = arOther.z;
}