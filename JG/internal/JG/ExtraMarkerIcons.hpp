#pragma once

class TESObjectREFR;

namespace ExtraMarkerIcons {
	void SetMapMarkerIcon(TESObjectREFR* marker, char* iconPath);
	char* __fastcall GetMapMarker(TESObjectREFR* thisObj, uint16_t mapMarkerType);
	void Install();
};