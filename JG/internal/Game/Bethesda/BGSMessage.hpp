#pragma once

#include "TESForm.hpp"
#include "TESCondition.hpp"
#include "TESDescription.hpp"
#include "TESFullName.hpp"

class BGSMenuIcon;

class BGSMessage : public TESForm, public TESFullName, public TESDescription {
public:
	BGSMessage();
	~BGSMessage();

	struct ALIGN4 _MessageFlags {
		enum Flags {
			MESSAGE_BOX  = 1u << 0,
			AUTO_DISPLAY = 1u << 1,
		};

		bool bMessageBox	: 1;
		bool bAutoDisplay	: 1;
	};
	using MessageFlags = _MessageFlags::Flags;

	struct Button {
		BSString		strText;
		TESCondition	kCondition;
	};

	BGSMenuIcon*			pIcon;
	BSSimpleList<Button*>	kButtons;
	Bitfield<_MessageFlags>	uiMessageFlags;
	uint32_t				uiDisplayTime;

	TESFORM_TYPE(BGSMessage);

	bool GetIsMessageBox() const;
	void SetIsMessageBox(bool abVal);

	bool GetAutoDisplay() const;
	void SetAutoDisplay(bool abVal);

	BGSMenuIcon* GetIcon() const;
	void SetIcon(BGSMenuIcon* apIcon);

	const BSSimpleList<Button*>* GetButtonList() const;
	BSSimpleList<Button*>* GetButtonList();
	void AddButton(Button* apButton);

	uint32_t GetDisplayTime() const;
	void SetDisplayTime(uint32_t auiTime);

};

ASSERT_SIZE(BGSMessage, 0x40);