#pragma once

#include "Gamebryo/NiSmartPointer.hpp"

class NiTexture;

class SkyTextureManager {
public:
	static void LoadTextureInBackground(NiPointer<NiTexture>& arTexture, const char* apTexturePath);
};