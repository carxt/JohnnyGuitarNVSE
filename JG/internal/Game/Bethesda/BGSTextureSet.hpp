#pragma once

#include "BSTextureSet.hpp"
#include "DecalData.hpp"
#include "TESBoundObject.hpp"
#include "TESTexture.hpp"

class BSFileEntry;
class QueuedFile;
class BSShaderTextureSet;

class BGSTextureSet : public TESBoundObject, public BSTextureSet {
public:
	BGSTextureSet();
	~BGSTextureSet();

	enum TextureType {
		DIFFUSE,
		NORMAL,
		ENV_MASK,
		GLOW,
		PARALLAX,
		ENV
	};

	struct ALIGN2 _TextureSetFlags {
		enum Flags : uint16_t {
			NO_SPEC_MAP = 1u << 0,
		};

		bool bNoSpecMap : 1;
	};
	using TextureSetFlags = _TextureSetFlags::Flags;

	TESTexture						kTextures[6];
	DecalData*						pDecalData;
	Bitfield<_TextureSetFlags>		usTextureSetFlags;
	BSFileEntry*					pTextureFileEntries[6];

	TESFORM_TYPE(BGSTextureSet);

	bool HasDecalData() const;

	DecalData* GetDecalData() const;

	BSTextureSet* GetAsShaderTextureSet();

	BSShaderTextureSet* CreateShaderTextureSet() const;

	static BGSTextureSet* GetNullTextureSet();

private:
	static constexpr AddressPtr<BGSTextureSet*, 0x11CA898> pNullTextureSet;
};

ASSERT_SIZE(BGSTextureSet, 0xA0);