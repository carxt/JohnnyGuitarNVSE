#include "JIPUtils.hpp"
#include "PluginAPI.h"

#include <array>

extern NVSECommandTableInterface* g_cmdTableInterface;

namespace JIPUtils {

	HMODULE hJIP = 0;

	constexpr uint32_t CRC32_TABLE_SIZE = 256;
	constexpr uint32_t JIP_TARGET_HASH = 0x9DF36B6;
	constexpr uint32_t JIP_TARGET_SIZE = 502272;

	static constexpr std::array<uint32_t, CRC32_TABLE_SIZE> initCRC32Table() {
		constexpr uint32_t polynomial = 0xEDB88320;
		std::array<uint32_t, CRC32_TABLE_SIZE> crc32table;
		for (uint32_t i = 0; i < CRC32_TABLE_SIZE; i++) {
			uint32_t crc = i;
			for (uint32_t j = 0; j < 8; j++) {
				if (crc & 1)
					crc = (crc >> 1) ^ polynomial;
				else
					crc >>= 1;
			}
			crc32table[i] = crc;
		}
		return crc32table;
	}


	static uint32_t crc32(const uint8_t* data, size_t length) {
		constexpr std::array<uint32_t, CRC32_TABLE_SIZE> crc32table = initCRC32Table();
		uint32_t crc = 0xFFFFFFFF;
		for (size_t i = 0; i < length; i++) {
			uint8_t byte = data[i];
			crc = (crc >> 8) ^ crc32table[(crc ^ byte) & 0xFF];
		}
		return crc ^ 0xFFFFFFFF;
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

	void Init() {
		HMODULE hJIPModule = GetModuleHandle("jip_nvse.dll");
		if (!hJIPModule) {
			_MESSAGE("Failed to find JIP LN!");
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

		HANDLE hJIPFile = CreateFile("Data\\NVSE\\Plugins\\jip_nvse.dll", GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr);

		if (!hJIPFile || hJIPFile == INVALID_HANDLE_VALUE) {
			_MESSAGE("Failed to find JIP LN!");
			return;
		}

		DWORD dwFileSize = GetFileSize(hJIPFile, nullptr);

		if (dwFileSize != JIP_TARGET_SIZE) {
			ShowErrorMessage("Incompatible JIP LN version!");
			return;
		}

		DWORD dwBytesRead = 0;
		HANDLE hMemoryMapping = CreateFileMapping(hJIPFile, nullptr, PAGE_READONLY, 0, 0, nullptr);
		if (!hMemoryMapping) {
			CloseHandle(hJIPFile);
			ShowErrorMessage("Failed to create JIP LN mapping!");
			return;
		}

		const uint8_t* pFileData = reinterpret_cast<const uint8_t*>(MapViewOfFile(hMemoryMapping, FILE_MAP_READ, 0, 0, 0));
		if (!pFileData) {
			CloseHandle(hMemoryMapping);
			CloseHandle(hJIPFile);
			ShowErrorMessage("Failed to read JIP LN!");
			return;
		}

		const uint32_t uiHash = crc32(pFileData, dwFileSize);

		UnmapViewOfFile(pFileData);
		CloseHandle(hMemoryMapping);
		CloseHandle(hJIPFile);

		if (uiHash != JIP_TARGET_HASH) {
			ShowErrorMessage("Incompatible JIP LN binary!");
			return;
		}

		hJIP = hJIPModule;
		_MESSAGE("JIP LN detected and verified.");
	}
}