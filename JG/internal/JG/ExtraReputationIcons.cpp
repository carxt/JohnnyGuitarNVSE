#include "ExtraReputationIcons.hpp"
#include <GameForms.h>
#include <Bethesda/Setting.hpp>
#include <GameAPI.h>

namespace ExtraReputationIcons {
	std::unordered_map <uint32_t, std::vector<const char*>> factionRepIcons;

	const char* __fastcall GetReputationIconHook(TESReputation* rep) {
		auto it = factionRepIcons.find(rep->GetFormID());
		if (it != factionRepIcons.end()) {
			uint8_t tierID = 0;
			uint8_t pos = ThisCall<uint8_t>(0x616950, rep, 1);
			uint8_t neg = ThisCall<uint8_t>(0x616950, rep, 0);
			if ((pos == 0 && neg == 1) || (pos == 2 && (neg == 2 || neg == 3)) || (pos == 3 && neg == 3)) {
				tierID = 0; // in pain
			}
			else if (((neg == 2 || neg == 3) && (pos == 0 || pos == 1)) || (pos == 3 && neg == 2)) {
				tierID = 1; // sad
			}
			else if (((pos == 0 || pos == 1) && neg == 0) || (pos == 1 && neg == 1)) {
				tierID = 2; // neutral
			}
			else {
				tierID = 3; // very happy
			}
			if (*it->second[tierID]) return it->second[tierID];
		}
		return ThisCall<char*>(0x6167D0, rep);
	}

	const char* __fastcall GetReputationMessageIconHook(uint32_t a1) {
		uint32_t addr = (uint32_t)_ReturnAddress();
		auto* _ebp = GetParentBasePtr(_AddressOfReturnAddress(), false);
		TESReputation* rep = nullptr;
		switch (addr) {
		case 0x615951:
		case 0x61585A:
		case 0x615B1E:
		case 0x615C09:
			rep = *reinterpret_cast<TESReputation**>(_ebp - 0x110);
			break;
		case 0x615E0B:
		case 0x615F10:
		case 0x61610F:
		case 0x616208:
			rep = *reinterpret_cast<TESReputation**>(_ebp - 0x128);
			break;
		default:
			break;
		}
		if (rep && rep->GetFormID()) {
			auto it = factionRepIcons.find(rep->GetFormID());
			if (it != factionRepIcons.end()) {
				uint8_t tierID = 0;
				if (a1 == 0x11CBAD0 || a1 == 0x11CBC34) {
					tierID = 1;
				}
				else if (a1 == 0x11CBA00 || a1 == 0x11CBD5C) {
					tierID = 3;
				}
				if (*it->second[tierID]) return it->second[tierID];
			}
		}
		return a1 ? ((Setting*)a1)->String() : "\0";
	}

	void Install() {
		// SetCustomReputationChangeIcon
		HookUtils::WriteRelCall(0x6156A2, uint32_t(GetReputationIconHook));
		HookUtils::WriteRelCall(0x6156FB, uint32_t(GetReputationIconHook));
		HookUtils::WriteRelCall(0x615B19, uint32_t(GetReputationMessageIconHook));
		HookUtils::WriteRelCall(0x615C04, uint32_t(GetReputationMessageIconHook));
		HookUtils::WriteRelCall(0x61610A, uint32_t(GetReputationMessageIconHook));
		HookUtils::WriteRelCall(0x616203, uint32_t(GetReputationMessageIconHook));
		HookUtils::WriteRelCall(0x615855, uint32_t(GetReputationMessageIconHook));
		HookUtils::WriteRelCall(0x61594C, uint32_t(GetReputationMessageIconHook));
		HookUtils::WriteRelCall(0x615F0B, uint32_t(GetReputationMessageIconHook));
		HookUtils::WriteRelCall(0x615E06, uint32_t(GetReputationMessageIconHook));
	}

	void Set(uint32_t formID, uint32_t tierID, const char* path) {
		auto pos = factionRepIcons.find(formID);
		uint32_t bufferSize = strlen(path) + 1;
		char* pathCopy = new char[bufferSize];
		strcpy_s(pathCopy, bufferSize, path);

		if (pos != factionRepIcons.end()) {
			if (*pos->second[tierID - 1]) delete[] pos->second[tierID - 1];
			pos->second[tierID - 1] = pathCopy;
		}
		else {
			std::vector<const char*> v{ "", "", "", "" };
			v[tierID - 1] = pathCopy;
			factionRepIcons.insert(std::pair<uint32_t, std::vector<const char*>>(formID, v));
		}
	}

	void Dump() {
		auto it = factionRepIcons.begin();
		for (auto const& it : factionRepIcons) {
			Console_Print("0x%X - %s %s %s %s", it.first, it.second[0], it.second[1], it.second[2], it.second[3]);
		}
	}
}