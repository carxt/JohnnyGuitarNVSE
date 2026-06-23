#include "FixedStringsRework.hpp"
#include "JIP/JIPUtils.hpp"
#include "Utilities.h"

#include "Bethesda/AutoMemContext.hpp"
#include "Gamebryo/NiGlobalStringTable.hpp"

#include "shared/BSMemory/BSMemory.hpp"
#include "shared/BSMemory/BSScrapMemory.hpp"

#include <vector>
#include <algorithm>
#include <execution>
#include <span>

STACK_FRAME_OPT_ENABLE
#pragma warning(disable: 4200)

namespace FixedStringsRework {

#define FIXED_STRING_DEBUG 0
#define FIXED_STRING_ASYNC_CLEANUP 0

	class ALIGN16 String {
		volatile mutable uint32_t	uiRefCount;
		uint32_t					uiLength;
		char						cText[];

		String() = delete;
		String(const String&) = delete;
		String(String&&) = delete;
		~String() = delete;

		inline void __fastcall _Create(const std::string_view& arString) noexcept {
			uiRefCount = 0;
			uiLength = arString.length();
			CopyString(arString.data());
		}

		inline void __fastcall CopyString(const char* apText) {
			memcpy(cText, apText, uiLength);
			cText[uiLength] = '\0';
		}

		// Both strings must have the same length
		static constexpr bool __fastcall StringMatch(const char* __restrict apStr1, const char* __restrict apStr2) noexcept {
			ASSUME_ASSERT(apStr1 && apStr2 && apStr1 != apStr2);
			do {
				if (*apStr1 != *apStr2)
					return false;
				apStr1++;
				apStr2++;
			} while (*apStr1);
			return true;
		}

	public:
		constexpr const char* GetText() const noexcept {
			return cText;
		}

		constexpr uint32_t GetLength() const noexcept {
			return uiLength;
		}

		constexpr uint32_t GetRefCount() const noexcept {
			return uiRefCount;
		}

		inline bool IsDeleted() const noexcept {
			uint32_t uiExpected = 0;
			return InterlockedCompareExchange(&uiRefCount, 0, uiExpected) == uiExpected;
		}

		inline void IncRefCount() noexcept {
			InterlockedIncrement(&uiRefCount);
		}

		// Returns the string pointer and increments the reference count.
		[[nodiscard]] inline const char* Take() noexcept {
			IncRefCount();
			return cText;
		}

		constexpr bool __fastcall Match(const std::string_view& arString) const noexcept {
			if (cText == arString.data()) [[unlikely]]
				return true;

			ASSUME_ASSERT(uiLength && arString.length());
			if (uiLength == arString.length()) [[likely]] {
				if (StringMatch(cText, arString.data())) [[likely]]
					return true;
			}

#if FIXED_STRING_DEBUG
			++NiGlobalStringTable::uiTotalCollisions;
			_MESSAGE("Hash conflict - \"%s\" with \"%s\"", cText, arString.data());
#endif
			return false;
		}

		static constexpr uint32_t __fastcall GetMemorySize(uint32_t auiLength) noexcept {
			static constexpr uint32_t uiAlignment = 4;

			uint32_t uiAllocSize = sizeof(String);

			if (auiLength >= sizeof(uint32_t) * 2) [[likely]] {
				uiAllocSize += sizeof(char) + auiLength;
				const uint32_t uiSpillover = uiAllocSize % uiAlignment;
				if (uiSpillover != 0)
					uiAllocSize += uiAlignment - uiSpillover;
			}

			return uiAllocSize;
		}

		static String* __fastcall Create(const std::string_view& arString) noexcept {
			const uint32_t uiAllocSize = GetMemorySize(arString.length());
			String* pString = static_cast<String*>(BSMemory::malloc(uiAllocSize));
			pString->_Create(arString);
			++NiGlobalStringTable::uiTotalStrings;
			return pString;
		};

		static void __fastcall Destroy(String* apString) noexcept {
			BSMemory::free(apString);
			--NiGlobalStringTable::uiTotalStrings;
		}

		static String strEmptyString;
	};

