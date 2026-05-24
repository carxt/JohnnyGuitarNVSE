#pragma once

class NiCamera;
class NiAVObject;
class BSCullingProcess;
class BSShaderAccumulator;

class BSShaderUtil {
public:
	static void AccumulateScene(const NiCamera* apCamera, NiAVObject* apNode, BSCullingProcess* apCullingProcess);
	static void RenderScene(NiCamera* apCamera, BSShaderAccumulator* apAccumulator);
};