#pragma once

#include "Bethesda/BSMemObject.hpp"
#include "NiColor.hpp"
#include "NiPoint3.hpp"

class NiColorA {
public:
	NiColorA() {};
	NiColorA(const NiColor& arColor) : r(arColor.r), g(arColor.g), b(arColor.b), a(1.0f) {};
	NiColorA(const NiColor& arColor, float a) : r(arColor.r), g(arColor.g), b(arColor.b), a(a) {};
	NiColorA(float r, float g, float b) : r(r), g(g), b(b), a(1.0f) {};
	NiColorA(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {};
	NiColorA(float f) : r(f), g(f), b(f), a(f) {};

	float r;
	float g;
	float b;
	float a;

	const float& operator[] (int32_t i) const { return reinterpret_cast<const float*>(this)[i]; };
	float& operator[] (int32_t i) { return reinterpret_cast<float*>(this)[i]; };

	operator float* () const { return (float*)this; };

	NiColorA operator*(const float f) const {
		return NiColorA(r * f, g * f, b * f, a * f);
	};

	NiColorA operator*(const NiColorA& color) const {
		return NiColorA(r * color.r, g * color.g, b * color.b, a * color.a);
	};

	bool operator==(const NiColorA& color) const {
		return r == color.r && g == color.g && b == color.b && a == color.a;
	};

	bool operator==(const float f) const {
		return r == f && g == f && b == f && a == f;
	};

	bool operator!=(const NiColorA& color) const {
		return r != color.r || g != color.g || b != color.b || a != color.a;
	};

	bool operator>(const float f) const {
		return r > f && g > f && b > f && a > f;
	}

	bool operator<(const float f) const {
		return r < f && g < f && b < f && a < f;
	}

	NiColorA operator*=(const float f) {
		r *= f;
		g *= f;
		b *= f;
		a *= f;
		return *this;
	};

	NiColorA operator=(const NiColor& color) {
		r = color.r;
		g = color.g;
		b = color.b;
		return *this;
	};

	NiColorA operator=(const NiPoint3& color) {
		r = color.x;
		g = color.y;
		b = color.z;
		return *this;
	};

	NiColorA operator+(const NiColorA& color) const {
		return NiColorA(r + color.r, g + color.g, b + color.b, a + color.a);
	}

	bool IsVisible() const {
		return a > 0.f && (r > 0.f || g > 0.f || b > 0.f);
	}

	static const NiColorA BLACK;
	static const NiColorA WHITE;
	static const NiColorA RED;
	static const NiColorA GREEN;
	static const NiColorA BLUE;
	static const NiColorA YELLOW;
	static const NiColorA CYAN;
	static const NiColorA MAGENTA;

	static NiColorA& GetRandomColor(float afAlpha = 1.f) {
		static NiColorA kColor;
		kColor.r = (float)(rand() % 255) / 255.f;
		kColor.g = (float)(rand() % 255) / 255.f;
		kColor.b = (float)(rand() % 255) / 255.f;
		kColor.a = afAlpha;
		return kColor;
	}
};

ASSERT_SIZE(NiColorA, 0x10);