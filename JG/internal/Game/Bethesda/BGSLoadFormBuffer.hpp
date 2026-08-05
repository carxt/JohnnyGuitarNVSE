#pragma once

#include "BGSLoadGameBuffer.hpp"
#include "BGSSaveLoadFormHeader.hpp"
#include "BGSChangeFlags.hpp"

class BGSLoadFormBuffer : public BGSLoadGameBuffer {
public:
	BGSLoadFormBuffer();
	~BGSLoadFormBuffer();

	struct ALIGN4 _LoadFormBufferFlags {
		enum Flags : uint32_t {
			SKIP_FORM			= 1u << 0,
			FORM_PENDING		= 1u << 1,
			REVERT_ONLY			= 1u << 2,
			RECONSTRUCTED_FORM	= 1u << 3,
			CELL_CHANGED		= 1u << 4,
		};

		bool bSkipForm			: 1;
		bool bFormPending		: 1;
		bool bRevertOnly		: 1;
		bool bReconstructedForm : 1;
		bool bCellChanged		: 1;
	};
	using LoadFormBufferFlags = _LoadFormBufferFlags::Flags;

	uint32_t						uiFormID;
	BGSSaveLoadFormHeader			kHeader;
	uint32_t						uiBufferSize;
	TESForm*						pForm;
	Bitfield<_LoadFormBufferFlags>	uiFlags;
	BGSChangeFlags					uiOldChangeFlags;
};

ASSERT_SIZE(BGSLoadFormBuffer, 0x30);