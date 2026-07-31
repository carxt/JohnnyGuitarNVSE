#include "NiNode.hpp"

NiNode* NiNode::Create(uint16_t ausChildCount) {
#ifdef GAME
    return NiCreate<NiNode, 0xA5ECB0>(ausChildCount);
#else
    return NiCreate<NiNode, 0x810C20>(ausChildCount);
#endif
}

// GAME - 0x43B480
uint32_t NiNode::GetArrayCount() const {
    return m_kChildren.GetSize();
}

// GAME - 0x453470
uint32_t NiNode::GetChildCount() const {
    return m_kChildren.GetEffectiveSize();
}

// GAME - 0x43B4A0
NiAVObject* NiNode::GetAt(uint32_t i) const {
    return m_kChildren.GetAt(i).m_pObject;
}

// GAME - 0x45BC00
// GECK - 0x43EAC0
NiAVObject* NiNode::GetAtChecked(uint32_t i) const {
    if (GetArrayCount() <= i)
        return nullptr;

    return GetAt(i);
}

NiAVObject* NiNode::GetLastChild() const {
    if (GetChildCount() == 0)
        return nullptr;

    return GetAt(GetChildCount() - 1);
}

// GAME - 0x4ADD70
void NiNode::CompactChildArray() {
    m_kChildren.Compact();
    m_kChildren.UpdateSize();
}

void NiNode::SetChildArraySize(uint32_t auiSize) {
    m_kChildren.SetSize(auiSize);
}

// GAME  0x572160
// GECK - 0x641CD0
void NiNode::DetachAllChildren() {
#ifdef GAME
    ThisCall(0x572160, this);
#else
    ThisCall(0x641CD0, this);
#endif
}

// GAME - 0xA5E3A0
// GECK - 0x810250
void NiNode::UpdatePropertiesUpward(NiPropertyState*& apParentState) {
#ifdef GAME
    ThisCall(0xA5E3A0, this, &apParentState);
#else
    ThisCall(0x810250, this, &apParentState);
#endif
}