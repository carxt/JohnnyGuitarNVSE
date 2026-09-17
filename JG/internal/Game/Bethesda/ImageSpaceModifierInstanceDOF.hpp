#pragma once

#include "ImageSpaceModifierInstanceTemp.hpp"

class ImageSpaceModifierInstanceDOF : public ImageSpaceModifierInstanceTemp {
public:
	ImageSpaceModifierInstanceDOF();
	virtual ~ImageSpaceModifierInstanceDOF();

	struct _DOFMode {
		enum Mode {
			FRONT_BACK		= 0,
			FRONT			= 1,
			BACK			= 2,
			FRONT_BACK_MASK	= 3,
			FRONT_MASK		= 4,
			BACK_MASK		= 5,
			NONE			= 6
		};
	};
	using DOFMode = _DOFMode::Mode;

	float		fDistance;
	float		fRange;
	float		fMotionBlur;
	DOFMode		eMode;

	float GetDistance() const;
	void SetDistance(float afDistance);

	float GetRange() const;
	void SetRange(float afRange);

	float GetMotionBlur() const;
	void SetMotionBlur(float afMotionBlur);

	DOFMode GetMode() const;
	void SetMode(DOFMode aeMode);
};

ASSERT_SIZE(ImageSpaceModifierInstanceDOF, 0x30);