#include "ProcessLists.hpp"

ProcessLists* ProcessLists::GetSingleton() {
	return reinterpret_cast<ProcessLists*>(0x11E0E80);
}

// GAME - 0x717E50
const ProcessArray* ProcessLists::GetProcessArray() const {
	return &kAllProcessArrays; 
}

// GAME - 0x717E50
ProcessArray* ProcessLists::GetProcessArray() {
	return &kAllProcessArrays; 
}

// GAME - 0x9764A0
bool ProcessLists::AreHostileActorsNear(bool abInterior) {
	return ThisCall<bool>(0x9764A0, this, abInterior);
}
