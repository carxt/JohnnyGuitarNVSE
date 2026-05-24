#include "TESMain.hpp"
#include <netimmerse.h>

TESMain* TESMain::GetSingleton() {
	return *reinterpret_cast<TESMain**>(0x11DEA0C);
}

// GAME - 0x45C670
SceneGraph* TESMain::GetWorldSceneGraph() {
	return *reinterpret_cast<SceneGraph**>(0x11DEB7C);
}

// GAME - 0x524C90
NiCamera* TESMain::GetWorldRootCamera() {
	return GetWorldSceneGraph()->spCamera;
}
