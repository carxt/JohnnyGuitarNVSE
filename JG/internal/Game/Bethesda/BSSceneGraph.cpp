#include "BSSceneGraph.hpp"

// GAME - 0x6629F0
NiCamera* BSSceneGraph::GetCamera() const {
    return spCamera;
}

// GAME - 0x8D80E0
BSCullingProcess* BSSceneGraph::GetCullingProcess() const {
    return pCuller;
}

// GAME - 0x99E040
float BSSceneGraph::GetCameraFOV() const {
    return fCurrentFOV;
}

// GAME - 0xC52020
void BSSceneGraph::SetCameraFOV(float afFOV, bool abForce, NiCamera* apCamera, bool abSetLODMult) {
    ThisCall(0xC52020, this, afFOV, abForce, apCamera, abSetLODMult);
}

// GAME - 0x558310
NiNode* BSSceneGraph::GetCameraRoot() const {
    return static_cast<NiNode*>(GetAtChecked(0));
}
