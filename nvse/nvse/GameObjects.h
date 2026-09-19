#pragma once

#include "GameForms.h"
#include "GameSound.h"
#ifdef GAME
#include "Bethesda/PlayerCharacter.hpp"
#include "Bethesda/Creature.hpp"
#else
#include "Bethesda/TESObjectREFR.hpp"
#endif

#ifdef GAME
void __fastcall UpdateReference3D(TESObjectREFR* apReference);
#endif