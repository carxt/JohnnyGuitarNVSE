#include "MagicItem.hpp"

#ifdef GAME
// GAME - 0x40A1E0
FormID MagicItem::GetMagicItemFormID() const {
	return ThisCall<FormID>(0x40A1E0, this);
}
#endif
