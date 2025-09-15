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

	namespace CloseActiveMenuFix {
		void InitHooks() {
			SafeWrite8(GetJIPAddress(0x1003B87B + 1), 0x7A);
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
		CloseActiveMenuFix::InitHooks();
	}

	void InitDeferredHooks() {
		if (!hJIP)
			return;
	}
}