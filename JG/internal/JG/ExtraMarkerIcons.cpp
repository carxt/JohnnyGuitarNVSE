#include "ExtraMarkerIcons.hpp"

namespace ExtraMarkerIcons {
	std::unordered_map<uint32_t, char*> markerIconMap;
	char** defaultMarkerList = (char**)0x11A0404;

	void SetMapMarkerIcon(TESObjectREFR* marker, char* iconPath) {
		auto pos = markerIconMap.find(marker->GetFormID());
		uint32_t bufferSize = strlen(iconPath) + 1;
		char* pathCopy = BSMemory::malloc<char>(bufferSize);
		strcpy_s(pathCopy, bufferSize, iconPath);

		if (pos != markerIconMap.end()) {
			delete[] pos->second;
			pos->second = pathCopy;
		}
		else {
			markerIconMap.insert({ marker->GetFormID(), pathCopy });
		}
	}


	char* __fastcall GetMapMarker(TESObjectREFR* thisObj, uint16_t mapMarkerType) {
		auto it = markerIconMap.find(thisObj->GetFormID());
		if (it != markerIconMap.end()) return it->second;
		return defaultMarkerList[mapMarkerType];
	}

	__declspec (naked) void GetMapMarkerHook() {
		//uint32_t static const retAddr = 0x079D337;
		__asm
		{
			mov edx, eax
			mov ecx, [ebp - 0x24]
			jmp GetMapMarker
		}
	}
	void Install() {
		// SetCustomMapMarkerIcon
		HookUtils::SafeWrite16(0x79D330, 0x9090);
		HookUtils::WriteRelCall(0x79D332, (uint32_t)GetMapMarkerHook);
	}
}