#pragma once

// keeping this in a separate file so we don't need to include dinput/dsound everywhere

#define DIRECTINPUT_VERSION 0x0800
#define DIRECTSOUND_VERSION 0x0800
#include <dinput.h>
//#include <dsound.h>

enum
{
	kMaxControlBinds =	0x1C,
};

enum XboxControlCode
{
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

// 1C04
class OSInputGlobals
{
public:
	enum
	{
		kFlag_HasJoysticks =	1 << 0,
		kFlag_HasMouse =		1 << 1,
		kFlag_HasKeyboard =		1 << 2,
		kFlag_BackgroundMouse =	1 << 3,
	};

	// Have not verified nothing has changed here so commenting out (no controllers to test with currently)
#if 0
	enum
	{
		kMaxDevices = 8,
	};

	OSInputGlobals();
	~OSInputGlobals();

	// 244
	class Joystick
	{
	public:
		Joystick();
		~Joystick();

		UInt32	unk000[0x244 >> 2];
	};

	struct JoystickObjectsInfo
	{
		enum
		{
			kHasXAxis =		1 << 0,
			kHasYAxis =		1 << 1,
			kHasZAxis =		1 << 2,
			kHasXRotAxis =	1 << 3,
			kHasYRotAxis =	1 << 4,
			kHasZRotAxis =	1 << 5
		};

		UInt32	axis;
		UInt32	buttons;
	};

	// 2C
	struct Unk1AF4
	{
		UInt32	bufLen;
		UInt8	unk04[0x2C - 4];
	};

	// 28
	struct Unk1B20
	{
		UInt32	unk00;
		UInt32	unk04;
		UInt32	unk08;
		UInt32	unk0C;
		UInt32	unk10;
		UInt32	unk14;
		UInt32	unk18;
		UInt32	unk1C;
		UInt32	unk20;
		UInt32	unk24;
	};
#endif

	UInt32			unk0000;				// 0000
	UInt32			flags;					// 0004
	IDirectInput8	*directInput;			// 0008
	UInt32			unk000C;				// 000C
	UInt32			unk0010;				// 0010
	UInt32			unk0014;				// 0014
	UInt32			unk0018;				// 0018
	UInt32			unk001C;				// 001C
	UInt32			unk0020;				// 0020
	UInt32			unk0024;				// 0024
	UInt32			unk0028;				// 0028
	void			*unk002C;				// 002C
	void			*unk0030;				// 0030
	UInt32			unk0034[1584];			// 0034
	UInt32			unk18F4;				// 18F4
	UInt8			currKeyStates[256];		// 18F8
	UInt8			lastKeyStates[256];		// 19F8
	UInt32			unk1AF8[11];			// 1AF8
	int				unk1B24;				// 1B24
	int				unk1B28;				// 1B28
	int				mouseWheelScroll;		// 1B2C
	UInt8			currButtonStates[8];	// 1B30
	UInt32			unk1B38[3];				// 1B38
	UInt8			lastButtonStates[8];	// 1B44
	UInt32			ltrtButtonState;		// 1B4C
	UInt32			unk1B50[2];				// 1B50
	UInt8			buttonStates1B58[8];	// 1B58
	UInt32			unk1B60[8];				// 1B60
	UInt32			*controllerVibration;	// 1B80
	UInt32			unk1B84[4];				// 1B84
	UInt8			keyBinds[28];			// 1B94
	UInt8			mouseBinds[28];			// 1BB0
	UInt8			joystickBinds[28];		// 1BCC
	UInt8			controllerBinds[28];	// 1BE8
};
STATIC_ASSERT(sizeof(OSInputGlobals) == 0x1C04);

extern OSInputGlobals **g_OSInputGlobals;

#if 0
#include "GameTypes.h"

class TESGameSound;
class NiAVObject;

// 58
class TESGameSound
{
public:
	TESGameSound();
	~TESGameSound();

