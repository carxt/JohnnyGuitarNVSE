#pragma once

#include <nvse/FormExtraData.hpp>
#include "Bethesda/BSSimpleList.hpp"

class JGExtraData final : public NVSE::FormExtraData {
protected:
	virtual ~JGExtraData() override;

	void Reset();

public:
	JGExtraData();
	virtual void DeleteThis() override;
	virtual bool OnRemoval(TESForm* apForm, uint32_t aeRemovalReason) override;
	virtual TESForm* GetOwner() const;
	virtual const char* GetOwnerEDID() const;

	NVSE_FED_NAME("JGExtraData");
	NVSE_FED_FUNCS(JGExtraData);
	static JGExtraData* Create();
	bool OnAdd(TESForm* apForm);

	TESForm*	pOwner;

	template<class T>
	T* GetOwner() const { return static_cast<T*>(GetOwner()); };

#ifdef GAME
	enum EDIDResult : uint8_t {
		FAILURE			= 0,
		SUCCESS			= 1,
		ALREADY_EXISTS	= 2,
	};

	using EDIDList = BSSimpleList<NiFixedString>;

	EDIDList	kEditorIDs;

	virtual const NiFixedString& GetEditorID() const;
	virtual EDIDResult __fastcall SetEditorID(const NiFixedString& arEDID);
	virtual EDIDResult __fastcall RemoveEditorID(const NiFixedString& arEDID);
	EDIDList* GetEditorIDHead();

	// Used only by EDIDRestoration
	void DetachEditorIDs();
#endif
};