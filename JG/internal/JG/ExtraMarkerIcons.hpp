#pragma once
#include <unordered_map>
#include "GameObjects.h"

namespace ExtraMarkerIcons {
	extern std::unordered_map<uint32_t, std::string> customMapMarkerIcons;
	void SetMapMarkerIcon(TESObjectREFR* marker, char* iconPath);
	char* __fastcall GetMapMarker(TESObjectREFR* thisObj, uint16_t mapMarkerType);
	void Install();
};