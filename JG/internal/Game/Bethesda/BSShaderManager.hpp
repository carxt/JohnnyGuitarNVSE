#pragma once

#include "BSTextureManager.hpp"

class ShadowSceneNode;
class NiDX9Renderer;
class NiFixedString;
class ImageSpaceManager;

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

	static constexpr AddressPtr<NiFixedString*, 0x11F94BC> pTexPercTag;

	static NiDX9Renderer* GetRenderer();

	static BSTextureManager* GetTextureManager();

	static ImageSpaceManager* GetImageSpaceManager();

	static ShadowSceneNode* GetShadowSceneNode(uint32_t aeType);

	static const NiFixedString& GetTexPercTag();
};