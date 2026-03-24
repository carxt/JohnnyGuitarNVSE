#pragma once

#include <atomic>

template <typename T>
class CustomClass : public T {
	static_assert(std::is_polymorphic_v<T>, "CustomClass requires a polymorphic class.");

protected:
	struct FunctionOverride {
		uint32_t	uiIndex;
		void*		pFuncPtr;

		template<typename FuncType>
		constexpr FunctionOverride(uint32_t auiIndex, const FuncType& arFunc) noexcept : uiIndex(auiIndex) {
			union {
				FuncType	kFunc;
				void*		pFuncPtr;
			} kConversion({ .kFunc = arFunc });
			pFuncPtr = kConversion.pFuncPtr;
		}
	};

	template<typename PROVIDER, std::size_t VTABLE_SIZE>
	class VTableOverride {
		static_assert(std::is_base_of_v<PROVIDER, T>, "VTableOverride requires the provider class to be a base of the target class.");
		static_assert(std::is_polymorphic_v<PROVIDER>, "VTableOverride requires a polymorphic class.");

		using VTABLE = void**;

		static inline void* kVTable[VTABLE_SIZE] = {};

		inline void CopyVTable(T* apThis, std::size_t auiSource = 0) noexcept {
			VTABLE ppSourceFunctions;
			if (auiSource == 0) {
				PROVIDER* pSource = static_cast<PROVIDER*>(apThis);
				ppSourceFunctions = *reinterpret_cast<VTABLE*>(pSource);
			}
			else {
				ppSourceFunctions = reinterpret_cast<VTABLE>(auiSource);
			}
			memcpy(kVTable, ppSourceFunctions, VTABLE_SIZE * sizeof(void*));
		}
	public:
		inline VTableOverride(T* apThis, std::size_t auiSource = 0) noexcept {
			if (!HasBeenInitialized()) {
				CopyVTable(apThis, auiSource);
			}
		}

		inline VTableOverride(T* apThis, const std::initializer_list<const FunctionOverride>& arFunctions, std::size_t auiSource = 0) noexcept {
			if (!HasBeenInitialized()) {
				CopyVTable(apThis, auiSource);

				for (const auto& rEntry : arFunctions) {
					if (rEntry.uiIndex >= VTABLE_SIZE)
						continue;
					kVTable[rEntry.uiIndex] = rEntry.pFuncPtr;
				}
			}
			Apply(apThis);
		}

		template<typename FuncType>
		inline void __fastcall SetFunction(uint32_t auiIndex, const FuncType& arFunc) {
			union {
				FuncType	func;
				void*		funcPtr;
			} conversion;
			conversion.func = arFunc;
			kVTable[auiIndex] = conversion.funcPtr;
		}

		inline void __fastcall  Apply(T* apTarget) {
			PROVIDER* pSource = static_cast<T*>(apTarget);
			*reinterpret_cast<VTABLE*>(pSource) = kVTable;
		}

		inline bool HasBeenInitialized() noexcept {
			return kVTable[0] != nullptr;
		}
	};

	template<typename PROVIDER, std::size_t VTABLE_SIZE>
	inline void __fastcall  BuildVTable(const std::initializer_list<const FunctionOverride>& arFunctions, std::size_t auiSource = 0) {
		VTableOverride<PROVIDER, VTABLE_SIZE>(this, arFunctions, auiSource);
	}

	template<typename TARGET>
	inline const TARGET* GetAs() const 
		requires std::derived_from<T, TARGET> {
		return static_cast<TARGET*>(this);
	}

	template<typename TARGET>
	inline TARGET* GetAs() 
		requires std::derived_from<T, TARGET> {
		return static_cast<TARGET*>(this);
	}

	template<typename TARGET>
	inline const TARGET* ReadAs() const
		requires std::derived_from<T, TARGET> {
		return reinterpret_cast<TARGET*>(this);
	}

	template<typename TARGET>
	inline TARGET* ReadAs()
		requires std::derived_from<T, TARGET> {
		return reinterpret_cast<TARGET*>(this);
	}


};