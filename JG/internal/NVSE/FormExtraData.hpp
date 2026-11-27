#pragma once

#include <nvse/PluginAPI.h>

namespace NVSE {

#define NVSE_FED_NAME(x) \
static inline NiFixedString strName; \
static inline bool bInitialized = NVSE::FormExtraData::RegisterExtraData(strName, x); \
static const NiFixedString& GetDataName() { assert(strName.m_kHandle); return strName; } \
virtual const NiFixedString& GetName() const override { return GetDataName(); };

#define NVSE_FED_DEFAULT_CREATE(x) \
static inline x* Create() { return new x(); };

#define NVSE_FED_FUNCS(x) \
[[nodiscard]] static inline x* __fastcall Get(const TESForm* apForm) { return NVSE::FormExtraData::Get<x>(apForm); } \
[[nodiscard]] static SPEC_NOINLINE x* __fastcall GetOrCreate(TESForm* apForm) { return NVSE::FormExtraData::GetOrCreate<x>(apForm); } \
[[nodiscard]] static SPEC_NOINLINE bool __fastcall Add(TESForm* apForm, x* apExtraData) { return NVSE::FormExtraData::Add<x>(apForm, apExtraData); } \
[[nodiscard]] static inline bool __fastcall Remove(TESForm* apForm) { return NVSE::FormExtraData::Remove<x>(apForm); }

#define NVSE_FED_DEFAULTS(x) \
NVSE_FED_NAME(#x) \
NVSE_FED_DEFAULT_CREATE(x) \
NVSE_FED_FUNCS(x)

	// Wow, it's even green!
	template<class T>
	concept FED_HasOnAdd = requires (T * a, TESForm * b) { a->OnAdd(b); };

	class FormExtraData : public PluginFormExtraData, public BSMemObject {
	protected:
		static inline _PluginFormExtraData_Get				pfGet = nullptr;
		static inline _PluginFormExtraData_Add				pfAdd = nullptr;
		static inline _PluginFormExtraData_RemoveByName		pfRemoveByName = nullptr;
		static inline _PluginFormExtraData_RemoveByPtr		pfRemoveByPtr = nullptr;

		static SPEC_NOINLINE bool __fastcall RegisterExtraData(NiFixedString& arName, const char* apName);

	public:
		static void __fastcall Init(NVSEDataInterface* apNVSEData);

		template<class T>
		[[nodiscard]] static inline T* __fastcall Get(const TESForm* apForm) {
			assert(pfGet);
			return static_cast<T*>(pfGet(apForm, T::GetDataName()));
		}

		template<class T>
		[[nodiscard]] static inline T* __fastcall GetOrCreate(TESForm* apForm) {
			if (!apForm) [[unlikely]]
				return nullptr;

			T* pData = Get<T>(apForm);
			if (pData)
				return pData;

			T* pNew = T::Create();
			if (Add(apForm, pNew)) [[likely]]
				return pNew;

			pNew->DeleteThis();
			return nullptr;
		}

		template<class T>
		[[nodiscard]] static inline bool __fastcall Add(TESForm* apForm, T* apExtraData) {
			assert(pfAdd);
			if (pfAdd(apForm, apExtraData)) [[likely]] {
				if constexpr (FED_HasOnAdd<T>) {
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
			assert(pfRemoveByName);
			return pfRemoveByName(apForm, T::GetDataName());
		}
	};

}