#pragma once

#include "BSHash.hpp"

class BSFileEntry : public BSHash {
public:
	struct ALIGN4 _SizeFlags {
		enum Flags : uint32_t {
			SIZE_MASK	= 0x3FFFFFFF,
			COMPRESSION = 1u << 30,
			CHECKED		= 1u << 31,
		};

		uint32_t uiSize			: 30 = 0;
		BOOL	 bCompression	: 1  = 0;
		BOOL	 bChecked		: 1  = 0;
	};
	using SizeFlags = _SizeFlags::Flags;

	struct ALIGN4 _OffsetFlags {
		enum Flags : uint32_t {
			OFFSET_MASK			= 0x7FFFFFFF,
			SECONDARY_ARCHIVE	= 1u << 31,
		};
		
		uint32_t uiOffset			: 31 = 0;
		BOOL	 bSecondaryArchive	: 1	 = 0;
	};
	using OffsetFlags = _OffsetFlags::Flags;

	Bitfield<_SizeFlags>	uiSize;
	Bitfield<_OffsetFlags>	uiOffset;

	uint32_t GetFileSize() const;

	uint32_t GetFileOffset() const;
	void SetOffset(uint32_t auiOffset);

	bool IsSecondaryArchive() const;

	bool GetCompressionFlag() const;

	bool IsChecked() const;
	void SetChecked(bool abChecked);

	bool IsInvalidated() const;
};

ASSERT_SIZE(BSFileEntry, 0x10);