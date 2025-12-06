#include "NiTypes.h"
#include "cmath"

const NiMatrix3 NiMatrix3::IDENTITY = NiMatrix3(1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f);

void NiMatrix3::MakeXRotation(float fAngle) {
	float sn = std::sin(fAngle);
	float cs = std::cos(fAngle);

	cr[0][0] = 1.0f;
	cr[0][1] = 0.0f;
	cr[0][2] = 0.0f;
	cr[1][0] = 0.0f;
	cr[1][1] = cs;
	cr[1][2] = sn;
	cr[2][0] = 0.0f;
	cr[2][1] = -sn;
	cr[2][2] = cs;
}

void NiMatrix3::MakeYRotation(float fAngle) {
	float sn = std::sin(fAngle);
	float cs = std::cos(fAngle);

	cr[0][0] = cs;
	cr[0][1] = 0.0f;
	cr[0][2] = -sn;
	cr[1][0] = 0.0f;
	cr[1][1] = 1.0f;
	cr[1][2] = 0.0f;
	cr[2][0] = sn;
	cr[2][1] = 0.0f;
	cr[2][2] = cs;
}

void NiMatrix3::MakeZRotation(float fAngle) {
	float sn = std::sin(fAngle);
	float cs = std::cos(fAngle);

	cr[0][0] = cs;
	cr[0][1] = sn;
	cr[0][2] = 0.0f;
	cr[1][0] = -sn;
	cr[1][1] = cs;
	cr[1][2] = 0.0f;
	cr[2][0] = 0.0f;
	cr[2][1] = 0.0f;
	cr[2][2] = 1.0f;
}

NiMatrix3 NiMatrix3::operator* (const NiMatrix3& mat) const {
	NiMatrix3 result;
	result.cr[0][0] =
		cr[0][0] * mat.cr[0][0] +
		cr[0][1] * mat.cr[1][0] +
		cr[0][2] * mat.cr[2][0];
	result.cr[1][0] =
		cr[1][0] * mat.cr[0][0] +
		cr[1][1] * mat.cr[1][0] +
		cr[1][2] * mat.cr[2][0];
	result.cr[2][0] =
		cr[2][0] * mat.cr[0][0] +
		cr[2][1] * mat.cr[1][0] +
		cr[2][2] * mat.cr[2][0];
	result.cr[0][1] =
		cr[0][0] * mat.cr[0][1] +
		cr[0][1] * mat.cr[1][1] +
		cr[0][2] * mat.cr[2][1];
	result.cr[1][1] =
		cr[1][0] * mat.cr[0][1] +
		cr[1][1] * mat.cr[1][1] +
		cr[1][2] * mat.cr[2][1];
	result.cr[2][1] =
		cr[2][0] * mat.cr[0][1] +
		cr[2][1] * mat.cr[1][1] +
		cr[2][2] * mat.cr[2][1];
	result.cr[0][2] =
		cr[0][0] * mat.cr[0][2] +
		cr[0][1] * mat.cr[1][2] +
		cr[0][2] * mat.cr[2][2];
	result.cr[1][2] =
		cr[1][0] * mat.cr[0][2] +
		cr[1][1] * mat.cr[1][2] +
		cr[1][2] * mat.cr[2][2];
	result.cr[2][2] =
		cr[2][0] * mat.cr[0][2] +
		cr[2][1] * mat.cr[1][2] +
		cr[2][2] * mat.cr[2][2];
	return result;
}

#include <Utilities.h>