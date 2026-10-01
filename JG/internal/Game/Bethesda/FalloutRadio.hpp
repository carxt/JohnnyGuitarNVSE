#pragma once

#include "BSSimpleList.hpp"
#include "BSSoundHandle.hpp"

class Conversation;
class TESObjectREFR;
class TESSound;

class FalloutRadio {
public:
	struct FORadioReceiver {
		TESObjectREFR*	pRadio;
		BSSoundHandle	kSound;
		BSSoundHandle	kStaticSound;
		bool			bShouldBePlaying;
		bool			bJustStarted;
		bool			bInRange;
		bool			bIsActor;
	};

	struct StationState {
		Conversation*					pConvo;
		Conversation*					pNextConvo;
		uint32_t						uiCurrentItemStartTime;
		int32_t							iCurrentItemDuration;
		uint8_t							ucStationPower;
		uint8_t							ucTargetPower;
		Bitfield32						uiStationFlags;
		BSSimpleList<FORadioReceiver*>	kStationUsers;
	};

	struct FORadioStation {
		TESObjectREFR*	pStation;
		StationState	kCurrentState;
	};

	static constexpr AddressPtr<bool, 0x11DD434> bPipboyRadioEnabled;
	static constexpr AddressPtr<bool, 0x11DD435> bWasInInterior;
	static constexpr AddressPtr<bool, 0x11DD436> bShutdown;
	static constexpr AddressPtr<bool, 0x11DD437> bIsDialogueOnlyRadio;
	static constexpr AddressPtr<uint32_t, 0x11DD438> uiQueuedState;
	static constexpr AddressPtr<uint32_t, 0x11DD43C> uiRadioState;
	static constexpr AddressPtr<TESSound*, 0x11DD440> pRadioAttenuationModel;
	static constexpr AddressPtr<BSSimpleList<FORadioStation*>, 0x11DD554> kActiveRadioStations;
};