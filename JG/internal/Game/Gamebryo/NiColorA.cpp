#include "NiColorA.hpp"
#include "NiColor.hpp"
#include "NiPoint3.hpp"
#include "NiPoint4.hpp"

// GAME - 0x11A9BD0
const NiColorA NiColorA::BLACK	    = { 0.f, 0.f, 0.f, 1.f };

// GAME - 0x11A9BE0
const NiColorA NiColorA::WHITE	    = { 1.f, 1.f, 1.f, 1.f };

// GAME - 0x11A9BF0
const NiColorA NiColorA::RED	    = { 1.f, 0.f, 0.f, 1.f };

// GAME - 0x11A9C00
const NiColorA NiColorA::GREEN	    = { 0.f, 1.f, 0.f, 1.f };

// GAME - 0x11A9C10
const NiColorA NiColorA::BLUE	    = { 0.f, 0.f, 1.f, 1.f };

// GAME - 0x11A9C20
const NiColorA NiColorA::YELLOW	    = { 1.f, 1.f, 0.f, 1.f };

// GAME - 0x11A9C30
const NiColorA NiColorA::MAGENTA    = { 1.f, 0.f, 1.f, 1.f };

// GAME - 0x11A9C40
const NiColorA NiColorA::CYAN		= { 0.f, 1.f, 1.f, 1.f };

NiColorA::NiColorA(const NiPoint3& arOther) noexcept : r(arOther.x), g(arOther.y), b(arOther.z), a(1.f) {}

NiColorA::NiColorA(const NiPoint4& arOther) noexcept : r(arOther.x), g(arOther.y), b(arOther.z), a(arOther.w) {}

NiColorA::NiColorA(const NiColor& arOther) noexcept : r(arOther.r), g(arOther.g), b(arOther.b), a(1.f) {}

NiColorA::NiColorA(const NiColor& arOther, float afA) noexcept : r(arOther.r), g(arOther.g), b(arOther.b), a(afA) {}