#include "QueuedTexture.hpp"

// GAME - 0x43E530
bool QueuedTexture::GetAlreadyLoaded() const {
    return ucFlags.bAlreadyLoaded;
}

// GAME - 0x43E480
void QueuedTexture::SetAlreadyLoaded(bool abVal) {
    ucFlags.bAlreadyLoaded = abVal;
}

// GAME - 0x43C3D0
bool QueuedTexture::GetLoadDegraded() const {
    return ucFlags.bLoadDegraded;
}

// GAME - 0x43C0D0
void QueuedTexture::SetLoadDegraded(bool abVal) {
    ucFlags.bLoadDegraded = abVal;
}

// GAME - 0x43C630
bool QueuedTexture::GetInQueuedTextureMap() const {
    return ucFlags.bInQueuedTextureMap;
}

// GAME - 0x43C100
void QueuedTexture::SetInQueuedTextureMap(bool abVal) {
    ucFlags.bInQueuedTextureMap = abVal;
}
