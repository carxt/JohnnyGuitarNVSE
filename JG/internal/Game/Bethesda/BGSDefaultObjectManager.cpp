#include "BGSDefaultObjectManager.hpp"

// GAME - 0x58D680
// GAME - 0x5A9D90
BGSDefaultObjectManager* BGSDefaultObjectManager::GetSingleton() {
#ifdef GAME
	return CdeclCall<BGSDefaultObjectManager*>(0x58D680);
#else
	return CdeclCall<BGSDefaultObjectManager*>(0x5A9D90);
#endif
}

// GAME - 0x58DB10
// GECK - 0x5A9E10
TESForm* BGSDefaultObjectManager::GetItem(DefaultObjects aeObject) {
	BGSDefaultObjectManager* pMgr = GetSingleton();
	if (pMgr->GetInitialized())
		return pMgr->pForms[aeObject];

	return nullptr;
}
