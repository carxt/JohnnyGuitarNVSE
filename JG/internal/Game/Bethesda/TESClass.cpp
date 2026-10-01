#include "TESClass.hpp"

ActorValue::Index TESClass::GetTagSkill(uint32_t auiIndex) const {
    assert(auiIndex < GetTagSkillCount());
    return kData.eTagSkills[auiIndex];
}

// GAME - 0x5F6E80
void TESClass::SetTagSkill(uint32_t auiIndex, ActorValue::Index aeSkill) {
    assert(auiIndex < GetTagSkillCount());
#ifdef GAME
    ThisCall(0x5F6E80, this, auiIndex, aeSkill);
#else
    if (ActorValue::IsSkill(aeSkill) || aeSkill == ActorValue::Index::NONE)
        kData.eTagSkills[auiIndex] = aeSkill;
#endif
}

// GAME - 0x5A5F40
bool TESClass::IsTagSkill(ActorValue::Index aeSkill) const {
#ifdef GAME
    return ThisCall<bool>(0x5A5F40, this, aeSkill);
#else
    return kData.eTagSkills[0] == aeSkill
        || kData.eTagSkills[1] == aeSkill
        || kData.eTagSkills[2] == aeSkill
        || kData.eTagSkills[3] == aeSkill;
#endif
}

bool TESClass::IsPlayable() const {
    return kData.ucFlags.bPlayable;
}

void TESClass::SetPlayable(bool abVal) {
    kData.ucFlags.bPlayable = abVal;
}

// GAME - 0x5F6E60
bool TESClass::IsGuard() const {
    return kData.ucFlags.bGuard;
}

void TESClass::SetGuard(bool abVal) {
    kData.ucFlags.bGuard = abVal;
}

// GAME - 0x5F6DD0
ActorValue::Index TESClass::GetTrainingSkill() const {
#ifdef GAME
    return ThisCall<ActorValue::Index>(0x5F6DD0, this);
#else
    return ActorValue::ToActorValue(ActorValue::Section::SKILL, kData.ucTrainingSkill);
#endif
}

void TESClass::SetTrainingSkill(ActorValue::Index aeSkill) {
    if (ActorValue::IsSkill(aeSkill))
        kData.ucTrainingLevel = ActorValue::ToArrayIndex(ActorValue::Section::SKILL, aeSkill);
}

uint32_t TESClass::GetTrainingSkillLevel() const {
    return kData.ucTrainingLevel;
}

void TESClass::SetTrainingSkillLevel(uint8_t aucLevel) {
    kData.ucTrainingLevel = aucLevel;
}

// GAME - 0x5D9660
uint32_t TESClass::GetTagSkillCount() {
    return 4;
}
