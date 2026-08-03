#include "NiInterpolator.hpp"

void NiInterpolator::ForceNextUpdate() {
	m_fLastTime = -FLT_MAX;
}
