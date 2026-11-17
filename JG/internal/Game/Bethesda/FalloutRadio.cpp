#include "FalloutRadio.hpp"

// GAME - 0x832930
FalloutRadio::FORadioReceiver* FalloutRadio::GetActiveReceiver(TESObjectREFR* apReceiverRef) {
	return CdeclCall<FORadioReceiver*>(0x832930, apReceiverRef);
}

// GAME - 0x8325B0
void FalloutRadio::ActivateRadio(TESObjectREFR* apRadioRef, bool abEnable) {
	CdeclCall(0x8325B0, apRadioRef, abEnable);
}
