#pragma once

#define DIRECTINPUT_VERSION 0x800
#include <dinput.h>
#include <xinput.h>

class Controls {
private:
	LPCDIDATAFORMAT GetMouseDataFormat();
	LPCDIDATAFORMAT GetKeyboardDataFormat();

	static constexpr uint32_t JOYSTICK_COUNT = 8;

public:
	struct _DeviceType {
		enum Type {
			KEYBOARD = 0,
			MOUSE,
			JOYSTICK,
			CONTROLLER,
			COUNT
		};
	};
	using DeviceType = _DeviceType::Type;

	struct _DeviceState {
		enum State {
			CURRENT	 = 0,
			PREVIOUS = 1,
			COUNT
		};
	};
	using DeviceState = _DeviceState::State;

	struct _ButtonState {
		enum State {
			NONE		= -1,
			HELD		= 0,
			PRESSED		= 1,
			DEPRESSED	= 2,
			CHANGED		= 3,
		};
	};
	using ButtonState = _ButtonState::State;
	
	struct _KeyboardButton {
		enum Button {
			USE_DIK_MACROS = 0xFF, // DIK_ from dintput.h!
		};
	};
	using KeyboardButton = _KeyboardButton::Button;

	struct _MouseButton {
		enum Button {
			LEFT		= 0,
			RIGHT		= 1,
			MIDDLE		= 2,
			BUTTON_3	= 3,
			BUTTON_4	= 4,
			BUTTON_5	= 5,
			BUTTON_6	= 6,
			BUTTON_7	= 7,
			WHEEL_UP	= 8,
			WHEEL_DOWN	= 9,
			COUNT,
		};
	};
	using MouseButton = _MouseButton::Button;

	struct _MouseAxis {
		enum Axis {
			DELTA_X			= 0,
			DELTA_Y			= 1,
			DELTA_SCROLL	= 2,
		};
	};
	using MouseAxis = _MouseAxis::Axis;

	struct _JoystickAxis {
		enum Axis {
			NONE		= 0,

			// Joystick only
			MOV_X		= 1,
			MOV_Y		= 2,
			MOV_Z		= 3,
			ROT_X		= 4,
			ROT_Y		= 5,
			ROT_Z		= 6,

			// Controller only
			L_THUMB_X	= 7,
			L_THUMB_Y	= 8,
			R_THUMB_X	= 9,
			R_THUMB_Y	= 10,

			COUNT,
		};
	};
	using JoystickAxis = _JoystickAxis::Axis;

	struct _ControllerButton {
		enum Button {
			DPAD_UP			= 1,	// XINPUT_GAMEPAD_DPAD_UP
			DPAD_DOWN		= 2,	// XINPUT_GAMEPAD_DPAD_DOWN
			DPAD_RIGHT		= 4,	// XINPUT_GAMEPAD_DPAD_RIGHT
			DPAD_LEFT		= 5,	// XINPUT_GAMEPAD_DPAD_LEFT
			START			= 6,	// XINPUT_GAMEPAD_START
			BACK			= 7,	// XINPUT_GAMEPAD_BACK
			L_THUMB_BUTTON	= 8,	// XINPUT_GAMEPAD_LEFT_THUMB
			R_THUMB_BUTTON	= 9,	// XINPUT_GAMEPAD_RIGHT_THUMB
			BUTTON_A		= 10,	// XINPUT_GAMEPAD_A
			BUTTON_B		= 11,	// XINPUT_GAMEPAD_B
			BUTTON_X		= 12,	// XINPUT_GAMEPAD_X
			BUTTON_Y		= 13,	// XINPUT_GAMEPAD_Y
			R_BUTTON		= 14,	// XINPUT_GAMEPAD_RIGHT_SHOULDER
			L_BUTTON		= 15,	// XINPUT_GAMEPAD_LEFT_SHOULDER
			L_TRIGGER		= 16,	// bLeftTrigger
			R_TRIGGER		= 17,	// bRightTrigger
			L_THUMB_UP		= 19,	// sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
			L_THUMB_DOWN	= 20,	// sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
			L_THUMB_RIGHT	= 22,	// sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
			L_THUMB_LEFT	= 23,	// sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE

			// Right thumbstick is available only through joystick axis

			R_THUMB_UP		= 25,	// Use JoystickAxis
			R_THUMB_DOWN	= 26,	// Use JoystickAxis
			R_THUMB_RIGHT	= 28,	// Use JoystickAxis
			R_THUMB_LEFT	= 29,	// Use JoystickAxis

			COUNT,
		};
	};
	using ControllerButton = _ControllerButton::Button;

