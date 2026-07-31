#include "netimmerse.h"

NiNode* NiNode::GetNode(const char* nodeName) {
	NiAVObject* found = GetBlock(nodeName);
	return found ? found->IsNode() : NULL;
}

NiNode* NiNode::Create(uint16_t ausChildCount) {
#ifdef GAME
	return NiCreate<NiNode, 0xA5ECB0>(ausChildCount);
#else
	return NiCreate<NiNode, 0x810C20>(ausChildCount);
#endif
}

NiAVObject* NiNode::GetBlock(const char* blockName) {
	return GetObjectByName(blockName);
}