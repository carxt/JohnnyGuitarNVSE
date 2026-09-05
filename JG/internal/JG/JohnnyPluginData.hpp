#pragma once

namespace JohnnyPluginData {

	constexpr const char* JG_ABBREVIATION = "JG";

	constexpr const char* JG_FULL_NAME = "Johnny Guitar NVSE";

	constexpr const char* JG_PLUGIN_NAME = "JohnnyGuitarNVSE";

#ifdef GAME
	constexpr const char* JG_LOG_PATH = "logs\\JohnnyGuitarNVSE.log";
#else
	constexpr const char* JG_LOG_PATH = "logs\\JohnnyGuitarNVSE_GECK.log";
#endif

	constexpr uint32_t JG_VERSION = 529;

	constexpr double JG_VERSION_DECIMAL = JG_VERSION / 100.0;

	constexpr uint32_t JG_OPCODE_BASE = 0x3100;

}
