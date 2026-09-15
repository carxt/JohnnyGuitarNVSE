#include "TESReactionForm.hpp"

// GAME - 0x717E50
BSSimpleList<GroupReaction*>* TESReactionForm::GetReactionList() {
    return &kReactions;
}

// GAME - 0x717E50
const BSSimpleList<GroupReaction*>* TESReactionForm::GetReactionList() const {
    return &kReactions;
}

// GAME - 0x48BF50
int32_t TESReactionForm::GetReaction(const TESForm* apForm) const {
#ifdef GAME
    return ThisCall<int32_t>(0x48BF50, this, apForm);
#else
    if (apForm) {
        auto pIter = GetReactionList();
        while (pIter && pIter->GetItem()) {
            GroupReaction* pReaction = pIter->GetItem();
            if (pReaction->pForm == apForm)
                return pReaction->iReaction;

            pIter = pIter->GetNext();
        }
    }
    return 0;
#endif
}

// GAME - 0x48BFC0
// GECK - 0x509CE0
void TESReactionForm::SetReaction(TESForm* apForm, int32_t aiReaction) {
#ifdef GAME
    ThisCall(0x48BFC0, this, apForm, aiReaction);
#else
    ThisCall(0x509CE0, this, apForm, aiReaction);
#endif
}

#ifdef GAME
// GAME - 0x48C0B0
void TESReactionForm::ModReaction(TESForm* apForm, int32_t aiReaction) {
    ThisCall(0x48C0B0, this, apForm, aiReaction);
}
#endif

// GAME - 0x48C1B0
// GECK - 0x509200
FIGHT_REACTION TESReactionForm::GetFactionCombatRelation(const TESForm* apForm) const {
#ifdef GAME
    return ThisCall<FIGHT_REACTION>(0x48C1B0, this, apForm);
#else
    return ThisCall<FIGHT_REACTION>(0x509200, this, apForm);
#endif
}

#ifdef GAME
// GAME - 0x48C220
void TESReactionForm::SetFightReaction(TESForm* apForm, FIGHT_REACTION aeFightReaction) {
    ThisCall(0x48C220, this, apForm, aeFightReaction);
}
#endif
