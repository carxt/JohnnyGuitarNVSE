#pragma once
// Functions affecting gameplay
DEFINE_COMMAND_PLUGIN(ToggleLevelUpMenu, , 0, 1, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(TogglePipBoy, , 0, 1, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(ShowPerkMenu, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(Jump, , 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(StopVATSCam, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(SetCameraShake, , 0, 2, kParams_TwoFloats);
DEFINE_COMMAND_PLUGIN(ApplyWeaponPoison, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SendStealingAlarm, , 0, 2, kParamsJohnny_TwoForms);
DEFINE_COMMAND_PLUGIN(SetVelEx, , 1, 3, kParamsJohnnyThreeFloats);
DEFINE_COMMAND_PLUGIN(StopSoundAlt, , 0, 2, kParamsJohnny_TwoForms);
DEFINE_COMMAND_PLUGIN(DisableMuzzleFlashLights, , 0, 1, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(UnsetAV, , 1, 1, kParams_OneActorValue);
DEFINE_COMMAND_PLUGIN(UnforceAV, , 1, 1, kParams_OneActorValue);
DEFINE_COMMAND_PLUGIN(ToggleNthPipboyLight, , 0, 2, kParams_TwoInts);
DEFINE_COMMAND_PLUGIN(GetRunSpeed, , 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(DisableMenuArrowKeys, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(EnableMenuArrowKeys, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(HighlightBodyPartAlt, , 1, 1, kParamsJohnnyOneOptionalFloat);
DEFINE_COMMAND_PLUGIN(DeactivateAllHighlightsAlt, , 1, 1, kParamsJohnnyOneOptionalFloat);
DEFINE_COMMAND_PLUGIN(GetNearestCompassHostileDirection, , 0, 1, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetNearestCompassHostile, , 0, 1, kParams_OneOptionalInt);
DEFINE_COMMAND_ALT_PLUGIN(SetDisablePlayerControlsHUDVisibilityFlags, SetDPCHUDFlags, , 0, 1, kParams_OneOptionalInt);

void(__cdecl* HandleActorValueChange)(ActorValueOwner* avOwner, int avCode, float oldVal, float newVal, ActorValueOwner* avOwner2) =
(void(__cdecl*)(ActorValueOwner*, int, float, float, ActorValueOwner*))0x66EE50;
bool(*Cmd_HighLightBodyPart)(COMMAND_ARGS) = (bool (*)(COMMAND_ARGS)) 0x5BB570;
bool(*Cmd_DeactivateAllHighlights)(COMMAND_ARGS) = (bool (*)(COMMAND_ARGS)) 0x5BB6C0;
void(__cdecl* HUDMainMenu_UpdateVisibilityState)(signed int) = (void(__cdecl*)(signed int))(0x771700);
#define NUM_ARGS *((UInt8*)scriptData + *opcodeOffsetPtr)
void RestoreDisabledPlayerControlsHUDFlags()
{
	SafeWrite32(0x771A53, HUDMainMenu::kXpMeter | HUDMainMenu::kSubtitles | HUDMainMenu::kMessages | HUDMainMenu::kQuestReminder | HUDMainMenu::kRadiationMeter);
}

bool Cmd_SetDisablePlayerControlsHUDVisibilityFlags_Execute(COMMAND_ARGS)
{
	UInt32 flags;
	if (NUM_ARGS && ExtractArgs(EXTRACT_ARGS, &flags))
	{
		SafeWrite32(0x771A53, flags);
		HUDMainMenu_UpdateVisibilityState(HUDMainMenu::kHUDState_RECALCULATE);
	}
	else
	{
		RestoreDisabledPlayerControlsHUDFlags();
	}

	return true;
}
bool Cmd_GetNearestCompassHostile_Execute(COMMAND_ARGS)
{
	*result = -1;

	NiPoint3* playerPos = PlayerCharacter::GetSingleton()->GetPos();

	Setting* fSneakMaxDistance = (Setting*)0x11CD7D8;
	Setting* fSneakExteriorDistanceMult = (Setting*)0x11CDCBC;
	bool isInterior = PlayerCharacter::GetSingleton()->GetParentCell()->IsInterior();
	float interiorDistanceSquared = fSneakMaxDistance->data.f * fSneakMaxDistance->data.f;
	float exteriorDistanceSquared = (fSneakMaxDistance->data.f * fSneakExteriorDistanceMult->data.f) * (fSneakMaxDistance->data.f * fSneakExteriorDistanceMult->data.f);
	float maxDist = isInterior ? interiorDistanceSquared : exteriorDistanceSquared;
	Actor* closestHostile = nullptr;
	UInt32 skipInvisible = 0;
	ExtractArgs(EXTRACT_ARGS, &skipInvisible);
	auto iter = PlayerCharacter::GetSingleton()->compassTargets->Begin();
	for (; !iter.End(); ++iter)
	{
		PlayerCharacter::CompassTarget* target = iter.Get();
		if (target->isHostile)
		{
			if (skipInvisible > 0 && (target->target->avOwner.Fn_02(kAVCode_Invisibility) > 0 || target->target->avOwner.Fn_02(kAVCode_Chameleon) > 0)) {
				continue;
			}
			auto distToPlayer = target->target->GetPos()->CalculateDistSquared(playerPos);
			if (distToPlayer < maxDist)
			{
				maxDist = distToPlayer;
				closestHostile = target->target;
			}
		}
	}

	if (closestHostile)	*(UInt32*)result = closestHostile->refID;

	return true;
}
bool Cmd_GetNearestCompassHostileDirection_Execute(COMMAND_ARGS)
{
	*result = -1;

	NiPoint3* playerPos = PlayerCharacter::GetSingleton()->GetPos();
	
	Setting* fSneakMaxDistance = (Setting*)0x11CD7D8;
	Setting* fSneakExteriorDistanceMult = (Setting*)0x11CDCBC;
	bool isInterior = PlayerCharacter::GetSingleton()->GetParentCell()->IsInterior();
	float maxDist = isInterior ? powf(fSneakMaxDistance->data.f, 2) : powf((fSneakMaxDistance->data.f * fSneakExteriorDistanceMult->data.f), 2);
	Actor* closestHostile = nullptr;
	UInt32 skipInvisible = 0;
	ExtractArgs(EXTRACT_ARGS, &skipInvisible);
	auto iter = PlayerCharacter::GetSingleton()->compassTargets->Begin();
	for (; !iter.End(); ++iter)
	{
		PlayerCharacter::CompassTarget* target = iter.Get();
		if (target->isHostile)
		{
			if (skipInvisible > 0 && (target->target->avOwner.Fn_02(kAVCode_Invisibility) > 0 || target->target->avOwner.Fn_02(kAVCode_Chameleon) > 0)) {
				continue;
			}
			auto distToPlayer = target->target->GetPos()->CalculateDistSquared(playerPos);
			if (distToPlayer < maxDist)
			{
				maxDist = distToPlayer;
				closestHostile = target->target;
			}
		}
	}

	if (closestHostile)
	{
		auto playerRotation = PlayerCharacter::GetSingleton()->AdjustRot(0);
		double headingAngle = GetAngleBetweenPoints(closestHostile->GetPos(), playerPos, playerRotation);

		// shift the coordinates from -180:180 to 0:360 and offset them (360 / 8 quadrants / 2) degrees
		int angle = headingAngle + 180 + 22.5;

		// convert the angle to which quadrant the NPC is in
		angle /= 45;
		*result = (angle + 4) % 8; // make 0 in front, 1 front right, 2 right, 3 back right ...
	}

	return true;
}
bool Cmd_HighlightBodyPartAlt_Execute(COMMAND_ARGS)
{
	return Cmd_HighLightBodyPart(PASS_COMMAND_ARGS);
}

bool Cmd_DeactivateAllHighlightsAlt_Execute(COMMAND_ARGS)
{
	return Cmd_DeactivateAllHighlights(PASS_COMMAND_ARGS);
}

bool Cmd_DisableMenuArrowKeys_Execute(COMMAND_ARGS) {
	if (!bArrowKeysDisabled) {
		bArrowKeysDisabled = true;
	}
	return true;
}
bool Cmd_EnableMenuArrowKeys_Execute(COMMAND_ARGS) {
	if (bArrowKeysDisabled) {
		bArrowKeysDisabled = false;
	}
	return true;
}
bool Cmd_GetRunSpeed_Execute(COMMAND_ARGS) {
	*result = 0;
	Actor* actor = (Actor*)thisObj;
	*result = ThisStdCall_F(0x884EB0, actor);
	if (IsConsoleMode()) Console_Print("GetRunSpeed >> %.2f", *result);
	return true;
}
bool Cmd_ToggleNthPipboyLight_Execute(COMMAND_ARGS)
{
	UInt32 index, isVisible;
	if (ExtractArgs(EXTRACT_ARGS, &index, &isVisible) && index < 3)
	{
		FOPipboyManager* pipboyManager = InterfaceManager::GetSingleton()->pipboyManager;
		if (pipboyManager->byte028)
		{
			if (isVisible)
			{
				pipboyManager->pipboyLightGlow[index]->m_flags &= ~1;
			}
			else
			{
				pipboyManager->pipboyLightGlow[index]->m_flags |= 1;
			}
		}
	}
	return true;
}
bool Cmd_UnsetAV_Execute(COMMAND_ARGS)
{
	UInt32 avCode;
	if (thisObj->IsActor() && ExtractArgs(EXTRACT_ARGS, &avCode))
	{
		Actor* actor = (Actor*)thisObj;
		ActorValueOwner* avOwner = &actor->avOwner;
		float oldVal = avOwner->GetActorValue(avCode);

		tList<void>* actorPermSetAVList = &actor->list0E0;
		void* avEntry = ThisStdCall<void*>(0x937760, actorPermSetAVList, avCode);
		ThisStdCall(0x937400, actorPermSetAVList, avEntry);
		thisObj->MarkAsModified(0x400000);

		if (!actor->IsPlayerRef())
		{
			BaseProcess* base = actor->baseProcess;
			if (base)
			{
				base->Unk_EC(avCode);
			}
		}

		// call handle change with new value
		float newVal = avOwner->GetActorValue(avCode);
		HandleActorValueChange(avOwner, avCode, oldVal, newVal, NULL);
	}
	return true;
}

bool Cmd_UnforceAV_Execute(COMMAND_ARGS)
{
	UInt32 avCode;
	if (thisObj->IsActor() && ExtractArgs(EXTRACT_ARGS, &avCode))
	{
		Actor* actor = (Actor*)thisObj;
		ActorValueOwner* avOwner = &actor->avOwner;
		float oldVal = avOwner->GetActorValue(avCode);

		tList<void>* actorPermForceAVList = &actor->list0D0;
		void* avEntry = ThisStdCall<void*>(0x937760, actorPermForceAVList, avCode);
		ThisStdCall(0x937400, actorPermForceAVList, avEntry);
		thisObj->MarkAsModified(0x800000);

		if (!actor->IsPlayerRef())
		{
			BaseProcess* base = actor->baseProcess;
			if (base)
			{
				base->Unk_EC(avCode);
			}
		}

		// call handle change with new value
		float newVal = avOwner->GetActorValue(avCode);
		HandleActorValueChange(avOwner, avCode, oldVal, newVal, NULL);
	}
	return true;
}

bool Cmd_StopSoundAlt_Execute(COMMAND_ARGS) {
	BSAudioManager* g_audioManager = (BSAudioManager*)0x11F6EF0;
	TESSound* soundForm;
	TESObjectREFR* source;
	BSFadeNode* fadeNode;
	*result = 0;
	if (ExtractArgs(EXTRACT_ARGS, &soundForm, &source))
	{
		if (soundForm->soundFile.path.m_dataLen)
		{
			const char* soundPath = soundForm->soundFile.path.m_data;
			BSGameSound* gameSound;
			for (auto sndIter = g_audioManager->playingSounds.Begin(); !sndIter.End(); ++sndIter)
			{
				gameSound = sndIter.Get();
				if (gameSound && StrBeginsCI(gameSound->filePath + 0xB, soundPath)) {
					fadeNode = (BSFadeNode*)g_audioManager->soundPlayingObjects.Lookup(gameSound->mapKey);
					if (fadeNode && fadeNode->GetFadeNode() && fadeNode->linkedObj && fadeNode->linkedObj == source)
					{
						gameSound->stateFlags &= 0xFFFFFF0F;
						gameSound->stateFlags |= 0x10;
						*result = 1;
						break;
					}
				}
			}
		}
	}
	return true;
}

bool Cmd_SetVelEx_Execute(COMMAND_ARGS) {
	NiPoint3 Point;
	if (ExtractArgs(EXTRACT_ARGS, &(Point.x), &(Point.y), &(Point.z)))
		((void(__cdecl*)(NiNode*, NiPoint3*, int))(0x62B8D0))(thisObj->GetNiNode(), &Point, 1);
	return true;
}

bool Cmd_SendStealingAlarm_Execute(COMMAND_ARGS) {
	TESObjectREFR* stolenItem;
	TESObjectREFR* owner;
	if (ExtractArgs(EXTRACT_ARGS, &owner, &stolenItem)) {
		PlayerCharacter* g_thePlayer = PlayerCharacter::GetSingleton();
		ThisStdCall(0x8BFA40, g_thePlayer, owner, owner, stolenItem->baseForm, 1, 1, owner);
		Console_Print("done");
	}
	return true;
}
bool Cmd_ApplyWeaponPoison_Execute(COMMAND_ARGS) {
	AlchemyItem* poison;
	if (ExtractArgs(EXTRACT_ARGS, &poison) && IS_TYPE(poison, AlchemyItem) && poison->IsPoison()) {
		PlayerCharacter* g_thePlayer = PlayerCharacter::GetSingleton();
		ContChangesEntry* wpnInfo = g_thePlayer->baseProcess->GetWeaponInfo();
		if (wpnInfo && wpnInfo->extendData)
		{
			UInt32 weaponSkill = ((TESObjectWEAP*)wpnInfo->type)->weaponSkill;
			if (weaponSkill != kAVCode_Unarmed && weaponSkill != kAVCode_MeleeWeapons) return true;
			ExtraDataList* xDataList = wpnInfo->extendData->GetFirstItem();
			if (xDataList)
			{
				ExtraPoison* xPoison = GetExtraType((*xDataList), Poison);
				if (!xPoison)
					ThisStdCall(0x4BDD20, wpnInfo, poison); // ContChangesEntry::AddExtraPoison
			}
		}
	}
	return true;
}

bool Cmd_ShowPerkMenu_Execute(COMMAND_ARGS) {
	InterfaceManager* g_interfaceManager = *(InterfaceManager**)0x011D8A80;
	if (g_interfaceManager) {
		PatchMemoryNop(0x784F47, 6); // NOP-ing iLevelsPerPerk check
		SafeWrite8(0x7850D6, 0x01);
		PatchMemoryNop(0x785D25, 5);
		ThisStdCall(0x784C80, NULL);						// LevelUpMenu::Create
		SafeWriteBuf(0x784F47, "\x0F\x85\x2D\x01\x00\x00", 6); // Restoring iLevelsPerPerk check
		SafeWrite8(0x7850D6, 0x00);
		SafeWriteBuf(0x785D25, "\xE8\x06\xFB\xFF\xFF", 5);
		LevelUpMenu* g_levelUpMenu = *(LevelUpMenu**)0x11D9FDC;
		g_levelUpMenu->tileBackBtn->SetFloat(kTileValue_visible, 0);
	}
	return true;
}

bool Cmd_TogglePipBoy_Execute(COMMAND_ARGS) {
	int pipboyTab = 0;
	ExtractArgs(EXTRACT_ARGS, &pipboyTab);
	if (pipboyTab == 0 || pipboyTab == 1002 || pipboyTab == 1003 || pipboyTab == 1023) {
		InterfaceManager* g_interfaceManager = *(InterfaceManager**)0x011D8A80;
		if (g_interfaceManager) {
			if (!g_interfaceManager->pipBoyMode)
				ThisStdCall(0x70F4E0, g_interfaceManager, 0, pipboyTab);
			else if (g_interfaceManager->pipBoyMode == 3)
				ThisStdCall(0x70F690, g_interfaceManager, 0);
			ThisStdCall(0x70EE80, g_interfaceManager);
		}
	}
	return true;
}

bool Cmd_ToggleLevelUpMenu_Execute(COMMAND_ARGS)
{
	UInt32 ToExtract;
	if (ExtractArgs(EXTRACT_ARGS, &ToExtract)) isShowLevelUp = ToExtract;
	return true;
}

bool Cmd_Jump_Execute(COMMAND_ARGS) {
	if (!thisObj->IsActor()) return true;
	((MobileObject*)thisObj)->Unk_95();
	return true;
}

bool Cmd_StopVATSCam_Execute(COMMAND_ARGS)
{
	ThisStdCall(0x93E770, PlayerCharacter::GetSingleton(), 2, 0);
	return true;
}

bool Cmd_SetCameraShake_Execute(COMMAND_ARGS) {
	float shakeMult, time;
	if (ExtractArgs(EXTRACT_ARGS, &shakeMult, &time)) {
		*(float*)(0x11DFED4) = shakeMult;
		*(float*)(0x11DFED8) = time;
	}
	return true;
}

bool Cmd_DisableMuzzleFlashLights_Execute(COMMAND_ARGS) {
	UInt32 toExtract = -1;
	if (ExtractArgs(EXTRACT_ARGS, &toExtract) && toExtract <= 1) DoSkipMuzzleLights = toExtract;
	*(UInt32*)result = (DoSkipMuzzleLights == 1);
	if (IsConsoleMode()) Console_Print("DisableMuzzleFlashLights >> %u", *result);
	return true;
}