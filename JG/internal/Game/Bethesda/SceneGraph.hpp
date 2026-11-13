#pragma once

#include "BSSceneGraph.hpp"

NiSmartPointer(SceneGraph);

class SceneGraph : public BSSceneGraph {
public:
	static SceneGraph* Create(const char* apName, bool abMenuSceneGraph = false, NiCamera* apCamera = nullptr);
};