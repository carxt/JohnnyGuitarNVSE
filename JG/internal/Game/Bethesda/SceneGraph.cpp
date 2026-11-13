#include "SceneGraph.hpp"

// GAME - 0x878610
SceneGraph* SceneGraph::Create(const char* apName, bool abMenuSceneGraph, NiCamera* apCamera) {
    return NiCreate<SceneGraph, 0x878610>(apName, abMenuSceneGraph, apCamera);
}