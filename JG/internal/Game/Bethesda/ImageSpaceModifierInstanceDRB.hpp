#pragma once

#include "ImageSpaceModifierInstanceTemp.hpp"
#include "Gamebryo/NiPoint2.hpp"

class ImageSpaceModifierInstanceDRB : public ImageSpaceModifierInstanceTemp {
public:
	struct _DOFMode {
		enum Mode {
			FRONT_BACK	= 0,
			FRONT		= 1,
			BACK		= 2,
			NONE		= 3
		};
	};
	using DOFMode = _DOFMode::Mode;

	float		fRampup;
	float		fStart;
	float		fRampdown;
	float		fDownStart;
	NiPoint2	kCenter;
	float		fDistance;
	float		fRange;
	DOFMode		eMode;

	float GetRampup() const;
	void SetRampup(float afVal);

	float GetStart() const;
	void SetStart(float afVal);

	float GetRampdown() const;
	void SetRampdown(float afVal);

	float GetDownStart() const;
	void SetDownStart(float afVal);

	void SetCenter(const NiPoint2& arCenter);
	NiPoint2 GetCenter() const;

	float GetDistance() const;
	void SetDistance(float afDistance);

	float GetRange() const;
	void SetRange(float afRange);

	DOFMode GetMode() const;
	void SetMode(DOFMode aeMode);
};

ASSERT_SIZE(ImageSpaceModifierInstanceDRB, 0x44);