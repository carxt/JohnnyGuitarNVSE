#include "MediaLocationController.hpp"

// GAME - 0x595CF0
MediaLocationController::DeadRepState MediaLocationController::GetDeadRep() const {
    return DeadRepState(uiFlags.eDeadRep);
}

// GAME - 0x598000
MediaLocationController::LoopState MediaLocationController::GetLoop() const {
    return LoopState(uiFlags.eLoop);
}

// GAME - 0x595E80
bool MediaLocationController::GetDefaultTime() const {
    return uiFlags.bDefaultTime;
}

// GAME - 0x598020
bool MediaLocationController::GetDay() const {
    return bIsDay;
}

// GAME - 0x71AA80
bool MediaLocationController::GetTension() const {
    return bInTension;
}

// GAME - 0x595D30
bool MediaLocationController::GetDayNight() const {
    return ThisCall<bool>(0x595D30, this);
}

uint32_t MediaLocationController::GetLocationDelay() const {
    return uiLocationDelay;
}

// GAME - 0x7037C0
void MediaLocationController::SetLocationDelay(uint32_t auiDelay) {
    uiLocationDelay = auiDelay;
}

// GAME - 0x595560
MediaSet* MediaLocationController::GetRandomListItem(BSSimpleList<MediaSet*>* apList) const {
    return ThisCall<MediaSet*>(0x595560, this, apList);
}