	template<uint32_t INITIAL_SIZE>
	class ALIGN16 StringArray {
		struct StringEntry {
			constexpr StringEntry() noexcept : uiHash(0), pString(nullptr) {};
			constexpr StringEntry(uint32_t auiHash, String* apString) noexcept : uiHash(auiHash), pString(apString) {};
			constexpr StringEntry(const StringEntry& arOther) noexcept : uiHash(arOther.uiHash), pString(arOther.pString) {};
			constexpr StringEntry(StringEntry&& arOther) noexcept : uiHash(arOther.uiHash), pString(arOther.pString) { arOther.uiHash = 0; arOther.pString = nullptr; }
			constexpr ~StringEntry() noexcept {}

			uint32_t	uiHash;
			String* 	pString;

			constexpr void operator=(const StringEntry& arOther) noexcept {
				uiHash = arOther.uiHash;
				pString = arOther.pString;
			}

			constexpr void operator=(StringEntry&& arOther) noexcept {
				uiHash = arOther.uiHash;
				pString = arOther.pString;
				arOther.uiHash = 0;
				arOther.pString = nullptr;
			}

			constexpr operator const String* () const noexcept {
				return pString;
			}

			constexpr operator String* () noexcept {
				return pString;
			}

			constexpr const String* operator->() const noexcept {
				return pString;
			}

			constexpr String* operator->() noexcept {
				return pString;
			}

			constexpr bool __fastcall Match(const std::string_view& arString, uint32_t auiHash) const noexcept {
				ASSUME_ASSERT(uiHash && auiHash);
				if (uiHash != auiHash) [[likely]]
					return false;

				ASSUME_ASSERT(pString != nullptr);
				if (!pString->Match(arString)) [[unlikely]]
					return false;

				return true;
			}

			constexpr uint32_t GetHash() const noexcept {
				return uiHash;
			}

			const char* Take() const noexcept {
				ASSUME_ASSERT(pString != nullptr);
				return pString->Take();
			}
		};

		std::vector<StringEntry>	kStrings;
		mutable SRWLOCK				kLock = SRWLOCK_INIT;

		const char* __fastcall GetString(const std::string_view& arString, uint32_t auiHash) const noexcept {
			for (const StringEntry& rEntry : kStrings) {
#if 0
				if (rEntry.Match(arString, auiHash))
					return rEntry.Take();
#else
				ASSUME_ASSERT(rEntry.GetHash() && auiHash);
				if (rEntry.GetHash() == auiHash) [[unlikely]] {
					ASSUME_ASSERT(rEntry.pString != nullptr);
					if (rEntry.pString->Match(arString)) [[likely]]
						return rEntry.Take();
				}

#endif
			}

			return nullptr;
		}

		const char* __fastcall CreateString(const std::string_view& arString, uint32_t auiHash) noexcept {
			MEMORY_CONTEXT(MC_STRINGS);
			StringEntry kNewEntry(auiHash, String::Create(arString));
			kStrings.push_back(kNewEntry);
			return kNewEntry.Take();
		}

		uint32_t __fastcall DestroyString(uint32_t auiIndex) noexcept {
			String::Destroy(kStrings[auiIndex]);
			kStrings[auiIndex] = kStrings.back();
			kStrings.pop_back();
			return auiIndex - 1;
		}

	public:
		StringArray() noexcept {
			MEMORY_CONTEXT(MC_STRINGS);
			kStrings.reserve(INITIAL_SIZE);
			kLock = SRWLOCK_INIT;
		}

		~StringArray() noexcept {
			SRWUniqueLock kGuard(kLock);
			for (StringEntry& rEntry : kStrings) {
				String::Destroy(rEntry.pString);
			}
		}

		const char* __fastcall GetOrCreateString(const std::string_view& arString, uint32_t auiHash) noexcept {
			const char* pFoundString = nullptr;
			// Retrieval happens more often than insertion, so let's gamble
			if (TryAcquireSRWLockShared(&kLock)) [[likely]] {
				pFoundString = GetString(arString, auiHash);
				ReleaseSRWLockShared(&kLock);
			}

			if (!pFoundString) {
				// Need to iterate again, bummer
				SRWUniqueLock kGuard(kLock);
				pFoundString = GetString(arString, auiHash);
				if (!pFoundString)
					pFoundString = CreateString(arString, auiHash);
			}

			return pFoundString;
		}

