#pragma once

#include <nvse/PluginAPI.h>
#include <nvse/NiTypes.h>
#include <mutex>

class JohnnyExtraData : public PluginFormExtraData, public BSMemObject {
public:
	JohnnyExtraData();
	virtual ~JohnnyExtraData() override;

	// Persistent
	struct FormData {
		NiFixedString			strEditorID;
	};

	// Temporary
	struct ScriptData {
	};

	uint32_t	uiFormID;
	TESForm*	pOwner;
	FormData	kFormData;
	ScriptData	kScriptData;

	static const NiFixedString& GetName();

	static void __fastcall Initialize(NVSEDataInterface* apNVSEData);

	static void InitName();

	static [[nodiscard]] JohnnyExtraData* __fastcall Find(const TESForm* apForm);

	static [[nodiscard]] JohnnyExtraData* __fastcall GetOrCreate(TESForm* apForm);

	static [[nodiscard]] bool __fastcall Add(TESForm* apForm, JohnnyExtraData* apExtraData);

	static [[nodiscard]] JohnnyExtraData* __fastcall Add(TESForm* apForm);
};

class JohnnyExtraDataArray {
private:
	JohnnyExtraDataArray() = default;
	JohnnyExtraDataArray(const JohnnyExtraDataArray&) = delete;
	JohnnyExtraDataArray& operator=(const JohnnyExtraDataArray&) = delete;
	
	std::mutex						kMutex;
	std::vector<JohnnyExtraData*>	kExtraDatas;

	friend class JohnnyExtraData;

	void __fastcall Add(JohnnyExtraData* apExtraData);
	void __fastcall Remove(JohnnyExtraData* apExtraData);

public:
	static JohnnyExtraDataArray& GetInstance();

	void ResetScriptData();
};
