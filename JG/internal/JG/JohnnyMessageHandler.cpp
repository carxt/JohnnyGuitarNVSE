#include "JohnnyMessageHandler.hpp"
#include "BarterFilter.hpp"
#include "CameraOverlay.hpp"
#include "CameraOverride.hpp"
#include "CommandOpcodes.h"
#include "CustomHUDShake.hpp"
#include "DisabledArrowKeys.hpp"
#include "DisabledLevelUp.hpp"
#include "DisabledMuzzleFlashLights.hpp"
#include "DisabledSaves.hpp"
#include "EditorIDRestoration.hpp"
#include "events/JohnnyEvents.hpp"
#include "ExtraMiscStats.hpp"
#include "JohnnyExtraData.hpp"
#include "JohnnyFixes.hpp"
#include "JohnnyPluginData.hpp"
#include "JohnnyPatches.hpp"
#include "JohnnyRadios.hpp"
#include "LandRemapping.hpp"
#include "MediaLocationControllerTweaks.hpp"
#include "NPCAccuracy.hpp"
#include "RSMBarberHook.hpp"
#include "TaskQueue.hpp"

#include "JIP/JIPFixes.hpp"

#include "functions/fn_gameplay.h"

#include <GameUI.h>

#include "Bethesda/AutoMemContext.hpp"

DWORD dwGameStartTimestamp = 0;
bool (*Cmd_Update3D)(COMMAND_ARGS) = 0;
extern NVSECommandTableInterface* g_cmdTableInterface;

// The reason we're doing functions per event is because we don't want a massive, cache destroying message handler function

static SPEC_NOINLINE void PostPostLoad(bool abGECK) {
	if (JohnnyPatches::bFixJIP) {
		JIPFixes::InitCommandHooks(abGECK);
		JIPFixes::InitHooks(abGECK);
	}

	if (abGECK)
		return;

	const CommandInfo* pUpdate3D = g_cmdTableInterface->GetByOpcode(CommandOpcodes::kUpdate3D);
	if (pUpdate3D)
		Cmd_Update3D = pUpdate3D->execute;
}

static SPEC_NOINLINE void DeferredInit() {
	if (JohnnyPatches::bFixJIP)
		JIPFixes::InitDeferredHooks(false);

	dwGameStartTimestamp = GetTickCount();
	JohnnyPatches::DeferredInit();
	CameraOverlay::Init();
	EDIDRestoration::PrintErrors();
	NiGlobalStringTable::RemoveUnusedStrings();

	Console_Print("JohnnyGuitar version: %.2f", JohnnyPluginData::JG_VERSION_DECIMAL);
}

static void MainGameLoop() {
	TaskQueue::ExecuteTasks();

	CameraOverlay::Update();
	CustomHUDShake::Update();
	JohnnyRadios::Update();
	JohnnyEvents::Update();
	ExtraMiscStats::Update();
	JohnnyPatches::Update();

	TaskQueue::ExecuteTasks();
}

static void __fastcall GameReset(uint32_t aeType) {
	JohnnyExtraDataArray::GetInstance().ResetScriptData();

	if (aeType == NVSEMessagingInterface::kMessage_NewGame)
		CameraOverlay::ReInit();
	else
		CameraOverlay::Reset();

	DisabledMuzzleFlashLights::Reset(); //reset the muzzle hook every time
	DisabledArrowKeys::Reset();
	DisabledLevelUp::Reset();

	ThisCall(0x8C17C0, PlayerCharacter::GetSingleton()); // reevaluate reload speed modifiers
	ThisCall(0x8C1940, PlayerCharacter::GetSingleton()); // reevaluate equip speed modifiers

	RestoreDisabledPlayerControlsHUDFlags();

	DisabledSaves::Reset();
	ExtraMiscStats::Reset();
	RSMBarberHook::Reset();
	JohnnyRadios::Reset();
	BarterFilter::Reset();
	NPCAccuracy::Reset();
	CustomHUDShake::Reset();
	MediaLocationControllerTweaks::ResetOverride();
	JohnnyFixes::ClearPlayerFurniture(); //fix furniture crash on reload
	CameraOverride::Reset();
	JohnnyEvents::Reset();
	LandRemapping::Reset();

	bNoHolotapeStopSound = false;
}

static void PostLoadGame() {
	NiGlobalStringTable::RemoveUnusedStrings();
	CameraOverlay::ReInit();
}

void JohnnyMessageHandler::Game(NVSEMessagingInterface::Message* apMessage) {
	const uint32_t eMessageType = apMessage->type;

	// Not needed at the moment, and gets called more often than the rest - thus, skip early
	if (eMessageType >= NVSEMessagingInterface::kMessage_OnFramePresent && eMessageType <= NVSEMessagingInterface::kMessage_OnNonPersistentFormUnload) [[likely]]
		return;

	MEMORY_CONTEXT(MC_DEFAULT);

	// Obviously a hot path, so we handle it here
	if (eMessageType == NVSEMessagingInterface::kMessage_MainGameLoop) [[likely]] {
		MainGameLoop();
	}
	else {
		switch (eMessageType) {
			[[unlikely]] case NVSEMessagingInterface::kMessage_PostPostLoad:
				PostPostLoad(false);
				break;
			[[unlikely]] case NVSEMessagingInterface::kMessage_DeferredInit:
				DeferredInit();
				break;
			[[unlikely]] case NVSEMessagingInterface::kMessage_NewGame:
			[[unlikely]] case NVSEMessagingInterface::kMessage_PreLoadGame:
				GameReset(eMessageType);
				break;
			[[unlikely]] case NVSEMessagingInterface::kMessage_PostLoadGame:
				PostLoadGame();
				break;
			default:
				break;
		}
	}
}

void JohnnyMessageHandler::GECK(NVSEMessagingInterface::Message* apMessage) {
	const uint32_t eMessageType = apMessage->type;

	if (eMessageType == NVSEMessagingInterface::kMessage_PostPostLoad) {
		PostPostLoad(true);
	}
}
