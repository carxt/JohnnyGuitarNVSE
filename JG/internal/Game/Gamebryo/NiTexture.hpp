#pragma once

#include "NiObjectNET.hpp"
#include "NiPixelFormat.hpp"
#include "Bethesda/BSDegradePriority.hpp"

NiSmartPointer(NiTexture);

class NiFixedString;
class NiDX9TextureData;

class NiTexture : public NiObjectNET {
public:
	NiTexture();
	virtual ~NiTexture();

	virtual void					Upgrade();
	virtual void					Degrade();
	virtual uint32_t				GetWidth() const;
	virtual uint32_t				GetHeight() const;
	virtual const NiFixedString&	GetFilename() const;
	virtual uint32_t				GetMemorySize() const;

	class FormatPrefs {
	public:
		struct _PixelLayout {
			enum Layout {
				PALETTIZED_8	= 0,
				HIGH_COLOR_16	= 1,
				TRUE_COLOR_32	= 2,
				COMPRESSED		= 3,
				BUMPMAP			= 4,
				PALETTIZED_4	= 5,
				DEFAULT			= 6,
				SINGLE_COLOR_8	= 7,
				SINGLE_COLOR_16 = 8,
				SINGLE_COLOR_32 = 9,
				DOUBLE_COLOR_32 = 10,
				DOUBLE_COLOR_64 = 11,
				FLOAT_COLOR_32	= 12,
				FLOAT_COLOR_64	= 13,
				FLOAT_COLOR_128 = 14,
			};
		};
		using PixelLayout = _PixelLayout::Layout;

		struct _AlphaFormat {
			enum Format {
				BINARY	= 1,
				SMOOTH	= 2,
				DEFAULT = 3,
			};
		};
		using AlphaFormat = _AlphaFormat::Format;

		struct _MipFlag {
			enum Flag {
				NO		= 0,
				YES		= 1,
				DEFAULT = 2,
			};
		};
		using MipFlag = _MipFlag::Flag;

		FormatPrefs() : m_ePixelLayout(PixelLayout::TRUE_COLOR_32), m_eAlphaFmt(AlphaFormat::SMOOTH), m_eMipMapped(MipFlag::YES) {};
		FormatPrefs(const PixelLayout& aePixelLayout, const AlphaFormat& aeAlphaFmt, const MipFlag& aeMipMapped)
			: m_ePixelLayout(aePixelLayout), m_eAlphaFmt(aeAlphaFmt), m_eMipMapped(aeMipMapped) {}
		~FormatPrefs() {};

		PixelLayout		m_ePixelLayout;
		AlphaFormat		m_eAlphaFmt;
		MipFlag			m_eMipMapped;
	};

	class RendererData : public NiObject {
	public:
		RendererData();
		virtual ~RendererData();

		virtual void		Upgrade(NiTexture* apTexture);
		virtual void		Degrade(NiTexture* apTexture);
		virtual uint32_t	ComputeAliasSize();

		NiTexture*			m_pkTexture;
		uint32_t			m_uiWidth;
		uint32_t			m_uiHeight;
		NiPixelFormat		m_kPixelFormat;
		BSDegradePriority   kDegradePriorityRange;
		Bitfield8			ucFlags;

		bool IsAlphaTexture() const {
			return m_kPixelFormat.IsAlpha();
		}
	};

	FormatPrefs		m_kFormatPrefs;
	RendererData*	m_pkRendererData;
	NiTexture*		m_pkPrev;
	NiTexture*		m_pkNext;

	NIRTTI_ADDRESS(0x11F450C);

	RendererData* GetRendererData() const;

	template<class T>
	T* GetRenderedData() const {
		return static_cast<T*>(GetRenderedData());
	}

	bool IsAlphaTexture() const;

	static NiTexture* GetListHead();
	static NiTexture* GetListTail();
};

ASSERT_SIZE(NiTexture, 0x30);
ASSERT_SIZE(NiTexture::RendererData, 0x60);