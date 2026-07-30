#include "NiPoint4.hpp"
#include "NiPoint2.hpp"
#include "NiPoint3.hpp"

const NiPoint4 NiPoint4::UNIT_X		= { 1.f, 0.f, 0.f, 0.f};
const NiPoint4 NiPoint4::UNIT_Y		= { 0.f, 1.f, 0.f, 0.f};
const NiPoint4 NiPoint4::UNIT_Z		= { 0.f, 0.f, 1.f, 0.f};
const NiPoint4 NiPoint4::UNIT_W		= { 0.f, 0.f, 0.f, 1.f};
const NiPoint4 NiPoint4::UNIT_ALL	= { 1.f, 1.f, 1.f, 1.f};
const NiPoint4 NiPoint4::ZERO		= { 0.f, 0.f, 0.f, 0.f};

NiPoint4::NiPoint4() noexcept {}

NiPoint4::NiPoint4(float afValue) noexcept : x(afValue), y(afValue), z(afValue), w(afValue) {}

NiPoint4::NiPoint4(float afX, float afY, float afZ, float afW) noexcept : x(afX), y(afY), z(afZ), w(afW) {}

NiPoint4::NiPoint4(const NiPoint4& arOther) noexcept : x(arOther.x), y(arOther.y), z(arOther.z), w(arOther.w) {}

NiPoint4::NiPoint4(const NiPoint2& arOther) noexcept : x(arOther.x), y(arOther.y), z(0.f), w(0.f) {}

NiPoint4::NiPoint4(const NiPoint3& arOther) noexcept : x(arOther.x), y(arOther.y), z(arOther.z), w(0.f) {}

NiPoint4::NiPoint4(const NiPoint3& arOther, float afW) noexcept : x(arOther.x), y(arOther.y), z(arOther.z), w(afW) {}


float& NiPoint4::operator[](uint32_t i) noexcept {
	ASSUME_ASSERT(i < 4);
	if consteval {
		switch (i) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
			case 3: return w;
		}
	}
	else {
		return reinterpret_cast<float*>(this)[i];
	}
}

const float& NiPoint4::operator[](uint32_t i) const noexcept {
	ASSUME_ASSERT(i < 4);
	if consteval {
		switch (i) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
			case 3: return w;
		}
	}
	else {
		return reinterpret_cast<const float*>(this)[i];
	}
}

NiPoint4::operator float* () noexcept {
	return &x;
}

bool NiPoint4::operator==(const NiPoint4& arOther) const noexcept {
	return x == arOther.x && y == arOther.y && z == arOther.z && w == arOther.w;
}

NiPoint4 NiPoint4::operator-() const noexcept {
	return NiPoint4(-x, -y, -z, -w);
}

NiPoint4 NiPoint4::operator+(const NiPoint4& arOther) const noexcept {
	return NiPoint4(x + arOther.x, y + arOther.y, z + arOther.z, w + arOther.w);
}

NiPoint4 NiPoint4::operator-(const NiPoint4& arOther) const noexcept {
	return NiPoint4(x - arOther.x, y - arOther.y, z - arOther.z, w - arOther.w);
}

float	NiPoint4::operator*(const NiPoint4& arOther) const noexcept {
	return x * arOther.x + y * arOther.y + z * arOther.z + w * arOther.w;
}

NiPoint4 NiPoint4::operator/(const NiPoint4& arOther) const noexcept {
	return NiPoint4(x / arOther.x, y / arOther.y, z / arOther.z, w / arOther.w);
}

NiPoint4 NiPoint4::operator+(float afVal) const noexcept {
	return NiPoint4(x + afVal, y + afVal, z + afVal, w + afVal);
}

NiPoint4 NiPoint4::operator-(float afVal) const noexcept {
	return NiPoint4(x - afVal, y - afVal, z - afVal, w - afVal);
}

NiPoint4 NiPoint4::operator*(float afVal) const noexcept {
	return NiPoint4(x * afVal, y * afVal, z * afVal, w * afVal);
}

NiPoint4 NiPoint4::operator/(float afVal) const noexcept {
	return NiPoint4(x / afVal, y / afVal, z / afVal, w / afVal);
}

NiPoint4& NiPoint4::operator+=(const NiPoint4& arOther) noexcept {
	x += arOther.x;
	y += arOther.y;
	z += arOther.z;
	w += arOther.w;
	return *this;
}

NiPoint4& NiPoint4::operator-=(const NiPoint4& arOther) noexcept {
	x -= arOther.x;
	y -= arOther.y;
	z -= arOther.z;
	w -= arOther.w;
	return *this;
}

