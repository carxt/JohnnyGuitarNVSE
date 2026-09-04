#pragma once

#include "SettingT.hpp"
#include <shared/BSMemory/BSMemory.hpp>

class INISettingCollection;
class INIPrefSettingCollection;
class RendererSettingCollection;
class GameSettingCollection;
class BlendSettingCollection;

template<typename COLLECTION>
inline COLLECTION* SettingT<COLLECTION>::pCollection = nullptr;

template<typename COLLECTION>
inline void SettingT<COLLECTION>::InitCollection() {
	if (!pCollection)
		pCollection = new COLLECTION();
}

// GAME - 0x44F570
// GECK - 0x41C8D0
inline void SettingT<INISettingCollection>::InitCollection() {
#ifdef GAME
	CdeclCall(0x44F570);
#else
	CdeclCall(0x41C8D0);
#endif
}

// GAME - 0x4DE4A0
// GECK - 0x40E150
inline void SettingT<INIPrefSettingCollection>::InitCollection() {
#ifdef GAME
	CdeclCall(0x4DE4A0);
#else
	CdeclCall(0x40E150);
#endif
}

// GAME - 0x45D190
inline void SettingT<RendererSettingCollection>::InitCollection() {
#ifdef GAME
	CdeclCall(0x45D190);
#else
	static constexpr AddressPtr<RendererSettingCollection*, 0xF1EF7C> _pCollection;
	if (!_pCollection) {
		_pCollection = BSMemory::create<RendererSettingCollection>();
		_pCollection.ReadAs<uint32_t*>()[0] = 0xD3F6C8;
	}
#endif
}

// GAME - 0x404A80
// GECK - 0x472C70
inline void SettingT<GameSettingCollection>::InitCollection() {
#ifdef GAME
	CdeclCall(0x404A80);
#else
	CdeclCall(0x472C70);
#endif
}

template<typename COLLECTION>
inline COLLECTION* SettingT<COLLECTION>::GetCollection() {
	InitCollection();
	return pCollection;
}

// GAME - 0x44F560
// GECK - 0x41CBC0
inline INISettingCollection* SettingT<INISettingCollection>::GetCollection() {
#ifdef GAME
	return CdeclCall<INISettingCollection*>(0x44F560);
#else
	return CdeclCall<INISettingCollection*>(0x41CBC0);
#endif
}

// GAME - 0x4DE490
// GECK - 0x40E1A0
inline INIPrefSettingCollection* SettingT<INIPrefSettingCollection>::GetCollection() {
#ifdef GAME
	return CdeclCall<INIPrefSettingCollection*>(0x4DE490);
#else
	return CdeclCall<INIPrefSettingCollection*>(0x40E1A0);
#endif
}

// GAME - 0x45D180
inline RendererSettingCollection* SettingT<RendererSettingCollection>::GetCollection() {
#ifdef GAME
	return CdeclCall<RendererSettingCollection*>(0x45D180);
#else
	InitCollection();
	return *reinterpret_cast<RendererSettingCollection**>(0xF1EF7C);
#endif
}

// GAME - 0x404A70
inline GameSettingCollection* SettingT<GameSettingCollection>::GetCollection() {
#ifdef GAME
	return CdeclCall<GameSettingCollection*>(0x404A70);
#else
	CdeclCall(0x472C70);
	return *reinterpret_cast<GameSettingCollection**>(0xF0647C);
#endif
}

#ifdef GAME
// GAME - 0x632E20
inline BlendSettingCollection* SettingT<BlendSettingCollection>::GetCollection() {
	return CdeclCall<BlendSettingCollection*>(0x632E20);
}
#endif