#pragma once

#include "ExtraData/JGExtraData.hpp"
#ifdef GAME
#include "ExtraData/JGExtraEmittanceSource.hpp"
#endif

namespace JohnnyExtraData {

	SPEC_NOINLINE void __fastcall Init(NVSEDataInterface* apNVSEData);

}