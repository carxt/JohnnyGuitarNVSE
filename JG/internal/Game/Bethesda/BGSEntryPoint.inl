#pragma once

#include "BGSEntryPoint.hpp"

// GAME - 0x5E58F0
void BGSEntryPoint::HandleEntryPoint(BGSEntryPoint::EntryPointType aeEntryPoint, Actor* apPerkOwner, auto ...args) {
	using func_t = void(__cdecl)(BGSEntryPoint::EntryPointType, Actor*, ...);
	CustomCall<func_t>(0x5E58F0, aeEntryPoint, apPerkOwner, std::forward<decltype(args)>(args)...);
}