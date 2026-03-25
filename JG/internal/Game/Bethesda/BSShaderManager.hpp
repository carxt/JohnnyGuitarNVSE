#pragma once

class ShadowSceneNode;

class BSShaderManager {
public:
	struct _SSNType {
		enum Type : uint32_t {
			WORLD			= 0,
			UI_TERMINALS	= 1,
			PREVIEW			= 2,
			UI_PLAYER		= 3,
			COUNT			= 4,
		};
	};
	using SceneGraphType = _SSNType::Type;


	static ShadowSceneNode* GetShadowSceneNode(uint32_t aeType);
};