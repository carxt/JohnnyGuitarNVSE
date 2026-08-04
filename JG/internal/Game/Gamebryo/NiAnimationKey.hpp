#pragma once

#include "NiMemObject.hpp"

class NiStream;

class SPEC_EMPTY_BASES NiAnimationKey : public NiMemObject {
public:
	NiAnimationKey() : m_fTime(0) {};
	~NiAnimationKey() = default;

	struct _KeyContent {
		enum Content {
			FLOAT,
			POS,
			ROT,
			COLOR,
			TEXT,
			BOOL,
			COUNT
		};
	};
	using KeyContent = _KeyContent::Content;

	struct _KeyType {
		enum Type {
			NO_INTERPOLATE,
			LINEAR,
			BEZIER,
			TCB,
			EULER,
			STEP,
			COUNT
		};
	};
	using KeyType = _KeyType::Type;

	float m_fTime;

	void SetTime(float afTime);
	float GetTime() const;

	NiAnimationKey* GetKeyAt(uint32_t auiIndex, uint8_t aucKeySize) const;
};

ASSERT_SIZE(NiAnimationKey, 0x4);