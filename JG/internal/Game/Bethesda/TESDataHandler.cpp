#include "TESDataHandler.hpp"

TESDataHandler* TESDataHandler::GetSingleton() {
#ifdef GAME
    return *reinterpret_cast<TESDataHandler**>(0x11C3F2C);
#else
	return *reinterpret_cast<TESDataHandler**>(0xED3B0C);
#endif
}

// GAME - 0x45DFC0
BSSimpleList<TESFile*>* TESDataHandler::GetFileList() {
	return &kFiles;
}

// GAME - 0x740940
TESRegionDataManager* TESDataHandler::GetRegionDataManager() const {
	return pRegionDataManager;
}

// GAME - 0x4603B0
// GECK - 0x4DA6C0
bool TESDataHandler::AddFormToDataHandler(TESForm* apForm) {
#ifdef GAME
	return ThisCall<bool>(0x4603B0, this, apForm);
#else
	return ThisCall<bool>(0x4DA6C0, this, apForm);
#endif
}

// GAME - 0x4617E0
// GECK - 0x4CF090
BGSAddonNode* TESDataHandler::GetAddonNode(uint32_t auiIndex) const {
#ifdef GAME
	return ThisCall<BGSAddonNode*>(0x4617E0, this, auiIndex);
#else
	return ThisCall<BGSAddonNode*>(0x4CF090, this, auiIndex);
#endif
}

// GAME - 0x45A120
uint32_t TESDataHandler::GetAddonNodeCount() const {
#ifdef GAME
	return ThisCall<uint32_t>(0x45A120, this);
#else
#if USE_JG_CHANGES
	return kAddons.GetCount();
#else
	return kAddons.GetSize();
#endif
#endif
}

// GAME - 0x461820
// GECK - 0x4D8AA0
void TESDataHandler::AddAddonNode(BGSAddonNode* apNode) {
#ifdef GAME
	ThisCall(0x461820, this, apNode);
#else
	ThisCall(0x4D8AA0, this, apNode);
#endif
}

// GAME - 0x461930
// GECK - 0x4CF0B0
void TESDataHandler::RemoveAddonNode(BGSAddonNode* apNode) {
#ifdef GAME
	ThisCall(0x461930, this, apNode);
#else
	ThisCall(0x4CF0B0, this, apNode);
#endif
}