	struct _UserAction {
		enum Action {
			FORWARD			= 0,
			BACK			= 1,
			LEFT			= 2,
			RIGHT			= 3,
			USE				= 4,
			ACTIVATE		= 5,
			BLOCK			= 6,
			RELOAD_WEAPON	= 7,
			CROUCH			= 8,
			RUN				= 9,
			TOGGLE_RUN		= 10,
			AUTO_MOVE		= 11,
			JUMP			= 12,
			TOGGLE_POV		= 13,
			MENU_MODE		= 14,
			SLEEP_MENU		= 15,
			VATS_MENU		= 16,
			HOTKEY_1		= 17,
			AMMO_SWAP		= 18,
			HOTKEY_3		= 19,
			HOTKEY_4		= 20,
			HOTKEY_5		= 21,
			HOTKEY_6		= 22,
			HOTKEY_7		= 24,
			QUICK_SAVE		= 25,
			QUICK_LOAD		= 26,
			GRAB			= 27,
			
			BINDABLE_COUNT	= 28,

			CONSOLE			= 29,
			SCREENSHOT		= 30,

			COUNT,
		};
	};
	using UserAction = _UserAction::Action;

	struct _RumblePattern {
		enum Pattern {
			CONSTANT			= 0,
			PERIODIC_SQUARE		= 1,
			PERIODIC_TRIANGLE	= 2,
			PERIODIC_SAWTOOTH	= 3,
			PERIODIC_SINE		= 5,
			PERIODIC_TANGENT	= 6,
		};
	};
	using RumblePattern = _RumblePattern::Pattern;

	struct RumbleEffect {
		struct State {
			uint32_t uiDuration;
			uint16_t usStartSpeed;
			uint16_t usEndSpeed;
		};

		uint32_t		uiSpeed;
		RumblePattern	ePattern;
		uint32_t		uiDuration;
		uint32_t		uiWavelength;
		bool			bAlternate;
		State			kRampUp;
		State			kRampDown;
	};

	struct RumbleTimer {
		uint32_t uiRumbleDuration;
		uint32_t uiRampUpDuration;
		uint32_t uiRampDownDuration;
		uint32_t uiRumbleCounter;
		uint32_t uiRampCounter;
	};

	struct RumbleManager {
		uint32_t		uiControllerIndex;
		RumbleEffect*	pLeftEffect;
		RumbleEffect*	pRightEffect;
		RumbleTimer		kLeftTimer;
		RumbleTimer		kRightTimer;
		DWORD			dwNewTime;
		DWORD			dwOldTime;
		DWORD			dwStartTime;
	};

	struct ALIGN4 _Flags {
		enum Flags {
			HAS_JOYSTICKS		= 1u << 0,
			HAS_MOUSE			= 1u << 1,
			HAS_KEYBOARD		= 1u << 2,
			BACKGROUND_MOUSE	= 1u << 3,
		};

		bool bHasJoysticks		: 1;
		bool bHasMouse			: 1;
		bool bHasKeyboard		: 1;
		bool bBackgroundMouse	: 1;
	};
	using Flags = _Flags::Flags;

	bool					bIsControllerDisabled;
	Bitfield<_Flags>		uiFlags;
	LPDIRECTINPUT8A			pDirectInput;
	LPDIRECTINPUTDEVICE8A	pJoySticks[JOYSTICK_COUNT];
	LPDIRECTINPUTDEVICE8A	pKeyboard;
	LPDIRECTINPUTDEVICE8A	pMouse;
	DIJOYSTATE				kJoyStickState[JOYSTICK_COUNT][DeviceState::COUNT];
	DIDEVICEINSTANCEA		kJoyStickInstances[JOYSTICK_COUNT];
	DIDEVCAPS				kJoyStickCaps[JOYSTICK_COUNT];
	uint32_t				uiJoyStickFlags[JOYSTICK_COUNT][DeviceState::COUNT];
	uint32_t				uiJoyStickCount;
	uint8_t					ucKeyboardState[DeviceState::COUNT][256];
	DIDEVCAPS				kMouseCaps;
	DIMOUSESTATE2			kMouseState[DeviceState::COUNT];
	BOOL					bSwapLeftRightMouseButtons;
	uint8_t					ucMouseSensitivity;
	uint32_t				uiDoubleClickTime;
	bool					bDoubleClicked[JOYSTICK_COUNT];
	uint32_t				uiLastClickedTime[JOYSTICK_COUNT];
	RumbleManager*			pRumbleManager;
	RumbleEffect*			pRumbleEffects;
	bool					bIsControllerEnabled;
	UserAction				eActionToSet;
	bool					bSettingAControl;
	bool					bUpdated;
	Bitfield16				usOverrideFlags;
	uint8_t					ucKeyBinds[DeviceType::COUNT][UserAction::BINDABLE_COUNT];

	static Controls* GetSingleton();

	static LPDIRECTINPUT8A GetDirectInput();

	static LPDIRECTINPUTDEVICE8A GetKeyboard();

	static LPDIRECTINPUTDEVICE8A GetMouse();

	uint32_t GetButtonState(uint32_t auiDevice, uint8_t aucButton, ButtonState aeState) const;

	int32_t GetUserAction(UserAction aeAction, ButtonState aeState) const;

	int32_t GetJoystickAxis(uint32_t auiJoystick, JoystickAxis aeAxis) const;

	int32_t GetMouseAxis(MouseAxis aeAxis) const;
};

ASSERT_SIZE(Controls, 0x1C04);