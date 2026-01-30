#pragma once

extern uint8_t s_preloadModRefIDs[0xFF];
extern uint8_t s_numPreloadMods;

void Core_PostLoadCallback(bool bLoadSucceeded);
uint8_t ResolveModIndexForPreload(uint8_t modIndexIn);
void Init_CoreSerialization_Callbacks();
