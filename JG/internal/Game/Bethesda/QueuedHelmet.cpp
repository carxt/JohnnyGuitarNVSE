#include "QueuedHelmet.hpp"

// GAME - 0x43FAB0
bool QueuedHelmet::GetFinishedQueuing() const {
    return ucFlags.bFinishedQueuing;
}

// GAME - 0x43F1F0
void QueuedHelmet::SetFinishedQueuing(bool abVal) {
    ucFlags.bFinishedQueuing = abVal;
}
