#include "Controls.hpp"

LPCDIDATAFORMAT Controls::GetMouseDataFormat() {
    return LPCDIDATAFORMAT(0x1100AAC);
}

LPCDIDATAFORMAT Controls::GetKeyboardDataFormat() {
    return LPCDIDATAFORMAT(0x1100CB4);
}

// GAME - 0x7FDF30
Controls* Controls::GetSingleton() {
    return *reinterpret_cast<Controls**>(0x11F35CC);
}

LPDIRECTINPUT8A Controls::GetDirectInput() {
    return GetSingleton()->pDirectInput;
}

LPDIRECTINPUTDEVICE8A Controls::GetKeyboard() {
    return GetSingleton()->pKeyboard;
}

LPDIRECTINPUTDEVICE8A Controls::GetMouse() {
    return GetSingleton()->pMouse;
}

// GAME - 0xA24560
uint32_t Controls::GetButtonState(uint32_t auiDevice, uint8_t aucButton, ButtonState aeState) const {
    return ThisCall<uint32_t>(0xA24560, this, auiDevice, aucButton, aeState);
}

// GAME - 0xA24660
int32_t Controls::GetUserAction(UserAction aeAction, ButtonState aeState) const {
    return ThisCall<int32_t>(0xA24660, this, aeAction, aeState);
}

// GAME - 0xA23390
int32_t Controls::GetJoystickAxis(uint32_t auiJoystick, JoystickAxis aeAxis) const {
    return ThisCall<int32_t>(0xA23390, this, auiJoystick, aeAxis);
}

// GAME - 0xA239E0
int32_t Controls::GetMouseAxis(MouseAxis aeAxis) const {
	return ThisCall<int32_t>(0xA239E0, this, aeAxis);
}
