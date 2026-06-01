#pragma once

#include "Bethesda/BSMemObject.hpp"
#include "NiPoint3.hpp"

class NiColor {
public:
	NiColor() {};
	NiColor(float r, float g, float b) : r(r), g(g), b(b) {};
	NiColor(float r, float g, float b, float a) : r(r), g(g), b(b) {};
	NiColor(float f) : r(f), g(f), b(f) {};

	float r;
	float g;
	float b;

	const float& operator[] (int32_t i) const { return reinterpret_cast<const float*>(this)[i]; };
	float& operator[] (int32_t i) { return reinterpret_cast<float*>(this)[i]; };

	operator float* () const { return (float*)this; };

	NiColor operator*(const float f) const {
		return NiColor(r * f, g * f, b * f);
	};

	NiColor operator*(const NiColor& color) const {
		return NiColor(r * color.r, g * color.g, b * color.b);
	};

	NiColor operator/(const float f) const {
		return NiColor(r / f, g / f, b / f);
	};

	NiColor operator/(const NiColor& color) const {
		return NiColor(r / color.r, g / color.g, b / color.b);
	};

	bool operator==(const NiColor& color) const {
		return r == color.r && g == color.g && b == color.b;
	};

	bool operator==(const float f) const {
		return r == f && g == f && b == f;
	};

	bool operator!=(const NiColor& color) const {
		return r != color.r || g != color.g || b != color.b;
	};

	bool operator!=(const float f) const {
		return r != f && g != f && b != f;
	};

	bool operator>(const float f) const {
		return r > f && g > f && b > f;
	}

	bool operator<(const float f) const {
		return r < f && g < f && b < f;
	}

	NiColor operator*=(const float f) {
		r *= f;
		g *= f;
		b *= f;
		return *this;
	};

	NiColor operator=(const NiPoint3& color) {
		r = color.x;
		g = color.y;
		b = color.z;
		return *this;
	};

	operator bool() const {
		return r != 0.0f || g != 0.0f || b != 0.0f;
	};

	const char* GetViewerStrings(const char* apText);

	float Luminance() const {
		return r * 0.31f + g * 0.36f + b * 0.32f;
	};

	NiColor Min(float f) {
		NiColor comp = NiColor(f);
		if ((*this) > f) {
			return comp;
		}
		return *this;
	};

	NiColor Max(float f) {
		NiColor comp = NiColor(f);
		if ((*this) < f) {
			return comp;
		}
		return *this;
	};


	static NiColor Lerp(const NiColor& to, const NiColor& from, float by) {
		return NiColor(to.r * (1 - by) + from.r * by,
			to.g * (1 - by) + from.g * by,
			to.b * (1 - by) + from.b * by);
	}

	bool IsVisible() const {
		return r > 0.f || g > 0.f || b > 0.f;
	}

	static const NiColor BLACK;
	static const NiColor WHITE;
	static const NiColor RED;
	static const NiColor GREEN;
	static const NiColor BLUE;
	static const NiColor YELLOW;
	static const NiColor CYAN;
	static const NiColor MAGENTA;
};

ASSERT_SIZE(NiColor, 0xC);