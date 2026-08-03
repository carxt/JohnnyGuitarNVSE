#include "QueuedKF.hpp"

// GAME - 0x43E530
bool QueuedKF::GetAlreadyLoaded() const {
    return ucFlags.bAlreadyLoaded;
}

// GAME - 0x43E480
void QueuedKF::SetAlreadyLoaded(bool abVal) {
    ucFlags.bAlreadyLoaded = abVal;
}