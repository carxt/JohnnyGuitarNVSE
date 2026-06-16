#pragma once

#include <nvse/PluginAPI.h>
#include <nvse/NiTypes.h>
#include <vector>
#include "Bethesda/BSSimpleList.hpp"

class JohnnyExtraData : public PluginFormExtraData, public BSMemObject {
public:
	JohnnyExtraData();
	virtual ~JohnnyExtraData() override;

	enum EDIDResult : uint8_t {
		FAILURE			= 0,
		SUCCESS			= 1,
		ALREADY_EXISTS	= 2,
	};

	using EDIDList = BSSimpleList<NiFixedString>;

	// Persistent
	struct FormData {
		EDIDList	kEditorIDs;
	};

	// Temporary
	struct ScriptData {
	};

	uint32_t	uiFormID;
	TESForm*	pOwner;
	FormData	kFormData;
	ScriptData	kScriptData;

	const NiFixedString& GetEditorID() const;
	EDIDResult __fastcall SetEditorID(const NiFixedString& arEDID);
	EDIDResult __fastcall RemoveEditorID(const NiFixedString& arEDID);

	static const NiFixedString& GetName();

	static void __fastcall Initialize(NVSEDataInterface* apNVSEData);

	[[nodiscard]] static JohnnyExtraData* __fastcall Find(const TESForm* apForm);

	[[nodiscard]] static JohnnyExtraData* __fastcall GetOrCreate(TESForm* apForm);

	[[nodiscard]] static bool __fastcall Add(TESForm* apForm, JohnnyExtraData* apExtraData);

	[[nodiscard]] static JohnnyExtraData* __fastcall Add(TESForm* apForm);

	// Used only by EDIDRestoration
	void DetachEditorIDs();
};

class JohnnyExtraDataArray {
private:
	JohnnyExtraDataArray() = default;
	JohnnyExtraDataArray(const JohnnyExtraDataArray&) = delete;
	JohnnyExtraDataArray& operator=(const JohnnyExtraDataArray&) = delete;
	
	SRWLOCK							kDataLock = SRWLOCK_INIT;
	std::vector<JohnnyExtraData*>	kExtraDatas;
	bool							bChanged = false;

	friend class JohnnyExtraData;

	void __fastcall Add(JohnnyExtraData* apExtraData);
	void __fastcall Remove(JohnnyExtraData* apExtraData);

public:
	static DECLSPEC_NOINLINE JohnnyExtraDataArray& GetInstance();

	void ResetScriptData();
};
