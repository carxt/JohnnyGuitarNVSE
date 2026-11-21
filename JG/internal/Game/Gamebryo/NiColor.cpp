#include "NiColor.hpp"
#include "NiPoint3.hpp"
#include "NiColorA.hpp"

// GAME - 0x11F4998
const NiColor NiColor::BLACK	= { 0.f, 0.f, 0.f };

// GAME - 0x11A9B7C
const NiColor NiColor::WHITE	= { 1.f, 1.f, 1.f };

// GAME - 0x11A9B88
const NiColor NiColor::RED		= { 1.f, 0.f, 0.f };

// GAME - 0x11A9B94
const NiColor NiColor::GREEN	= { 0.f, 1.f, 0.f };

// GAME - 0x11A9BA0
const NiColor NiColor::BLUE		= { 0.f, 0.f, 1.f };

// GAME - 0x11A9BAC
const NiColor NiColor::YELLOW	= { 1.f, 1.f, 0.f };

// GAME - 0x11A9BB8
const NiColor NiColor::MAGENTA  = { 1.f, 0.f, 1.f };

// GAME - 0x11A9BC4
const NiColor NiColor::CYAN		= { 0.f, 1.f, 1.f };

NiColor::NiColor(const NiPoint3& arOther) noexcept : r(arOther.x), g(arOther.y), b(arOther.z) {}

NiColor::NiColor(const NiColorA& arOther) noexcept : r(arOther.r), g(arOther.g), b(arOther.b) {}