#include "NiFogProperty.hpp"

// GAME - 0x891170
const NiColor& NiFogProperty::GetFogColor() const {
	return m_kColor;
}

// GAME - 0x633BF0
void NiFogProperty::SetFogColor(const NiColor& arColor) {
	m_kColor = arColor;
}
