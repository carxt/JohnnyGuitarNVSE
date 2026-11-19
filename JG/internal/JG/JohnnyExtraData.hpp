#pragma once

#include "Bethesda/BSSimpleList.hpp"

#include <nvse/PluginAPI.h>

#include <vector>
#include <atomic>
#include <forward_list>

#define JG_FED_NAME(x) \
static inline NiFixedString strName; \
static inline bool bInitialized = RegisterExtraData(strName, x); \
static const NiFixedString& GetDataName() { assert(strName.m_kHandle); return strName; } \
virtual const NiFixedString& GetName() const final { return GetDataName(); };

#define JG_FED_FUNCS(x) \
[[nodiscard]] static inline x* __fastcall Get(const TESForm* apForm) { return FormExtraData::Get<x>(apForm); } \
[[nodiscard]] static inline x* __fastcall GetOrCreate(TESForm* apForm) { return FormExtraData::GetOrCreate<x>(apForm); } \
[[nodiscard]] static inline bool __fastcall Add(TESForm* apForm, x* apExtraData) { return FormExtraData::Add<x>(apForm, apExtraData); } \
static inline bool __fastcall Remove(TESForm* apForm) { return FormExtraData::Remove<x>(apForm); }

// Wow, it's even green!
template<class T>
concept JG_FED_HasOnAdd = requires (T* a, TESForm* b) { a->OnAdd(b); };

class FormExtraData : public PluginFormExtraData, public BSMemObject {
protected:
	static _PluginFormExtraData_Get				pfGet;
	static _PluginFormExtraData_Add				pfAdd;
	static _PluginFormExtraData_RemoveByName	pfRemoveByName;
	static _PluginFormExtraData_RemoveByPtr		pfRemoveByPtr;
	
	static inline std::atomic_uint32_t uiCurrentDataCount = 0;
	static inline std::forward_list<std::pair<NiFixedString&, const char*>> kRegistrationQueue;

	static SPEC_NOINLINE bool __fastcall RegisterExtraData(NiFixedString& arName, const char* apName);

public:
	static SPEC_NOINLINE void __fastcall Initialize(NVSEDataInterface* apNVSEData);

	template<class T>
	[[nodiscard]] static inline T* __fastcall Get(const TESForm* apForm) {
		return static_cast<T*>(pfGet(apForm, T::GetDataName()));
	}

	template<class T>
	[[nodiscard]] static inline T* __fastcall GetOrCreate(TESForm* apForm) {
		if (!apForm) [[unlikely]]
			return nullptr;

		T* pData = Get<T>(apForm);
		if (pData)
			return pData;

		T* pNew = new T();
		if (Add(apForm, pNew)) [[likely]]
			return pNew;

		pNew->DeleteThis();
		return nullptr;
	}

	template<class T>
	[[nodiscard]] static inline bool __fastcall Add(TESForm* apForm, T* apExtraData) {
		if (pfAdd(apForm, apExtraData)) [[likely]] {
			if constexpr (JG_FED_HasOnAdd<T>) {
				return apExtraData->OnAdd(apForm);
			}
			else {
				return true;
			}
		}
		return false;
	}

	template<class T>
	[[nodiscard]] static inline bool __fastcall Remove(TESForm* apForm) {
		return pfRemoveByName(apForm, T::GetDataName());
	}

protected:
	virtual ~FormExtraData() override;
public:
	FormExtraData();

	static uint32_t GetDataCount();
};

class JohnnyExtraData final : public FormExtraData {
protected:
	virtual ~JohnnyExtraData();

	void Reset();

public:
	JohnnyExtraData();
	virtual bool OnRemoval(TESForm* apForm, uint32_t aeRemovalReason);

	bool OnAdd(TESForm* apForm);

	JG_FED_NAME("JohnnyExtraData");
	JG_FED_FUNCS(JohnnyExtraData);

	TESForm*	pOwner;

	const char* GetOwnerEDID() const;

#ifdef GAME
	enum EDIDResult : uint8_t {
		FAILURE			= 0,
		SUCCESS			= 1,
		ALREADY_EXISTS	= 2,
	};

	using EDIDList = BSSimpleList<NiFixedString>;

	EDIDList	kEditorIDs;

	const NiFixedString& GetEditorID() const;
	EDIDResult __fastcall SetEditorID(const NiFixedString& arEDID);
	EDIDResult __fastcall RemoveEditorID(const NiFixedString& arEDID);
	EDIDList* GetEditorIDHead();

	// Used only by EDIDRestoration
	void DetachEditorIDs();
#endif
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
