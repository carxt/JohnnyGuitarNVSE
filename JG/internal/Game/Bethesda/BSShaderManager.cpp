#include "BSShaderManager.hpp"
#include "Gamebryo/NiSmartPointer.hpp"

// GAME - 0x4A0E90
NiDX9Renderer* BSShaderManager::GetRenderer() {
	return *reinterpret_cast<NiPointer<NiDX9Renderer>*>(0x11F9508);
}

// GAME - 0x4A0EA0
BSTextureManager* BSShaderManager::GetTextureManager() {
#ifdef GAME
	return *reinterpret_cast<BSTextureManager**>(0x11F91A8);
#else
	return *reinterpret_cast<BSTextureManager**>(0xF23BF8);
#endif
}

// GAME - 0x4E3270
ImageSpaceManager* BSShaderManager::GetImageSpaceManager() {
#ifdef GAME
	return *reinterpret_cast<ImageSpaceManager**>(0x11F91AC);
#else
	return *reinterpret_cast<ImageSpaceManager**>(0xF23BFC);
#endif
}

// GAME - 0x450B80
ShadowSceneNode* BSShaderManager::GetShadowSceneNode(uint32_t aeType) {
    return reinterpret_cast<ShadowSceneNode**>(0x11F91C8)[aeType];
}

// GAME - 0x539F40
const NiFixedString& BSShaderManager::GetTexPercTag() {
	return *pTexPercTag;
}