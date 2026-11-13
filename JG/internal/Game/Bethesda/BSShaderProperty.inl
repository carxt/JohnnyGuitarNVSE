#pragma once

#include "BSShaderProperty.hpp"

// GAME - 0xBA8C50
// GECK - 0x908950
inline void BSShaderProperty::RenderPass::SetLights(uint8_t aucNumLights, auto ...args) {
	using func_t = void(__cdecl)(BSShaderProperty::RenderPass*, uint8_t, ...);
#ifdef GAME
	CustomCall<func_t>(0xBA8C50, this, aucNumLights, std::forward<decltype(args)>(args)...);
#else
	CustomCall<func_t>(0x908950, this, aucNumLights, std::forward<decltype(args)>(args)...);
#endif
}
