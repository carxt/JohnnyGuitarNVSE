#pragma once

#include "Interface.hpp"

// GAME - 0x703C00
void Interface::PrintLine(const char* apText, auto ...args) {
	CdeclCall(0x703C00, apText, std::forward<decltype(args)>(args)...);
}

// GAME - 0x703E80
bool Interface::CreateMessageMenu(const char* apText, const char* apIcon, const char* apTitle, MessageBoxCallback apCallback, int8_t acFirstButtonResult, int32_t aiWarningContext, float afAlpha, float afMenuWidth, auto ...args) {
	return CdeclCall<bool>(0x703E80, apText, apIcon, apTitle, apCallback, acFirstButtonResult, aiWarningContext, afAlpha, afMenuWidth, std::forward<decltype(args)>(args)...);
}

// GAME - 0x703F10
bool Interface::CreateMessageMenuSound(const char* apText, const char* apIcon, const char* apTitle, const char* apSound, MessageBoxCallback apCallback, int8_t acFirstButtonResult, int32_t aiWarningContext, float afAlpha, float afMenuWidth, auto ...args) {
	return CdeclCall<bool>(0x703E80, apText, apIcon, apTitle, apSound, apCallback, acFirstButtonResult, aiWarningContext, afAlpha, afMenuWidth, std::forward<decltype(args)>(args)...);
}