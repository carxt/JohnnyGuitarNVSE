#pragma once

#include "Bethesda\QuestUpdateManager.hpp"

class TESSound;

namespace ExtraUISounds {

	void Install();

	void __fastcall SetQuestSound(TESSound* apSound, QuestUpdateManager::UpdateType aeType);

}