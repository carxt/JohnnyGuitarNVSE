#include "NiInterpolator.hpp"
#include <limits>

void NiInterpolator::ForceNextUpdate() {
	m_fLastTime = -FLT_MAX;
}