NiPoint4& NiPoint4::operator*=(const NiPoint4& arOther) noexcept {
	x *= arOther.x;
	y *= arOther.y;
	z *= arOther.z;
	w *= arOther.w;
	return *this;
}

NiPoint4& NiPoint4::operator/=(const NiPoint4& arOther) noexcept {
	x /= arOther.x;
	y /= arOther.y;
	z /= arOther.z;
	w /= arOther.w;
	return *this;
}

NiPoint4& NiPoint4::operator+=(float afVal) noexcept {
	x += afVal;
	y += afVal;
	z += afVal;
	w += afVal;
	return *this;
}

NiPoint4& NiPoint4::operator-=(float afVal) noexcept {
	x -= afVal;
	y -= afVal;
	z -= afVal;
	w -= afVal;
	return *this;
}

NiPoint4& NiPoint4::operator*=(float afVal) noexcept {
	x *= afVal;
	y *= afVal;
	z *= afVal;
	w *= afVal;
	return *this;
}

NiPoint4& NiPoint4::operator/=(float afVal) noexcept {
	x /= afVal;
	y /= afVal;
	z /= afVal;
	w /= afVal;
	return *this;
}

NiPoint4 operator*(float afVal, const NiPoint4& arVec) noexcept {
	return NiPoint4(arVec.x * afVal, arVec.y * afVal, arVec.z * afVal, arVec.w * afVal);
}

void NiPoint4::operator=(const NiPoint2& arOther) noexcept {
	x = arOther.x;
	y = arOther.y;
}

void NiPoint4::operator=(const NiPoint3& arOther) noexcept {
	x = arOther.x;
	y = arOther.y;
	z = arOther.z;
}

bool NiPoint4::IsOk() const noexcept {
	return x != FLT_MAX && _isnan(x) == 0 && _finite(x) != 0
		&& y != FLT_MAX && _isnan(y) == 0 && _finite(y) != 0
		&& z != FLT_MAX && _isnan(z) == 0 && _finite(z) != 0
		&& w != FLT_MAX && _isnan(w) == 0 && _finite(w) != 0;
}

float NiPoint4::Length() const noexcept {
	return std::sqrt(x * x + y * y + z * z + w * w);
}

float NiPoint4::XYLength() const noexcept {
	return std::sqrt(x * x + y * y);
}

float NiPoint4::XYZLength() const noexcept {
	return std::sqrt(x * x + y * y + z * z);
}

float NiPoint4::SqrLength() const noexcept {
	return std::sqrt(x * x + y * y + z * z + w * w);
}

float NiPoint4::SqrXYLength() const noexcept {
	return std::sqrt(x * x + y * y);
}

float NiPoint4::SqrXYZLength() const noexcept {
	return std::sqrt(x * x + y * y + z * z);
}

float NiPoint4::Dot(const NiPoint4& arOther) const noexcept {
	return x * arOther.x + y * arOther.y + z * arOther.z + w * arOther.w;
}

NiPoint4 NiPoint4::Cross(const NiPoint4& arOther) const noexcept {
	return NiPoint4(w * arOther.y - y * arOther.w,
		x * arOther.w - w * arOther.x,
		y * arOther.x - x * arOther.y,
		z * arOther.x - x * arOther.z);
}

NiPoint4 NiPoint4::UnitCross(const NiPoint4& arOther) const noexcept {
	NiPoint4 kCross = Cross(arOther);
	float fLength = kCross.Length();
	if (fLength > 0.000001f)
		return kCross / fLength;
	else
		return NiPoint4::ZERO;
}

void NiPoint4::Unitize() noexcept {
	const float fLength = Length();
	if (fLength <= 0.000001f) [[unlikely]] {
		x = 0.f;
		y = 0.f;
		z = 0.f;
		w = 0.f;
	}
	else [[likely]] {
		const float fRecip = 1.f / fLength;
		x *= fRecip;
		y *= fRecip;
		z *= fRecip;
		w *= fRecip;
	}
}

float NiPoint4::UnitizeGetLength() noexcept {
	const float fLength = Length();
	if (fLength <= 0.000001f) [[unlikely]] {
		x = 0.f;
		y = 0.f;
		z = 0.f;
		w = 0.f;
	}
	else [[likely]] {
		const float fRecip = 1.f / fLength;
		x *= fRecip;
		y *= fRecip;
		z *= fRecip;
		w *= fRecip;
	}
	return fLength;
}