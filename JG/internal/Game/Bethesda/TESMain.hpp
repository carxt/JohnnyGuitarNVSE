#pragma once

#include "BSPackedTaskQueue.hpp"
#include "ScrapHeap.hpp"
#include "Gamebryo/NiRefObject.hpp"

class BSShaderAccumulator;
class NiCamera;
class SceneGraph;

// Officially just "Main"	
class TESMain {
public:
	bool							bResumeLoadingThread;
	bool							bQuitGame;
	bool							bResetGame;
	bool							bGameActive;
	bool							bOnIdle;
	bool							bReloadContent;
	bool							bIsFlyCam;
	bool							bFreezeTime;
	HWND							hWnd;
	HINSTANCE						hInstance;
	uint32_t						uiMainThreadID;
	HANDLE							hMainThread;
	ScrapHeap						kPackedTaskHeap;
	BSPackedTaskQueue				kTaskQueue;
	ScrapHeap						kSecondaryPackedTaskHeap;
	BSPackedTaskQueue				kSecondaryTaskQueue;
	NiPointer<BSShaderAccumulator>	spDrawWorldAccum;
	NiPointer<BSShaderAccumulator>	spDraw1stPersonAccum;
	NiPointer<BSShaderAccumulator>	spDraw1stPersonDepthAccum;
	NiPointer<BSShaderAccumulator>	spScreenSplatterAccum;
	NiPointer<BSShaderAccumulator>	spRenderedMenuAccum;
	bool							bRenderingMenuBG;
	NiPointer<NiCamera>				spFirstPersonCamera;

	static TESMain* GetSingleton();
	static SceneGraph* GetWorldSceneGraph();
	static NiCamera* GetWorldRootCamera();
};

ASSERT_SIZE(TESMain, 0xA4);