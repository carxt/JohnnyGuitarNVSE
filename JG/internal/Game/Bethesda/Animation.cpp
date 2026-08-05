#include "Animation.hpp"
#include "AnimIdle.hpp"

#ifdef GAME
// GAME - 0x494390
bool Animation::GetDelta(NiPoint3& arVector, const Actor* apActor, bool abRotation, bool abNoHeight) const {
    return ThisCall<bool>(0x494390, this, &arVector, apActor, abRotation, abNoHeight);
}

// GAME - 0x493930
bool Animation::UpdateIfRequired() {
    return ThisCall<bool>(0x493930, this);
}
#endif

// GAME - 0x490500
// GECK - 0x5107D0
bool Animation::AddAnimation(KFModel* apModel, bool abClone) {
#ifdef GAME
	return ThisCall<bool>(0x490500, this, apModel, abClone);
#else
	return ThisCall<bool>(0x5107D0, this, apModel, abClone);
#endif
}

// GAME - 0x490330
// GECK - 0x511EF0
void Animation::LoadSpecialAnims(BSSimpleList<const char*>* apAnimations, const char* apPath) {
#ifdef GAME
	ThisCall(0x490330, this, apAnimations, apPath);
#else
	ThisCall(0x511EF0, this, apAnimations, apPath);
#endif
}

// GAME - 0x8846C0
bool Animation::HasQueuedReload() const {
    return usQueuedReloadGroup != ANIM_GROUP_TYPE::NONE;
}

// GAME - 0x8DA3D0
TESIdleForm* Animation::GetIdleForm() const {
    return spAnimIdle ? spAnimIdle->pIdleForm : nullptr;
}

// GAME - 0x921E30
BSAnimGroupSequence* Animation::GetIdleAnimSequence() const {
    return spAnimIdle ? spAnimIdle->spSequence : nullptr;
}

// GAME - 0x491040
BSAnimGroupSequence* Animation::GetCurrentSequence(ANIM_GROUP_SECTION aeSection) const {
    if (aeSection == ANIM_GROUP_SECTION::WHOLE_BODY)
        aeSection = ANIM_GROUP_SECTION::MOVEMENT;
    else if (aeSection == ANIM_GROUP_SECTION::UPPER_BODY)
        aeSection = ANIM_GROUP_SECTION::WEAPON;
    return pCurrentSequences[aeSection];
}

// GAME - 0x453700
float Animation::GetTimePassed() const {
    return fTime;
}

// GAME - 0x4985F0
bool Animation::SpecialIdleDonePlaying() const {
	return ThisCall<bool>(0x4985F0, this);
}

#ifdef GAME
// GAME - 0x498F80
bool Animation::SpecialIdleWorking() const {
    return ThisCall<bool>(0x498F80, this);
}

// GAME - 0x498D30
bool Animation::SpecialIdleWorking(TESIdleForm* apIdle) const {
    return ThisCall<bool>(0x498D30, this, apIdle);
}

// GAME - 0x498EA0
bool Animation::SpecialIdleWorking(BSAnimGroupSequence* apAnimSequence) const {
	return ThisCall<bool>(0x498EA0, this, apAnimSequence);
}

// GAME - 0x497CA0
void Animation::SpecialIdleQueue(TESIdleForm* apIdle, ANIM_GROUP_SECTION aeGroupSection) {
    ThisCall(0x497CA0, this, apIdle, aeGroupSection);
}
#endif

// GAME - 0x497F20
// GECK - 0x511F80
void Animation::SpecialIdleAuto(TESIdleForm* apIdle, Actor* apActor, ANIM_GROUP_SECTION aeGroupSection, ANIM_IDLE_PLAY_TYPE aePlayType) {
#ifdef GAME
    ThisCall(0x497F20, this, apIdle, apActor, aeGroupSection, aePlayType);
#else
    ThisCall(0x511F80, this, apIdle, apActor, aeGroupSection, aePlayType);
#endif
}

// GAME - 0x498910
// GECK - 0x50F5E0
void Animation::SpecialIdleFree(bool abFreeQueued, bool abForceDelete) {
#ifdef GAME
    ThisCall(0x498910, this, abFreeQueued, abForceDelete);
#else
	ThisCall(0x50F5E0, this, abFreeQueued, abForceDelete);
#endif
}

// GAME - 0x494740
// GECK - 0x510550
BSAnimGroupSequence* Animation::PlayGroup(uint16_t aeGroup, ANIM_ACTION_FLAGS aeFlags, uint32_t auiLoopCount, ANIM_GROUP_SECTION aeSection) {
#ifdef GAME
    return ThisCall<BSAnimGroupSequence*>(0x494740, this, aeGroup, aeFlags, auiLoopCount, aeSection);
#else
	return ThisCall<BSAnimGroupSequence*>(0x510550, this, aeGroup, aeFlags, auiLoopCount, aeSection);
#endif
}

// GAME - 0x496080
// GECK - 0x50E870
void Animation::ClearGroup(ANIM_GROUP_SECTION aeSection, float afEaseOutTime) {
#ifdef GAME
	ThisCall(0x496080, this, aeSection, afEaseOutTime);
#else
	ThisCall(0x50E870, this, aeSection, afEaseOutTime);
#endif
}

// GAME - 0x4994F0
// GECK - 0x50ED40
void Animation::BlendOut(ANIM_GROUP_SECTION aeSection, bool abIronSightsToggle) {
#ifdef GAME
	ThisCall(0x4994F0, this, aeSection, abIronSightsToggle);
#else
	ThisCall(0x50ED40, this, aeSection, abIronSightsToggle);
#endif
}

// GAME - 0x499240
void Animation::ReloadTargets(bool abReload) {
    ThisCall(0x499240, this, abReload);
}

#ifdef GAME
// GAME - 0x496550
float Animation::GetSmallestHavokBlendValue(NiNode* apNode) {
	return ThisCall<float>(0x496550, this, apNode);
}
#endif

const char* Animation::GetGroupSectionName(ANIM_GROUP_SECTION aeSection) {
    if (aeSection == ANIM_GROUP_SECTION::NONE)
        return "None";
    else if (aeSection == ANIM_GROUP_SECTION::WHOLE_BODY)
        return "Whole Body";
    else if (aeSection == ANIM_GROUP_SECTION::UPPER_BODY)
        return "Upper Body";
    else {
#ifdef GAME
        return reinterpret_cast<const char**>(0x1199B2C)[aeSection];
#else
        return reinterpret_cast<const char**>(0xE9A5E4)[aeSection];
#endif
    }
}

const ANIM_GROUP_INFO* Animation::GetGroupInfo(ANIM_GROUP_TYPE aeGroup) {
#ifdef GAME
    return &reinterpret_cast<const ANIM_GROUP_INFO*>(0x11977D8)[aeGroup];
#else
    return &reinterpret_cast<const ANIM_GROUP_INFO*>(0xE98290)[aeGroup];
#endif
}

const char* Animation::GetGroupName(ANIM_GROUP_TYPE aeGroup) {
    if (aeGroup == ANIM_GROUP_TYPE::NONE)
        return "None";

    if (aeGroup > 244 || aeGroup < 0)
		return "Invalid";

    return GetGroupInfo(aeGroup)->pName;
}
