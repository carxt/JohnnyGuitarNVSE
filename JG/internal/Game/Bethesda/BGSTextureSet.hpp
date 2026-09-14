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

	struct _TextureType {
		enum Type {
			DIFFUSE,
			NORMAL,
			ENV_MASK,
			GLOW,
			PARALLAX,
			ENV,
			COUNT
		};
	};
	using TextureType = _TextureType::Type;

	struct ALIGN2 _TextureSetFlags {
		enum Flags : uint16_t {
			NO_SPEC_MAP = 1u << 0,
		};

		bool bNoSpecMap : 1;
	};
	using TextureSetFlags = _TextureSetFlags::Flags;

	TESTexture						kTextures[TextureType::COUNT];
	DecalData*						pDecalData;
	Bitfield<_TextureSetFlags>		usTextureSetFlags;
#ifdef GAME
	BSFileEntry*					pTextureFileEntries[TextureType::COUNT];
#endif

	TESFORM_TYPE(BGSTextureSet);

	const TESTexture* GetTESTexture(TextureType aeTexture) const;
	void SetBGSTextureFilename(TextureType aeTexture, const char* apName);

	bool HasDecalData() const;

	DecalData* GetDecalData() const;

	BSTextureSet* GetAsShaderTextureSet();

	BSShaderTextureSet* CreateShaderTextureSet() const;

	static BGSTextureSet* GetNullTextureSet();
};

#ifdef GAME
ASSERT_SIZE(BGSTextureSet, 0xA0);
#else
ASSERT_SIZE(BGSTextureSet, 0x10C);
#endif