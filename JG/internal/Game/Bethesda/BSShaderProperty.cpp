#include "BSShaderProperty.hpp"
#include "BSShaderManager.hpp"

int32_t BSShaderProperty::GetShader() const {
	return iShader;
}

void BSShaderProperty::SetShader(int32_t aiShader) {
	iShader = aiShader;
}

// GAME - 0x4A2020
// GECK - 0x5018F0
bool BSShaderProperty::GetFlag(ShaderBits aeBit) const {
	const uint32_t uiFlagSet = aeBit >> 5;
	const uint32_t uiBit = aeBit % 32;
	return ulFlags[uiFlagSet].GetBit(uiBit);
}

// GAME - 0x441130
// GECK - 0x4BB2E0
void BSShaderProperty::SetFlag(ShaderBits aeBit, bool abEnable) {
	bool bClear = false;
	const uint32_t uiFlagSet = aeBit >> 5;
	const uint32_t uiBit = aeBit % 32;
	if (abEnable)
		bClear = ulFlags[uiFlagSet].GetAndSetBit(uiBit) == false;
	else
		bClear = ulFlags[uiFlagSet].GetAndClearBit(uiBit) == true;

	if (bClear)
		iLastRenderPassState = 0;
}

// GAME - 0xBA91A0
// GECK - 0x908DF0
void BSShaderProperty::SetFlagRecurse(NiAVObject* apObject, ShaderBits aeBit, bool abSet) {
#ifdef GAME
	CdeclCall(0xBA91A0, apObject, aeBit, abSet);
#else
	CdeclCall(0x908DF0, apObject, aeBit, abSet);
#endif
}

// GAME - 0xBA8AB0
// GECK - 0x9087D0
void BSShaderProperty::SetAlpha(float afAlpha) {
#ifdef GAME
	ThisCall(0xBA8AB0, this, afAlpha);
#else
	ThisCall(0x9087D0, this, afAlpha);
#endif
}

float BSShaderProperty::GetFadeAlpha() const {
	return fFadeAlpha;
}

// GAME - 0x819A70
void BSShaderProperty::SetFadeAlpha(float afAlpha) {
	fFadeAlpha = afAlpha;
}

float BSShaderProperty::GetEnvmapScale() const {
	return fEnvMapScale;
}

void BSShaderProperty::SetEnvmapScale(float afScale) {
	fEnvMapScale = afScale;
}

float BSShaderProperty::GetCameraDistance() const {
	return fCameraDistance;
}

// GAME - 0x4E3C00
void BSShaderProperty::ClearRenderPasses() {
	if (pRenderPassArray)
		pRenderPassArray->Clear();
}

void BSShaderProperty::SetLastRenderPassState(int32_t aiState) {
	iLastRenderPassState = aiState;
}

void BSShaderProperty::InvalidateRenderPassState() {
	iLastRenderPassState = 0;
}

bool BSShaderProperty::RenderPass::Between(uint32_t auiStart, uint32_t auiEnd) const {
	return usPassEnum > auiStart && usPassEnum < auiEnd;
}

bool BSShaderProperty::RenderPass::IsPass(uint32_t auiPassEnum) const {
	return usPassEnum == auiPassEnum;
}

// GAME - 0xBA8C30
// GECK - 0x908930
void BSShaderProperty::RenderPass::FreeLightArray() {
#ifdef GAME
	ThisCall(0xBA8C30, this);
#else
	ThisCall(0x908930, this);
#endif
}

// GAME - 0xBA8C00
// GECK - 0x908900
void BSShaderProperty::RenderPass::AllocateLightArray(uint8_t aucNumLights) {
#ifdef GAME
	ThisCall(0xBA8C00, this, aucNumLights);
#else
	ThisCall(0x908900, this, aucNumLights);
#endif
}

NiGeometry* BSShaderProperty::RenderPass::GetGeometry() const {
	return pGeometry;
}

uint16_t BSShaderProperty::RenderPass::GetPassType() const {
	return usPassEnum; 
}

// GAME - 0xBA9EE0
// GECK - 0x909B60
void BSShaderProperty::RenderPassArray::AddPass(NiGeometry* apGeometry, uint32_t auiPassEnum, bool abFirst, uint8_t aucNumLights, ShadowSceneLight* apSceneLight, ShadowSceneLight* apSceneLight1, ShadowSceneLight* apSceneLight2, ShadowSceneLight* apSceneLight3) {
#ifdef GAME
	ThisCall(0xBA9EE0, this, apGeometry, auiPassEnum, abFirst, aucNumLights, apSceneLight, apSceneLight1, apSceneLight2, apSceneLight3);
#else
	ThisCall(0x909B60, this, apGeometry, auiPassEnum, abFirst, aucNumLights, apSceneLight, apSceneLight1, apSceneLight2, apSceneLight3);
#endif
}

// GAME - 0x4E3C20
void BSShaderProperty::RenderPassArray::Clear() {
	uiPassCount = 0;
}

bool BSShaderProperty::RenderPassArray::IsEmpty() const { 
	return uiPassCount == 0; 
}

BSShaderProperty::RenderPass* BSShaderProperty::RenderPassArray::GetLastPass() const {
	return GetAt(uiPassCount - 1);
}

BSShaderProperty::RenderPass* BSShaderProperty::RenderPassArray::GetAt(uint32_t auiIndex) const {
	return kPasses.GetAt(auiIndex);
}