		void __fastcall FreeUnusedStrings() noexcept {
			SRWUniqueLock kGuard(kLock);
			for (uint32_t i = 0; i < kStrings.size();) {
				if (kStrings[i]->IsDeleted()) {
					i = DestroyString(i);
				}
				else {
					++i;
				}
			}
			
			const uint32_t uiSize = kStrings.size();
			const uint32_t uiCapacity = kStrings.capacity();
			if (uiSize < uiCapacity / 2)
				kStrings.shrink_to_fit();

			std::sort(kStrings.begin(), kStrings.end(), [](String* a, String* b) {
				if (a->GetRefCount() == b->GetRefCount()) {
					return a->GetLength() < b->GetLength();
				}
				return a->GetRefCount() > b->GetRefCount();
				});
		}

#if FIXED_STRING_DEBUG
		uint32_t DumpInfo() noexcept {
			SRWSharedLock kGuard(&kLock);
			uint32_t uiMemoryUsage = kStrings.capacity() * (sizeof(StringEntry) + sizeof(String*));

			for (const StringEntry& rEntry : kStrings) {
				uiMemoryUsage += String::GetMemorySize(rEntry->GetLength());
				_MESSAGE("	Hash: %08X | RefCount: %u | Length: %u | String: \"%s\"", rEntry.GetHash(), rEntry->GetRefCount(), rEntry->GetLength(), rEntry->GetText());
			}
			_MESSAGE("Capacity: %u | Total strings: %u | Memory Usage: %u bytes", kStrings.capacity(), kStrings.size(), uiMemoryUsage);

			return uiMemoryUsage;
		}
#endif
	};

	template<uint32_t CONTAINER_SIZE>
	using StringContainer = StringArray<CONTAINER_SIZE>;

	template<uint32_t CONTAINER_COUNT, uint32_t CONTAINER_SIZE>
	class FixedStringTable {
#if FIXED_STRING_ASYNC_CLEANUP
		HANDLE hBackgroundThread	= nullptr;
		HANDLE hCleanupEvent		= nullptr;
		HANDLE hThreadExitEvent		= nullptr;
#endif
		StringContainer<CONTAINER_SIZE> kContainers[CONTAINER_COUNT];

		static inline String* pEmptyString = nullptr;

		static constexpr uint32_t __fastcall GetStringHash(const std::string_view& arString) noexcept {
			static constexpr std::hash<std::string_view> kStringHasher;
			return kStringHasher(arString);
		}

		static constexpr uint32_t __fastcall GetContainerIndex(uint32_t auiHash) noexcept {
			return auiHash % CONTAINER_COUNT;
		}
		
		// TODO: Use BSTasklets for this instead of creating new threads
		void __fastcall FreeUnusedStrings() noexcept {
			const std::span<StringContainer<CONTAINER_SIZE>> kContSpan(kContainers, CONTAINER_COUNT);

			std::for_each(std::execution::par, kContSpan.begin(), kContSpan.end(), [](StringContainer<CONTAINER_SIZE>& arCont) {
				arCont.FreeUnusedStrings();
				});
		}

		void __fastcall GarbageCollection() {
#if FIXED_STRING_DEBUG
			const uint32_t uiTotalStrings = NiGlobalStringTable::uiTotalStrings.Get();
			FreeUnusedStrings();
			const uint32_t uiFreedStrings = uiTotalStrings - NiGlobalStringTable::uiTotalStrings.Get();
			_MESSAGE("Freed %u strings", uiFreedStrings);
			DumpInfo();
#else
			FreeUnusedStrings();
#endif
		}

	public:
		FixedStringTable() noexcept {
			pEmptyString = String::Create("");
#if FIXED_STRING_ASYNC_CLEANUP
			hBackgroundThread = CreateThread(nullptr, 0, [](void* apParam) -> DWORD {
				FixedStringTable* pManager = static_cast<FixedStringTable*>(apParam);
				HANDLE hEvents[2] = { pManager->hCleanupEvent, pManager->hThreadExitEvent };
				while (true) {
					DWORD dwWaitResult = WaitForMultipleObjects(2, hEvents, FALSE, INFINITE);
					if (dwWaitResult == WAIT_OBJECT_0) {
						pManager->GarbageCollection();
						ResetEvent(pManager->hCleanupEvent);
					}
					else if (dwWaitResult == WAIT_OBJECT_0 + 1) {
						break;
					}
				}
				return 0;
				}, this, 0, nullptr);

			hCleanupEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
			hThreadExitEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
#endif
		};
		~FixedStringTable() noexcept {
			String::Destroy(pEmptyString);
#if FIXED_STRING_ASYNC_CLEANUP
			if (hBackgroundThread) {
				SetEvent(hThreadExitEvent);
				WaitForSingleObject(hBackgroundThread, INFINITE);
				CloseHandle(hBackgroundThread);
			}

			if (hCleanupEvent)
				CloseHandle(hCleanupEvent);

			if (hThreadExitEvent)
				CloseHandle(hThreadExitEvent);
#endif
		}

