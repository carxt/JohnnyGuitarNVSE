#include "TESCaravanDeck.hpp"

// GAME - 0x59BB30
BSSimpleList<TESCaravanCard*>* TESCaravanDeck::GetCaravanDeck() const {
    return pDeck;
}
