#pragma once

#include "BGSEntryPoint.hpp"

void BGSEntryPoint::HandleEntryPoint(BGSEntryPoint::EntryPointType aeEntryPoint, Actor* apPerkOwner, auto ...args) {
	CdeclCall(0x5E58F0, aeEntryPoint, apPerkOwner, std::forward<decltype(args)>(args)...);
}