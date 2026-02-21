#pragma once

#include "SettingT.hpp"
#include <type_traits>

class INISettingCollection;
class INIPrefSettingCollection;
class RendererSettingCollection;
class GameSettingCollection;
class BlendSettingCollection;

template<typename COLLECTION>
inline COLLECTION* SettingT<COLLECTION>::GetCollection() {
	if constexpr (std::is_same<COLLECTION, INISettingCollection>::value) {
#ifdef GAME
		return CdeclCall<COLLECTION*>(0x44F560);
#else
		return CdeclCall<COLLECTION*>(0x41CBC0);
#endif
	}
	else if constexpr (std::is_same<COLLECTION, INIPrefSettingCollection>::value) {
#ifdef GAME
		return CdeclCall<COLLECTION*>(0x4DE490);
#else
		return CdeclCall<COLLECTION*>(0x40E1A0);
#endif
	}
	else if constexpr (std::is_same<COLLECTION, RendererSettingCollection>::value) {
#ifdef GAME
		return CdeclCall<COLLECTION*>(0x45D180);
#else
		COLLECTION* Collection = BSMemory::create<COLLECTION>();
		if (Collection) {
			((DWORD*)Collection)[0] = (DWORD)0xD3F6C8;
			*reinterpret_cast<COLLECTION**>(0xF1EF7C) = Collection;
		}
		return *reinterpret_cast<COLLECTION**>(0xF1EF7C);
#endif
	}
	else if constexpr (std::is_same<COLLECTION, GameSettingCollection>::value) {
#ifdef GAME
		return CdeclCall<COLLECTION*>(0x404A70);
#else
		CdeclCall(0x472C70);
		return *reinterpret_cast<COLLECTION**>(0xF0647C);
#endif
	}
#ifdef GAME
	else if constexpr (std::is_same<COLLECTION, BlendSettingCollection>::value) {
		return CdeclCall<BlendSettingCollection*>(0x632E20);
	}
#endif
	else {
		InitCollection();
		return pCollection;
	}
}

template<typename COLLECTION>
inline void SettingT<COLLECTION>::InitCollection() {
	if (!pCollection)
		pCollection = new COLLECTION();
}

template<typename COLLECTION>
inline COLLECTION* SettingT<COLLECTION>::pCollection = nullptr;