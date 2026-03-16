#pragma once

// keeping this in a separate file so we don't need to include dinput/dsound everywhere

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

	// Have not verified nothing has changed here so commenting out (no controllers to test with currently)
#if 0
	enum {
		kMaxDevices = 8,
	};

	OSInputGlobals();
	~OSInputGlobals();

	// 244
	class Joystick {
	public:
		Joystick();
		~Joystick();

		uint32_t	unk000[0x244 >> 2];
	};

	struct JoystickObjectsInfo {
		enum {
			kHasXAxis = 1 << 0,
			kHasYAxis = 1 << 1,
			kHasZAxis = 1 << 2,
			kHasXRotAxis = 1 << 3,
			kHasYRotAxis = 1 << 4,
			kHasZRotAxis = 1 << 5
		};

		uint32_t	axis;
		uint32_t	buttons;
	};

	// 2C
	struct Unk1AF4 {
		uint32_t	bufLen;
		uint8_t	unk04[0x2C - 4];
	};

	// 28
	struct Unk1B20 {
		uint32_t	unk00;
		uint32_t	unk04;
		uint32_t	unk08;
		uint32_t	unk0C;
		uint32_t	unk10;
		uint32_t	unk14;
		uint32_t	unk18;
		uint32_t	unk1C;
		uint32_t	unk20;
		uint32_t	unk24;
	};
#endif

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

#if 0
#include "GameTypes.h"

class TESGameSound;
class NiAVObject;

// 58
class TESGameSound {
public:
	TESGameSound();
	~TESGameSound();

	uint32_t			unk00[3];	// 00
	uint32_t			hashKey;	// 0C
	uint32_t			unk10[4];	// 10
	float			x;			// 20
	float			y;			// 24
	float			z;			// 28
	uint32_t			unk2C[4];	// 2C
	float			unk3C;		// 3C
	uint32_t			unk40[3];	// 40
	const char* name;		// 4C
	uint32_t			unk50;		// 50
	uint32_t			unk54;		// 54
};

// 328
class OSSoundGlobals {
public:
	OSSoundGlobals();
	~OSSoundGlobals();

	enum {
		kFlags_HasDSound = 1 << 0,
		kFlags_HasHardware3D = 1 << 2,
	};

	typedef NiTPointerMap <TESGameSound>	TESGameSoundMap;
	typedef NiTPointerMap <NiAVObject>		NiAVObjectMap;

	uint32_t					unk000;						// 000
	uint32_t					unk004;						// 004
	IDirectSound8* dsoundInterface;			// 008
	IDirectSoundBuffer8* primaryBufferInterface;	// 00C
	DSCAPS					soundCaps;					// 010
	uint32_t					unk070;						// 070
	uint32_t					unk074;						// 074
	IDirectSound3DListener* listenerInterface;		// 078
	uint32_t					unk07C[(0x0A4 - 0x07C) >> 2];	// 07C
	uint8_t					unk0A4;						// 0A4
	uint8_t					unk0A5;						// 0A5
	uint8_t					unk0A6;						// 0A6
	uint8_t					pad0A7;						// 0A7
	uint32_t					unk0A8;						// 0A8
	uint32_t					flags;						// 0AC - flags?
	uint32_t					unk0B0;						// 0B0
	float					unk0B4;						// 0B4
	float					masterVolume;				// 0B8
	float					footVolume;					// 0BC
	float					voiceVolume;				// 0C0
	float					effectsVolume;				// 0C4
	uint32_t					unk0C8;						// 0C8 - time
	uint32_t					unk0CC;						// 0CC - time
	uint32_t					unk0D0;						// 0D0 - time
	uint32_t					unk0D4[(0x0DC - 0x0D4) >> 2];	// 0D4
	uint32_t					unk0DC;						// 0DC
	uint32_t					unk0E0[(0x2F0 - 0x0E0) >> 2];	// 0E0
	float					musicVolume;				// 2F0
	uint32_t					unk2F4;						// 2F4
	float					musicVolume2;				// 2F8
	uint32_t					unk2FC;						// 2FC
	TESGameSoundMap* gameSoundMap;				// 300
	NiAVObjectMap* niObjectMap;				// 304
	NiTPointerList <void>* soundMessageMap;			// 308 - AudioManager::SoundMessage *
	uint32_t					unk30C[(0x320 - 0x30C) >> 2];	// 30C
	void* soundMessageList;			// 320
	uint32_t					unk324;						// 324
};

static_assert(sizeof(OSSoundGlobals) == 0x328);
#endif

class OSSoundGlobals {};

// A4
class TESMain {
public:
	TESMain();
	~TESMain();

	bool					bResumeLoadingThread;
	bool					bQuitGame;
	bool					bResetGame;
	bool					bGameActive;
	bool					bOnIdle;
	bool					bReloadContent;
	bool					bIsFlyCam;
	bool					bFreezeTime;
	HWND			window;				// 08
	HINSTANCE		procInstance;		// 0C
	uint32_t			mainThreadID;		// 10
	HANDLE			mainThreadHandle;	// 14
	uint32_t* unk18;				// 18	ScrapHeapManager::Buffer*
	uint32_t			unk1C;				// 1C
	OSInputGlobals* input;				// 20
	OSSoundGlobals* sound;				// 24
	uint32_t			unk28;				// 28	relates to unk18
	//...
	uint32_t* unk50;				// 50	same object as unk18
	//..
	uint32_t			unk60;				// 60	relates to unk50

	static TESMain* GetSingleton() {
		return *reinterpret_cast<TESMain**>(0x11DEA0C);
	}
};

//static_assert(sizeof(TESMain) == 0x0A4);	// found in oldWinMain 0x0086AF4B

extern TESMain** g_osGlobals;