	UInt32			unk00[3];	// 00
	UInt32			hashKey;	// 0C
	UInt32			unk10[4];	// 10
	float			x;			// 20
	float			y;			// 24
	float			z;			// 28
	UInt32			unk2C[4];	// 2C
	float			unk3C;		// 3C
	UInt32			unk40[3];	// 40
	const char *	name;		// 4C
	UInt32			unk50;		// 50
	UInt32			unk54;		// 54
};

// 328
class OSSoundGlobals
{
public:
	OSSoundGlobals();
	~OSSoundGlobals();

	enum
	{
		kFlags_HasDSound =		1 << 0,
		kFlags_HasHardware3D =	1 << 2,
	};
	
	typedef NiTPointerMap <TESGameSound>	TESGameSoundMap;
	typedef NiTPointerMap <NiAVObject>		NiAVObjectMap;

	UInt32					unk000;						// 000
	UInt32					unk004;						// 004
	IDirectSound8			* dsoundInterface;			// 008
	IDirectSoundBuffer8		* primaryBufferInterface;	// 00C
	DSCAPS					soundCaps;					// 010
	UInt32					unk070;						// 070
	UInt32					unk074;						// 074
	IDirectSound3DListener	* listenerInterface;		// 078
	UInt32					unk07C[(0x0A4-0x07C) >> 2];	// 07C
	UInt8					unk0A4;						// 0A4
	UInt8					unk0A5;						// 0A5
	UInt8					unk0A6;						// 0A6
	UInt8					pad0A7;						// 0A7
	UInt32					unk0A8;						// 0A8
	UInt32					flags;						// 0AC - flags?
	UInt32					unk0B0;						// 0B0
	float					unk0B4;						// 0B4
	float					masterVolume;				// 0B8
	float					footVolume;					// 0BC
	float					voiceVolume;				// 0C0
	float					effectsVolume;				// 0C4
	UInt32					unk0C8;						// 0C8 - time
	UInt32					unk0CC;						// 0CC - time
	UInt32					unk0D0;						// 0D0 - time
	UInt32					unk0D4[(0x0DC-0x0D4) >> 2];	// 0D4
	UInt32					unk0DC;						// 0DC
	UInt32					unk0E0[(0x2F0-0x0E0) >> 2];	// 0E0
	float					musicVolume;				// 2F0
	UInt32					unk2F4;						// 2F4
	float					musicVolume2;				// 2F8
	UInt32					unk2FC;						// 2FC
	TESGameSoundMap			* gameSoundMap;				// 300
	NiAVObjectMap			* niObjectMap;				// 304
	NiTPointerList <void>	* soundMessageMap;			// 308 - AudioManager::SoundMessage *
	UInt32					unk30C[(0x320-0x30C) >> 2];	// 30C
	void					* soundMessageList;			// 320
	UInt32					unk324;						// 324
};

STATIC_ASSERT(sizeof(OSSoundGlobals) == 0x328);
#endif

class OSSoundGlobals {
};

// A4
class OSGlobals
{
public:
	OSGlobals();
	~OSGlobals();

	UInt8			oneMore;			// 00
	UInt8			quitGame;			// 01	The seven are initialized to 0, this one is set by QQQ
	UInt8			exitToMainMenu;		// 02
	UInt8			unk03;				// 03
	UInt8			unk04;				// 04
	UInt8			unk05;				// 05
	UInt8			unk06;				// 06	This looks promising as TFC status byte
	UInt8			disableAI;			// 07
	HWND			window;				// 08
	HINSTANCE		procInstance;		// 0C
	UInt32			mainThreadID;		// 10
	HANDLE			mainThreadHandle;	// 14
	UInt32			*unk18;				// 18	ScrapHeapManager::Buffer*
	UInt32			unk1C;				// 1C
	OSInputGlobals	*input;				// 20
	OSSoundGlobals	*sound;				// 24
	UInt32			unk28;				// 28	relates to unk18
	//...
	UInt32			*unk50;				// 50	same object as unk18
	//..
	UInt32			unk60;				// 60	relates to unk50
};

//STATIC_ASSERT(sizeof(OSGlobals) == 0x0A4);	// found in oldWinMain 0x0086AF4B

extern OSGlobals ** g_osGlobals;
