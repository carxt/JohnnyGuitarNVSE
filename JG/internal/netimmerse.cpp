#include "netimmerse.h"

// GAME - 0xA59D30
NiProperty* NiAVObject::GetProperty(uint32_t auiType) const {
	return ThisCall<NiProperty*>(0xA59D30, this, auiType);
}

float __declspec(naked) __fastcall NiNodeComputeDistance(NiPoint3* Vector1, NiPoint3* Vector2) {
	__asm
	{
		movd xmm0, [ecx]
		subss xmm0, [edx]
		mulss xmm0, xmm0
		movd xmm1, [ecx + 4]
		subss xmm1, [edx + 4]
		mulss xmm1, xmm1
		movd xmm2, [ecx + 8]
		subss xmm2, [edx + 8]
		mulss xmm2, xmm2
		addss xmm0, xmm1
		addss xmm0, xmm2
		sqrtss xmm0, xmm0
		movd eax, xmm0
		push eax
		fld dword ptr[esp]
		add esp, 4
		ret
	}
}


float __declspec(naked) __fastcall NiNodeComputeDistance2DSquared(NiPoint3* Vector1, NiPoint3* Vector2) {
	__asm
	{
		movd xmm0, [ecx]
		subss xmm0, [edx]
		mulss xmm0, xmm0
		movd xmm1, [ecx + 4]
		subss xmm1, [edx + 4]
		mulss xmm1, xmm1
		addss xmm0, xmm1
		movd eax, xmm0
		push eax
		fld dword ptr[esp]
		add esp, 4
		ret
	}
}

NiNode* NiNode::GetNode(const char* nodeName) {
	NiAVObject* found = GetBlock(nodeName);
	return found ? found->IsNode() : NULL;
}

void NiPointAssign(NiPoint3* NiPointBuffer, float& xIn, float& yIn, float& zIn) {
	NiPointBuffer->x = xIn;
	NiPointBuffer->y = yIn;
	NiPointBuffer->z = zIn;
}

NiAVObject* NiNode::GetBlock(const char* blockName) {
	return GetObjectByName(blockName);
}