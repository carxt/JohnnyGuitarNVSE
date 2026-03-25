#include "NiPoint2.hpp"
#include "NiPoint3.hpp"
#include "NiPoint4.hpp"

// GAME - 0x11F4980
const NiPoint2 NiPoint2::ZERO	= { 0.f, 0.f };

// GAME - 0x11A9B48
const NiPoint2 NiPoint2::UNIT_X	= { 1.f, 0.f };

// GAME - 0x11A9B50
const NiPoint2 NiPoint2::UNIT_Y	= { 0.f, 1.f };

NiPoint2::NiPoint2(const NiPoint3& arOther) noexcept : x(arOther.x), y(arOther.y) {}

NiPoint2::NiPoint2(const NiPoint4& arOther) noexcept : x(arOther.x), y(arOther.y) {}