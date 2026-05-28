#pragma once

#include "NiTexture.hpp"
#include "NiPersistentSrcTextureRendererData.hpp"
#include "NiPixelData.hpp"

NiSmartPointer(NiSourceTexture);

class NiFile;

class NiSourceTexture : public NiTexture {
public:
	NiSourceTexture();
	virtual ~NiSourceTexture();

	virtual void LoadPixelDataFromFile();
	virtual void DestroyAppPixelData();
	virtual bool CreateRendererData();

	NiFixedString							m_kFilename;
	NiFixedString							m_kPlatformFilename;
	NiPersistentSrcTextureRendererDataPtr	m_spPersistentSrcRendererData;
	NiPixelDataPtr							m_spSrcPixelData;
	bool									m_bStatic;
	bool									m_bLoadDirectToRendererHint;
	bool									m_bSrcRendererDataIsPersistent;
	bool									unk43;
	NiFile*									m_pFile;

	CREATE_OBJECT(NiSourceTexture, 0xA60070);
	NIRTTI_ADDRESS(0x11F444C);

	static constexpr AddressPtr<NiTexture::FormatPrefs, 0x11A9598> ms_kDefaultPrefs;
	
	static NiSourceTexture* CreateTexture(NiFile* apFile, const char* apPath, const FormatPrefs& arPrefs, bool abLoadDirectToRendererHint);

	static NiSourceTexture* Create(const NiFixedString& arFilename, const FormatPrefs& arPrefs, bool abLoadDirectToRendererHint, bool abSrcRendererDataIsPersistent);
};

ASSERT_SIZE(NiSourceTexture, 0x48);