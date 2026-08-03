#include "AlchemyItem.hpp"

// GAME - 0x4029D0
bool AlchemyItem::GetFlag(Flags aeFlag) const {
    return kData.ucFlags.Get(aeFlag);
}

// GAME - 0x402A20
void AlchemyItem::SetFlag(Flags aeFlag, bool abVal) {
    kData.ucFlags.Set(aeFlag, abVal);
}

// GAME - 0x4030B0
SpellItem* AlchemyItem::GetAddictionItem() const {
    return kData.pAddictionItem;
}

// GAME - 0x874460
void AlchemyItem::SetAddictionItem(SpellItem* apItem) {
    kData.pAddictionItem = apItem;
}

// GAME - 0x644A50
float AlchemyItem::GetAddictionChance() const {
    return kData.fAddictionChance;
}

void AlchemyItem::SetAddictionChance(float afChance) {
    kData.fAddictionChance = afChance;
}

// GAME - 0x9ACCE0
TESSound* AlchemyItem::GetConsumptionSound() const {
    return kData.pConsumeSound;
}

// GAME - 0x9ACCE0
void AlchemyItem::SetConsumptionSound(TESSound* apSound) {
    kData.pConsumeSound = apSound;
}

#ifdef GAME
// GAME - 0x4036D0
bool AlchemyItem::IsWater() const {
    return ThisCall<bool>(0x4036D0, this);
}
#endif
