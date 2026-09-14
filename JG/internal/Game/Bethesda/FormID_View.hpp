#pragma once

// Helper "view" class for FormIDs;

using FormID = uint32_t;

class FormID_View {
protected:
	union {
		struct {
			uint32_t uiID				: 24;
			uint32_t ucCompileIndex		: 8;
		};
		struct {
			uint32_t usSmallID			: 12;
			uint32_t usSmallIndex		: 12;
			const uint32_t ucFixedIndex	: 8;
		};
		FormID uiFormID;
	};

public:
	constexpr FormID_View(FormID auiFormID) noexcept : uiFormID(auiFormID) {}
	constexpr explicit FormID_View(uint8_t aucIndex, uint32_t auiID) noexcept : uiID(auiID), ucCompileIndex(aucIndex) {}
	constexpr explicit FormID_View(uint16_t ausSmallIndex, uint16_t ausID) noexcept : usSmallID(ausID), usSmallIndex(ausSmallIndex), ucFixedIndex(0xFE) { }

	constexpr FormID		Get() const noexcept							{ return uiFormID; }
	constexpr void			Set(FormID auiFormID) noexcept					{ uiFormID = auiFormID; }

	constexpr uint32_t		GetID() const noexcept							{ return uiID; }
	constexpr void			SetID(uint32_t auiID) noexcept					{ uiID = auiID; }

	constexpr uint16_t		GetSmallID() const noexcept						{ return usSmallID; }
	constexpr void			SetSmallID(uint16_t ausSmallID) noexcept		{ usSmallID = ausSmallID; }

	constexpr uint8_t		GetCompileIndex() const noexcept				{ return ucCompileIndex; }
	constexpr void			GetCompileIndex(uint8_t aucIndex) noexcept		{ ucCompileIndex = aucIndex; }

	constexpr uint16_t		GetSmallIndex() const noexcept					{ return usSmallIndex; }
	constexpr void			SetSmallIndex(uint16_t ausSmallIndex) noexcept	{ usSmallIndex = ausSmallIndex; }

	constexpr bool			IsCreated() const noexcept						{ return ucCompileIndex == 0xFF; }
	constexpr bool			IsSmall() const noexcept						{ return ucCompileIndex == 0xFE; }
	constexpr bool			IsDefault() const noexcept						{ return uiFormID != 0 && uiFormID < 0x800; }
};

ASSERT_SIZE(FormID_View, sizeof(uint32_t));