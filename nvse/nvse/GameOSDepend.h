#pragma once

// keeping this in a separate file so we don't need to include dinput/dsound everywhere

#include "Gamebryo/NiSmartPointer.hpp"
#include "Bethesda/TESMain.hpp"

#define DIRECTINPUT_VERSION 0x0800
#define DIRECTSOUND_VERSION 0x0800
#include <dinput.h>
//#include <dsound.h>

enum {
	kMaxControlBinds = 0x1C,
};

enum XboxControlCode {
	kXboxCtrl_DPAD_UP = 1,
	kXboxCtrl_DPAD_DOWN,
	kXboxCtrl_DPAD_RIGHT = 4,
	kXboxCtrl_DPAD_LEFT,
	kXboxCtrl_START,
	kXboxCtrl_BACK,
	kXboxCtrl_LS_BUTTON,
	kXboxCtrl_RS_BUTTON,
	kXboxCtrl_BUTTON_A,
	kXboxCtrl_BUTTON_B,
	kXboxCtrl_BUTTON_X,
	kXboxCtrl_BUTTON_Y,
	kXboxCtrl_RB,
	kXboxCtrl_LB,
	kXboxCtrl_LT,
	kXboxCtrl_RT,
	kXboxCtrl_LS_UP = 0x13,
	kXboxCtrl_LS_DOWN,
	kXboxCtrl_LS_RIGHT = 0x16,
	kXboxCtrl_LS_LEFT,
};
enum KeyState {
	isHeld = 0x0,
	isPressed = 0x1,
	isDepressed = 0x2,
	isChanged = 0x3,
};

enum ControlCode {
	Forward = 0x0,
	Backward = 0x1,
	Left = 0x2,
	Right = 0x3,
	Attack = 0x4,
	Activate = 0x5,
	Aim = 0x6,
	ReadyItem = 0x7,
	Crouch = 0x8,
	Run = 0x9,
	AlwaysRun = 0xA,
	AutoMove = 0xB,
	Jump = 0xC,
	TogglePOV = 0xD,
	MenuMode = 0xE,
	Rest = 0xF,
	VATS_ = 0x10,
	Hotkey1 = 0x11,
	AmmoSwap = 0x12,
	Hotkey3 = 0x13,
	Hotkey4 = 0x14,
	Hotkey5 = 0x15,
	Hotkey6 = 0x16,
	Hotkey7 = 0x17,
	Hotkey8 = 0x18,
	QuickSave = 0x19,
	QuickLoad = 0x1A,
	Grab = 0x1B,
	Escape_ = 0x1C,
	Console = 0x1D,
	Screenshot = 0x1E,
};
// 1C04
class OSInputGlobals {
public:
	enum {
		kFlag_HasJoysticks = 1 << 0,
		kFlag_HasMouse = 1 << 1,
		kFlag_HasKeyboard = 1 << 2,
		kFlag_BackgroundMouse = 1 << 3,
	};

	uint32_t			unk0000;				// 0000
	uint32_t			flags;					// 0004
	IDirectInput8* directInput;			// 0008
	uint32_t			unk000C;				// 000C
	uint32_t			unk0010;				// 0010
	uint32_t			unk0014;				// 0014
	uint32_t			unk0018;				// 0018
	uint32_t			unk001C;				// 001C
	uint32_t			unk0020;				// 0020
	uint32_t			unk0024;				// 0024
	uint32_t			unk0028;				// 0028
	void* unk002C;				// 002C
	void* unk0030;				// 0030
	uint32_t			unk0034[1584];			// 0034
	uint32_t			unk18F4;				// 18F4
	uint8_t			currKeyStates[256];		// 18F8
	uint8_t			lastKeyStates[256];		// 19F8
	uint32_t			unk1AF8[11];			// 1AF8
	int				unk1B24;				// 1B24
	int				unk1B28;				// 1B28
	int				mouseWheelScroll;		// 1B2C
	uint8_t			currButtonStates[8];	// 1B30
	uint32_t			unk1B38[3];				// 1B38
	uint8_t			lastButtonStates[8];	// 1B44
	uint32_t			ltrtButtonState;		// 1B4C
	uint32_t			unk1B50[2];				// 1B50
	uint8_t			buttonStates1B58[8];	// 1B58
	uint32_t			unk1B60[8];				// 1B60
	uint32_t* controllerVibration;	// 1B80
	uint32_t			unk1B84[4];				// 1B84
	uint8_t			keyBinds[28];			// 1B94
	uint8_t			mouseBinds[28];			// 1BB0
	uint8_t			joystickBinds[28];		// 1BCC
	uint8_t			controllerBinds[28];	// 1BE8
	bool GetControlState(ControlCode code, KeyState state) { return ((bool(__thiscall*)(OSInputGlobals*, ControlCode, KeyState))(0xA24660))(this, code, state); }
	void SetControlHeld(ControlCode code) { ((void(__thiscall*)(OSInputGlobals*, ControlCode))(0xA24280))(this, code); };
	bool GetMouseState(int buttonID, KeyState state) { return ((bool(__thiscall*)(OSInputGlobals*, int, KeyState))(0xA23A50))(this, buttonID, state); };

	bool GetKeyState(int key, KeyState state) { return 	((bool(__thiscall*)(OSInputGlobals*, int, KeyState))(0xA24180))(this, key, state); };
	static OSInputGlobals* GetSingleton() { return *(OSInputGlobals**)(0x11F35CC); }
};
static_assert(sizeof(OSInputGlobals) == 0x1C04);

extern OSInputGlobals** g_OSInputGlobals;