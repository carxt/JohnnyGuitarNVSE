#include "BSShaderLightingProperty.hpp"

// GAME - 0xB70790
// GECK - 0x925830
uint32_t BSShaderLightingProperty::GetNumberOfActiveLights() const {
#ifdef GAME
	return ThisCall<uint32_t>(0xB70790, this);
#else
	return ThisCall<uint32_t>(0x925830, this);
#endif
}

// GAME - 0xB707D0
// GECK - 0x925870
uint32_t BSShaderLightingProperty::GetNumberOfActiveNonShadowLights() const {
#ifdef GAME
	return ThisCall<uint32_t>(0xB707D0, this);
#else
	return ThisCall<uint32_t>(0x925870, this);
#endif
}

// GAME - 0xB70490
// GECK - 0x925530
ShadowSceneLight* BSShaderLightingProperty::GetNextLight(NiTListIterator& arIter) const {
#ifdef GAME
	return ThisCall<ShadowSceneLight*>(0xB70490, this, arIter);
#else
	return ThisCall<ShadowSceneLight*>(0x925530, this, arIter);
#endif
}

// GAME - 0xB70590
// GECK - 0x925630
ShadowSceneLight* BSShaderLightingProperty::GetFirstActiveLight(NiTListIterator& arIter) const {
#ifdef GAME
	return ThisCall<ShadowSceneLight*>(0xB70590, this, arIter);
#else
	return ThisCall<ShadowSceneLight*>(0x925630, this, arIter);
#endif
}

// GAME - 0xB70680
// GECK - 0x925720
ShadowSceneLight* BSShaderLightingProperty::GetNextActiveLight(NiTListIterator& arIter) const {
#ifdef GAME
	return ThisCall<ShadowSceneLight*>(0xB70680, this, arIter);
#else
	return ThisCall<ShadowSceneLight*>(0x925720, this, arIter);
#endif
}

// GAME - 0xB70600
// GECK - 0x9256A0
ShadowSceneLight* BSShaderLightingProperty::GetFirstActiveNonShadowLight(NiTListIterator& arIter) const {
#ifdef GAME
	return ThisCall<ShadowSceneLight*>(0xB70600, this, arIter);
#else
	return ThisCall<ShadowSceneLight*>(0x9256A0, this, arIter);
#endif
}

// GAME - 0xB70700
// GECK - 0x9257A0
ShadowSceneLight* BSShaderLightingProperty::GetNextActiveNonShadowLight(NiTListIterator& arIter) const {
#ifdef GAME
	return ThisCall<ShadowSceneLight*>(0xB70700, this, arIter);
#else
	return ThisCall<ShadowSceneLight*>(0x9257A0, this, arIter);
#endif
}

// GAME - 0x4E20C0
void BSShaderLightingProperty::SetShaderConstant(uint32_t auiIndex, NiPoint4 akValue) {
	kShaderLightConstants[auiIndex] = akValue;
}

BSShaderLightingProperty::ShaderConstants& BSShaderLightingProperty::GetShaderConstants() {
	return kShaderLightConstants.ReadAs<BSShaderLightingProperty::ShaderConstants>();
}
