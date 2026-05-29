#include "MagicItem.hpp"

// GAME - 0x40A1E0
uint32_t MagicItem::GetMagicItemFormID() const {
	return ThisCall<uint32_t>(0x40A1E0, this);
}