		const char* __fastcall GetString(const char* apString) noexcept {
			if (!apString) [[unlikely]]
				return nullptr;

			if (apString[0] == '\0') [[unlikely]]
				return pEmptyString->Take();

			const std::string_view svString(apString);
			const uint32_t uiHash = GetStringHash(svString);
			const uint32_t uiContainer = GetContainerIndex(uiHash);
			return kContainers[uiContainer].GetOrCreateString(svString, uiHash);
		}

		void __fastcall RequestStringCleanup() noexcept {
#if FIXED_STRING_ASYNC_CLEANUP
			SetEvent(hCleanupEvent);
#else
			GarbageCollection();
#endif
		}

#if FIXED_STRING_DEBUG
		void __fastcall DumpInfo() noexcept {
			uint32_t uiSize = 0;
			_MESSAGE("=== Fixed String Manager Info ===");
			for (uint32_t i = 0; i < CONTAINER_COUNT; i++) {
				_MESSAGE("\nContainer %i:", i);
				uiSize += kContainers[i].DumpInfo();
			}
			_MESSAGE("\nTotal strings: %u", NiGlobalStringTable::uiTotalStrings.Get());
			_MESSAGE("Total collisions: %u", NiGlobalStringTable::uiTotalCollisions.Get());
			_MESSAGE("Memory usage: %u bytes", uiSize);
			_MESSAGE("Empty string users: %u", pEmptyString->GetRefCount());
		}
#endif
	};

	namespace Data {
		constexpr uint32_t STRING_MAP_COUNT = 1023;
		constexpr uint32_t STRING_BUCKET_COUNT = 192;
		using GlobalStringTable = FixedStringTable<STRING_MAP_COUNT, STRING_BUCKET_COUNT>;

		static GlobalStringTable* pManager = nullptr;

		static void Init() {
#ifdef GAME
			char* pMemManager = reinterpret_cast<char*>(0x11F6238);
#else
			char* pMemManager = reinterpret_cast<char*>(0xF21B5C);
#endif
			MEMORY_CONTEXT(MC_STATIC_VARS);
			bool bOrgVal = pMemManager[129];
			pMemManager[129] = false;
			pManager = new GlobalStringTable();
			pMemManager[129] = bOrgVal;
		}
	}

	namespace Hooks {
		static const char* __cdecl GetFixedString(const char* apString) noexcept {
			return Data::pManager->GetString(apString);
		}

		static void __cdecl FreeUnusedFixedStrings() noexcept {
			Data::pManager->RequestStringCleanup();
		}

		static void Init() {

#ifdef GAME
			HookUtils::SafeWrite8(0xA5B630, 0xC3);
			HookUtils::WriteRelJump(0xA5B690, Hooks::GetFixedString);
			HookUtils::WriteRelJump(0xA5B460, Hooks::FreeUnusedFixedStrings);
#else
			HookUtils::SafeWrite8(0x81B060, 0xC3);
			HookUtils::WriteRelJump(0x81B0C0, Hooks::GetFixedString);
			HookUtils::WriteRelJump(0x81AF10, Hooks::FreeUnusedFixedStrings);
#endif

			if (JIPUtils::IsValid()) {
				HookUtils::PatchMemoryNopRange(JIPUtils::GetAddress(0x10012260), JIPUtils::GetAddress(0x1001228D));
				HookUtils::WriteRelJump(JIPUtils::GetAddress(0x1000CE20), Hooks::GetFixedString);
			}
		}
	}

	void Init() {
		Data::Init();
		Hooks::Init();
	}

}

#pragma warning(default: 4200)
STACK_FRAME_OPT_RESET

#undef SCOPED_TIMER