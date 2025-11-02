#include "Game/Bethesda/BSStringT.hpp"
#include "GameObjects.h"
#include "PluginAPI.h"
#include "SafeWrite.h"
#include "utility.h"
#include <fstream>

extern NVSECommandTableInterface* g_cmdTableInterface;
extern bool bFixJIP;

namespace JIPFixes {

	static HMODULE hJIP = 0;
	static UInt32 uiCrc32Table[256];
	static UInt32 uiJipHash = 0x9DF36B6;

	static size_t __fastcall GetJIPAddress(size_t aiAddress) {
		return reinterpret_cast<size_t>(hJIP) + aiAddress - 0x10000000;
	}

	static void initCRC32Table() {
		UInt32 polynomial = 0xEDB88320;
		for (UInt32 i = 0; i < 256; i++) {
			UInt32 crc = i;
			for (UInt32 j = 0; j < 8; j++) {
				if (crc & 1)
					crc = (crc >> 1) ^ polynomial;
				else
					crc >>= 1;
			}
			uiCrc32Table[i] = crc;
		}
	}


	static UInt32 crc32(const UInt8* data, size_t length) {
		UInt32 crc = 0xFFFFFFFF;
		for (size_t i = 0; i < length; i++) {
			UInt8 byte = data[i];
			crc = (crc >> 8) ^ uiCrc32Table[(crc ^ byte) & 0xFF];
		}
		return crc ^ 0xFFFFFFFF;
	}

	namespace ConsoleCmdFix {

		class ScriptCompileData {
		public:
			char*		pInput;
			uint32_t	uiInputOffset;
			uint32_t	eCompilerIndex;
			BSString	strCompilerName;
			// ... rest is not needed
		};

		bool __fastcall ScriptCompiler_Compile(void* apThis, void*, void* apScript, ScriptCompileData* apCompileData) {
			if (apCompileData->strCompilerName.pString && apCompileData->strCompilerName.pString[0] == 'C') {
				apCompileData->eCompilerIndex = strcmp(apCompileData->strCompilerName.pString, "Console") == 0;
			}

			return ThisCall<bool>(0x5AEB90, apThis, apScript, apCompileData);
		}

		void InitHooks() {
			SafeWrite32(GetJIPAddress(0x10059A86 + 1), uint32_t(ScriptCompiler_Compile));
		}

	}

	namespace PaletteCorruptionFix {

		static void __fastcall InvalidateObjPalette(NiAVObject* apObject) {
			if (!apObject) [[unlikely]]
				return;

			NiControllerManager* pControllerManager = ThisCall<NiControllerManager*>(0xA5C570, apObject, 0x11F36AC);
			if (pControllerManager && pControllerManager->defObjPlt)
				ThisCall(0xA6E960, pControllerManager->defObjPlt);
		}

		CallDetour kMemPoolFree;
		void __fastcall MemoryPool_Free(void* pBlock, unsigned int size) {
			char* pData = static_cast<char*>(pBlock);
			TESForm* pForm = *(TESForm**)pData;
			NiAVObject* pRoot = nullptr;
			if (pForm && pForm->GetIsReference())
				pRoot = static_cast<TESObjectREFR*>(pForm)->GetRefNiNode();

			if (pRoot) {
				NiControllerManager* pControllerManager = ThisCall<NiControllerManager*>(0xA5C570, pRoot, 0x11F36AC);
				if (pControllerManager && pControllerManager->defObjPlt)
					ThisCall(0xA6E960, pControllerManager->defObjPlt);
			}

			FastCall(kMemPoolFree.GetOverwrittenAddr(), pBlock, size);
		}

		void InitHooks() {
			kMemPoolFree.ReplaceCall(GetJIPAddress(0x1002BF45), MemoryPool_Free);
		}
	}

