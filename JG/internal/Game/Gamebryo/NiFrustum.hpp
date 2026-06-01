#pragma once

class NiFrustum {
public:
	NiFrustum() : m_fLeft(0.0f), m_fRight(0.0f), m_fTop(0.0f), m_fBottom(0.0f), m_fNear(0.0f), m_fFar(0.0f), m_bOrtho(false) {}
	NiFrustum(float afLeft, float afRight, float afTop, float afBottom, float afNear, float afFar, bool abOrtho) {
		m_fLeft = afLeft;
		m_fRight = afRight;
		m_fTop = afTop;
		m_fBottom = afBottom;
		m_fNear = afNear;
		m_fFar = afFar;
		m_bOrtho = abOrtho;
	}
	~NiFrustum() {};

	float	m_fLeft;
	float	m_fRight;
	float	m_fTop;
	float	m_fBottom;
	float	m_fNear;
	float	m_fFar;
	bool	m_bOrtho;
};

ASSERT_SIZE(NiFrustum, 0x1C);