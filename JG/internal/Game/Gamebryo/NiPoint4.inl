#pragma once

#include "NiPoint4.hpp"

inline NiPoint4::NiPoint4() noexcept {}

inline NiPoint4::NiPoint4(float afValue) noexcept : x(afValue), y(afValue), z(afValue), w(afValue) {}

inline NiPoint4::NiPoint4(float afX, float afY, float afZ, float afW) noexcept : x(afX), y(afY), z(afZ), w(afW) {}

inline NiPoint4::NiPoint4(const NiPoint4& arOther) noexcept : x(arOther.x), y(arOther.y), z(arOther.z), w(arOther.w) {}

inline float& NiPoint4::operator[](uint32_t i) noexcept {
	ASSUME_ASSERT(i < 4);
	if (std::is_constant_evaluated()) {
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

inline const float& NiPoint4::operator[](uint32_t i) const noexcept {
	ASSUME_ASSERT(i < 4);
	if (std::is_constant_evaluated()) {
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

inline NiPoint4::operator float*() noexcept {
	return &x;
}

inline bool NiPoint4::operator==(const NiPoint4& arOther) const noexcept { 
	return x == arOther.x && y == arOther.y && z == arOther.z && w == arOther.w; 
}

inline NiPoint4 NiPoint4::operator-() const noexcept { 
	return NiPoint4(-x, -y, -z, -w); 
}

inline NiPoint4 NiPoint4::operator+(const NiPoint4& arOther) const noexcept {
	return NiPoint4(x + arOther.x, y + arOther.y, z + arOther.z, w + arOther.w); 
}

inline NiPoint4 NiPoint4::operator-(const NiPoint4& arOther) const noexcept {
	return NiPoint4(x - arOther.x, y - arOther.y, z - arOther.z, w - arOther.w); 
}

inline float	NiPoint4::operator*(const NiPoint4& arOther) const noexcept {
	return x * arOther.x + y * arOther.y + z * arOther.z + w * arOther.w;
}

inline NiPoint4 NiPoint4::operator/(const NiPoint4& arOther) const noexcept {
	return NiPoint4(x / arOther.x, y / arOther.y, z / arOther.z, w / arOther.w);
}

inline NiPoint4 NiPoint4::operator+(float afVal) const noexcept {
	return NiPoint4(x + afVal, y + afVal, z + afVal, w + afVal);
}

inline NiPoint4 NiPoint4::operator-(float afVal) const noexcept {
	return NiPoint4(x - afVal, y - afVal, z - afVal, w - afVal);
}

inline NiPoint4 NiPoint4::operator*(float afVal) const noexcept {
	return NiPoint4(x * afVal, y * afVal, z * afVal, w * afVal);
}

inline NiPoint4 NiPoint4::operator/(float afVal) const noexcept {
	return NiPoint4(x / afVal, y / afVal, z / afVal, w / afVal);
}

inline NiPoint4& NiPoint4::operator+=(const NiPoint4& arOther) noexcept {
	x += arOther.x;
	y += arOther.y;
	z += arOther.z;
	w += arOther.w; 
	return *this; 
}

inline NiPoint4& NiPoint4::operator-=(const NiPoint4& arOther) noexcept {
	x -= arOther.x;
	y -= arOther.y;
	z -= arOther.z;
	w -= arOther.w; 
	return *this; 
}

inline NiPoint4& NiPoint4::operator*=(const NiPoint4& arOther) noexcept {
	x *= arOther.x;
	y *= arOther.y;
	z *= arOther.z;
	w *= arOther.w; 
	return *this; 
}

inline NiPoint4& NiPoint4::operator/=(const NiPoint4& arOther) noexcept {
	x /= arOther.x;
	y /= arOther.y;
	z /= arOther.z;
	w /= arOther.w; 
	return *this; 
}

inline NiPoint4& NiPoint4::operator+=(float afVal) noexcept {
	x += afVal;
	y += afVal;
	z += afVal;
	w += afVal;
	return *this; 
}

inline NiPoint4& NiPoint4::operator-=(float afVal) noexcept {
	x -= afVal;
	y -= afVal;
	z -= afVal;
	w -= afVal;
	return *this; 
}

inline NiPoint4& NiPoint4::operator*=(float afVal) noexcept {
	x *= afVal;
	y *= afVal;
	z *= afVal;
	w *= afVal;
	return *this; 
}

inline NiPoint4& NiPoint4::operator/=(float afVal) noexcept {
	x /= afVal;
	y /= afVal;
	z /= afVal;
	w /= afVal;
	return *this; 
}

inline NiPoint4 operator*(float afVal, const NiPoint4& arVec) noexcept { 
	return NiPoint4(arVec.x * afVal, arVec.y * afVal, arVec.z * afVal, arVec.w * afVal); 
}

inline float NiPoint4::Length() const noexcept {
	return std::sqrt(x * x + y * y + z * z + w * w);
}

inline float NiPoint4::XYLength() const noexcept {
	return std::sqrt(x * x + y * y);
}

inline float NiPoint4::XYZLength() const noexcept {
	return std::sqrt(x * x + y * y + z * z);
}

inline float NiPoint4::SqrLength() const noexcept {
	return std::sqrt(x * x + y * y + z * z + w * w);
}

inline float NiPoint4::SqrXYLength() const noexcept {
	return std::sqrt(x * x + y * y);
}

inline float NiPoint4::SqrXYZLength() const noexcept {
	return std::sqrt(x * x + y * y + z * z);
}

inline float NiPoint4::Dot(const NiPoint4& arOther) const noexcept {
	return x * arOther.x + y * arOther.y + z * arOther.z + w * arOther.w;
}

inline NiPoint4 NiPoint4::Cross(const NiPoint4& arOther) const noexcept {
	return NiPoint4(w * arOther.y - y * arOther.w,
					x * arOther.w - w * arOther.x,
					y * arOther.x - x * arOther.y,
					z * arOther.x - x * arOther.z);
}

inline NiPoint4 NiPoint4::UnitCross(const NiPoint4& arOther) const noexcept {
	NiPoint4 kCross = Cross(arOther);
	float fLength = kCross.Length();
	if (fLength > 0.000001f)
		return kCross / fLength;
	else
		return NiPoint4::ZERO;
}

inline void NiPoint4::Unitize() noexcept {
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

inline float NiPoint4::UnitizeGetLength() noexcept {
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
