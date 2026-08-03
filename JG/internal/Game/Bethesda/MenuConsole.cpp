#include "MenuConsole.hpp"

// GAME - 0x71B160
MenuConsole* MenuConsole::GetSingleton(bool abCreate) {
	return CdeclCall<MenuConsole*>(0x71B160, abCreate);
}

// GAME - 0x71D0A0
void MenuConsole::PrintLine(const char* apFormat, va_list args) {
	ThisCall(0x71D0A0, this, apFormat, args);
}

// GAME - 0x71D030
void MenuConsole::PrintLine(const char* apFormat, ...) {
	va_list args;
	va_start(args, apFormat);
	PrintLine(apFormat, args);
	va_end(args);
}

// GAME - 0x4A4020
bool MenuConsole::IsConsoleVisible() const {
	return cVisible > 0;
}

// GAME - 0x71D620
void MenuConsole::SetVisible(int8_t acState) {
	ThisCall(0x71D620, this, acState);
}

// GAME - 0x71D580
bool MenuConsole::ToggleVisible() {
	return ThisCall<bool>(0x71D580, this);
}