	namespace NotifyDurationFix {
		// This was painful
		uint32_t uiDefaultTimes[] = {
			0x4825C5,
			0x482619,
			0x4C5623,
			0x4CB8FC,
			0x4CEBDE,
			0x4CEC34,
			0x4CF14E,
			0x4CF1A7,
			0x4CF57B,
			0x4CF5D4,
			0x4CF7FB,
			0x4CF854,
			0x4CFB15,
			0x4CFB6E,
			0x4FEEE8,
			0x5013FD,
			0x501492,
			0x5016E8,
			0x508C7F,
			0x508D1F,
			0x509693,
			0x5096EB,
			0x50973C,
			0x509789,
			0x5097C7,
			0x509809,
			0x5150C6,
			0x5151CD,
			0x516F92,
			0x517063,
			0x51814E,
			0x518367,
			0x51853B,
			0x5185FF,
			0x5732E2,
			0x573449,
			0x5B5236,
			0x5B5285,
			0x5C1E86,
			0x5C86FD,
			0x5CDD75,
			0x5D0266,
			0x5D0473,
			0x5F5D34,
			0x5F5EE2,
			0x5F62DE,
			0x5F648C,
			0x5FA5D1,
			0x5FA687,
			0x5FA911,
			0x607BAD,
			0x607C63,
			0x60822D,
			0x608D3A,
			0x615845,
			0x61593C,
			0x615B09,
			0x615BF4,
			0x615DF6,
			0x615EFB,
			0x6160FA,
			0x6161F3,
			0x678442,
			0x702009,
			0x70E558,
			0x70E59C,
			0x7289B8,
			0x73380F,
			0x7338CB,
			0x73398D,
			0x733A48,
			0x7351AD,
			0x7352C7,
			0x737D32,
			0x7410FD,
			0x75739C,
			0x758295,
			0x75DE47,
			0x75E1A6,
			0x780506,
			0x780567,
			0x780849,
			0x7809B3,
			0x780A01,
			0x780A3D,
			0x780A8D,
			0x780AD5,
			0x780E83,
			0x780ED4,
			0x781C7F,
			0x781CEC,
			0x78DBEB,
			0x78EEB3,
			0x790160,
			0x790487,
			0x7981F4,
			0x7BBFEF,
			0x7BC0AB,
			0x7BC16A,
			0x7BC225,
			0x7BD714,
			0x7BD82E,
			0x7BEC27,
			0x7C0AFC,
			0x7C0C7B,
			0x7C0D37,
			0x7C0DF9,
			0x7C0EB4,
			0x7C18C2,
			0x7C2EDE,
			0x7C2FF8,
			0x7C3FC5,
			0x8159F6,
			0x823F58,
			0x825165,
			0x82BFC7,
			0x833E7B,
			0x834151,
			0x85045C,
			0x85057D,
			0x8505E2,
			0x8509AA,
			0x8509FA,
			0x856D21,
			0x878E46,
			0x88C914,
			0x88C969,
			0x88CB00,
			0x88CBE6,
			0x88CDB8,
			0x88CF98,
			0x88D1EC,
			0x88D840,
			0x891680, // The only ones with 4s duration instead of 2s
			0x8916C7, // The only ones with 4s duration instead of 2s
			0x891A9A, // The only ones with 4s duration instead of 2s
			0x8929F2,
			0x89AD83,
			0x89E0A9,
			0x8BA3AF,
			0x8C1E19,
			0x8C35CE,
			0x8C54E3,
			0x8C5523,
			0x8C557F,
			0x8C55BF,
			0x8C5771,
			0x8C57B1,
			0x8C580D,
			0x8C584D,
			0x8C59F1,
			0x8C5A31,
			0x8C5A8D,
			0x8C5ACD,
			0x8C5C71,
			0x8C5CB1,
			0x8C5D0D,
			0x8C5D4D,
			0x93D6C3,
			0x93D742,
			0x93D862,
			0x93D8CC,
			0x93D966,
			0x93D9F4,
			0x93DA50,
			0x93DB04,
			0x9423C6,
			0x942402,
			0x942462,
			0x9424AF,
			0x94250A,
			0x942562,
			0x9425A0,
			0x94260A,
			0x94264C,
			0x94DC08,
			0x94DD34,
			0x94FDEB,
			0x94FE1B,
			0x94FEEC,
			0x94FF1C,
			0x9627C2,
			0x966B38,
			0x969FC3,
			0x969FFF,
			0x96A05F,
			0x96A0AC,
			0x96A107,
			0x96A15F,
			0x96A19D,
			0x96A1FE,
			0x96A240,
		};

