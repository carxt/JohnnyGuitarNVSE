#pragma once

class TESForm;
class TESObjectREFR;

class BGSOpenCloseForm {
public:
	virtual void	HandleOpenFinish(TESObjectREFR* apItemActivated, TESObjectREFR* apActionRef);
	virtual void	HandleCloseFinish(TESObjectREFR* apItemActivated, TESObjectREFR* apActionRef);
	virtual bool	GetBlockActivatesWhileOpening() const;

	BGSOpenCloseForm();
	~BGSOpenCloseForm();

	struct _OpenCloseState {
		enum State : uint32_t {
			NONE	= 0,
			OPEN	= 1,
			OPENING = 2,
			CLOSED	= 3,
			CLOSING = 4,
		};
	};
	using OpenCloseState = _OpenCloseState::State;

	static BGSOpenCloseForm* GetAsOpenCloseForm(const TESForm* apForm);

	static bool IsOpenCloseForm(const TESForm* apForm);

	static void HandleActivate(TESObjectREFR* apItemActivated, TESObjectREFR* apActionRef, BGSOpenCloseForm* apDoor = nullptr);

	static OpenCloseState GetOpenState(TESObjectREFR* apRef);
	static bool SetOpenState(TESObjectREFR* apRef, bool abOpen, bool abSnap);
};

ASSERT_SIZE(BGSOpenCloseForm, 0x4);