#pragma once

#include "NiMemObject.hpp"

template <class T> 
class SPEC_EMPTY_BASES NiRect : public NiMemObject {
public:
	NiRect(T left = T(0), T right = T(0), T top = T(0), T bottom = T(0)) {
		m_left = left;
		m_right = right;
		m_top = top;
		m_bottom = bottom;
	}

	T m_left, m_right, m_top, m_bottom;
};

ASSERT_SIZE(NiRect<float>, 0x10);