		void InitHooks() {
			const uint32_t uiJIPMessageDurationAddr = GetJIPAddress(0x1006A1B4);
			for (uint32_t uiAddress : uiDefaultTimes)
				SafeWrite32(uiAddress + 2, uiJIPMessageDurationAddr);

			SafeWriteBuf(0x70535C, "\x51\xD9\x45\x18\xD9\x1C\x24", 7);
		}
	}

	namespace CloseActiveMenuFix {
		void InitHooks() {
			SafeWrite8(GetJIPAddress(0x1003B87B + 1), 0x7A);
		}
	}

	namespace FireWeaponFix {
		thread_local bool bScriptedCall = false;
		uint32_t uiDoFireWeaponAddr = 0;

		void __fastcall DoFireWeaponExWrapper(Actor* apActor, void*, TESObjectWEAP* apWeapon) {
			bScriptedCall = true;
			FastCall(uiDoFireWeaponAddr, apActor, nullptr, apWeapon);
			bScriptedCall = false;
		}

		class ActorEx : public Actor {
		public:
			CombatController* GetCombatControllerEx() {
				CombatController* pController = GetCombatController();
				if (bScriptedCall && pController && !pController->combatProcedure1)
					return nullptr;

				return pController;
			}
		};


		void InitHooks() {
			uiDoFireWeaponAddr = GetJIPAddress(0x1001B6F0);
			SafeWrite32(GetJIPAddress(0x1001B827) + 4, uint32_t(DoFireWeaponExWrapper));

			PatchMemoryNop(0x523B3F, 8);
			WriteRelCallEx(0x523B3F, &ActorEx::GetCombatControllerEx);
		}
	}

	void ShowErrorMessage(const char* fmt, ...) {
		char cBuffer[512];
		const char* pPrefix = "JIP LN Fixes error:\n";
		const char* pSuffix = "\n\nJIP LN Fixes will be disabled.\nTo disable this message, set bJIPFixes to 0 in JohnnyGuitar.ini or use the latest supported JIP LN 57.30";
		strcpy_s(cBuffer, pPrefix);
		const uint32_t uiPrefixLen = strlen(pPrefix);
		va_list args;
		va_start(args, fmt);
		vsprintf_s(cBuffer + uiPrefixLen, sizeof(cBuffer) - uiPrefixLen, fmt, args);
		va_end(args);
		strcat_s(cBuffer, pSuffix);
		MessageBox(NULL, cBuffer, "JohnnyGuitarNVSE", MB_OK | MB_ICONERROR);
		hJIP = nullptr;
	}

	void InitHooks() {
		hJIP = GetModuleHandle("jip_nvse.dll");
		if (!hJIP) {
			PrintLog("Failed to find JIP LN!");
			return;
		}

		const PluginInfo* pInfo = g_cmdTableInterface->GetPluginInfoByName("JIP LN NVSE");
		if (!pInfo) {
			ShowErrorMessage("Failed to get JIP LN plugin info!");
			return;
		}

		if (pInfo->version != 5730) {
			double dVersion = pInfo->version / 100.0;
			ShowErrorMessage("Incompatible JIP LN version! Expected 57.30, got %.2f.", dVersion);
			return;
		}

		std::ifstream file("Data\\NVSE\\Plugins\\jip_nvse.dll", std::ios::binary);

		if (!file) {
			PrintLog("Failed to find JIP LN!");
			return;
		}
		
		std::vector<UInt8> buffer((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());

		if (buffer.size() != 502272) {
			ShowErrorMessage("Incompatible JIP LN version!");
			return;
		}

		initCRC32Table();
		UInt32 hash = crc32(buffer.data(), buffer.size());
		if (hash != uiJipHash)
		{
			ShowErrorMessage("Incompatible JIP LN version!");
			return;
		}

		ConsoleCmdFix::InitHooks();
		PaletteCorruptionFix::InitHooks();
		NotifyDurationFix::InitHooks();
		CloseActiveMenuFix::InitHooks();
		FireWeaponFix::InitHooks();
	}

	void InitDeferredHooks() {
		if (!hJIP)
			return;
	}
}