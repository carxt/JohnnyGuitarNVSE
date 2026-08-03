#pragma once

// Helper "view" class for FormIDs;
class FormID_View {
protected:
	union {
		struct {
			uint32_t uiID    : 24;
			uint32_t uiIndex : 8;
		};
		struct {
			uint32_t usID			: 12;
			uint32_t usSmallIndex	: 12;
			uint32_t uiIndex		: 8;
		};
		uint32_t uiFormID;
	};

public:
	constexpr FormID_View(uint32_t auiFormID) noexcept : uiFormID(auiFormID) {}
	constexpr explicit FormID_View(uint8_t aucIndex, uint32_t auiID) noexcept : uiID(auiID), uiIndex(aucIndex) {}
	constexpr explicit FormID_View(uint16_t ausSmallIndex, uint16_t ausID) noexcept : usID(ausID), usSmallIndex(ausSmallIndex) { uiIndex = 0xFE; }

	constexpr uint32_t		Get() const noexcept							{ return uiFormID; }
	constexpr void			Set(uint32_t auiFormID) noexcept				{ uiFormID = auiFormID; }

	constexpr uint32_t		GetID() const noexcept							{ return uiID; }
	constexpr void			SetID(uint32_t auiID) noexcept					{ uiID = auiID; }

	constexpr uint8_t		GetIndex() const noexcept						{ return uiIndex; }
	constexpr void			SetIndex(uint8_t aucIndex) noexcept				{ uiIndex = aucIndex; }

	constexpr uint16_t		GetSmallIndex() const noexcept					{ return usSmallIndex; }
	constexpr void			SetSmallIndex(uint16_t ausSmallIndex) noexcept	{ usSmallIndex = ausSmallIndex; }

	constexpr bool			IsRuntime() const noexcept						{ return uiIndex == 0xFF; }
	constexpr bool			IsSmall() const noexcept						{ return uiIndex == 0xFE; }
	constexpr bool			IsDefault() const noexcept						{ return uiFormID != 0 && uiFormID < 0x800; }
};

ASSERT_SIZE(FormID_View, sizeof(uint32_t));