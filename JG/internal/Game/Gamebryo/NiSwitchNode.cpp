#include "NiSwitchNode.hpp"

NiAVObject* NiSwitchNode::GetActiveChild() {
    return GetAt(m_iIndex);
}

bool NiSwitchNode::GetUpdateOnlyActiveChild() const {
    return m_usFlags.bUpdateOnlyActiveChild;
}

void NiSwitchNode::SetUpdateOnlyActiveChild(bool abEnable) {
    m_usFlags.bUpdateOnlyActiveChild = abEnable;
}

bool NiSwitchNode::GetUpdateControllers() const {
    return m_usFlags.bUpdateControllers;
}

void NiSwitchNode::SetUpdateControllers(bool abEnable) {
    m_usFlags.bUpdateControllers = abEnable;
}

int32_t NiSwitchNode::GetIndex() const {
    return m_iIndex;
}

void NiSwitchNode::SetIndex(int32_t aiIndex) {
    if (aiIndex >= -1 && aiIndex < static_cast<int32_t>(m_kChildren.GetSize()))
        m_iIndex = aiIndex;
}

float NiSwitchNode::GetSavedTime() const {
    return m_fSavedTime;
}