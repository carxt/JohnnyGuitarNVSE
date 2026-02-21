#pragma once

#include "TESObject.hpp"

class NiNode;

class TESBoundObject : public TESObject {
public:
	TESBoundObject();
	~TESBoundObject();

	virtual NiNode* Clone3DAlt(TESObjectREFR* apRequester);
	virtual bool	ReplaceModelAlt(const char* apPath);

	struct Bounds {
		Bounds() : x(0), y(0), z(0) {};
		Bounds(int16_t aX, int16_t aY, int16_t aZ) : x(aX), y(aY), z(aZ) {};
		int16_t x = 0;
		int16_t y = 0;
		int16_t z = 0;

		Bounds operator-(const Bounds& aOther) const;

		float Length() const;
	};

	struct BoundData {
		Bounds kMin;
		Bounds kMax;
	};

	BoundData kBoundData;

	float GetBoundSize() const;
};

ASSERT_SIZE(TESBoundObject, 0x30)