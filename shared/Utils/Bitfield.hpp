#pragma once
#include <cstdint>
#include <type_traits>
#include <bit>

#if defined(_MSC_VER)
#include <intrin.h>
#else
inline bool _bittest(const long* base, long bit) { return (*base & (1L << bit)) != 0; }
inline bool _bittestandset(long* base, long bit) { bool b = _bittest(base, bit); *base |= (1L << bit); return b; }
inline bool _bittestandreset(long* base, long bit) { bool b = _bittest(base, bit); *base &= ~(1L << bit); return b; }
#endif

// I'm insane
// (Bitfields compile better than bitmasks)
// (Would be hilarious if I'm wrong)
namespace _BitfieldInternal {

#pragma region TemplateHelpers

	template <typename T>
	struct BitfieldWrapper {
	private:
		T tField;
	};

	template<typename T>
	concept HasInstructions = (sizeof(T) == 2 || sizeof(T) == 4);

	template<typename T>
	constexpr bool HasInstructions_v = HasInstructions<T>;

	template <typename T, T VALUE>
	concept SingleBit = std::has_single_bit(VALUE);

	template<typename T, T FLAG>
		requires SingleBit<T, FLAG>
	consteval uint32_t GetBitNumber() {
		return std::countr_zero(FLAG);
	}
	
	template<uint32_t N> struct PaddingBytes    { uint8_t _pad[N]; };
	template<>           struct PaddingBytes<0> {};
	
	template<uint32_t ALIGN, uint32_t BYTE_OFFSET, uint32_t BIT_OFFSET>
	struct alignas(ALIGN) BitGetterImpl : PaddingBytes<BYTE_OFFSET> {
		static_assert(BIT_OFFSET > 0 && BIT_OFFSET < 8);
		uint8_t        : BIT_OFFSET;
		uint8_t bValue : 1;
	};
	
	template<uint32_t ALIGN, uint32_t BYTE_OFFSET>
	struct alignas(ALIGN) BitGetterImpl<ALIGN, BYTE_OFFSET, 0> : PaddingBytes<BYTE_OFFSET> {
		uint8_t bValue : 1;
	};
	
	template<uint32_t ALIGN, uint32_t BIT_POS>
	using BitGetterAt = BitGetterImpl<ALIGN, BIT_POS / 8, BIT_POS % 8>;
	
	template<typename TYPE, TYPE FLAG>
	concept ValidFlag = std::has_single_bit(FLAG) && (GetBitNumber<TYPE, FLAG>() < sizeof(TYPE) * 8);
	
	template<typename TYPE, uint32_t BIT>
	concept ValidBitIndex = (BIT < sizeof(TYPE) * 8);
	
	template<typename TYPE, TYPE FLAG>
		requires ValidFlag<TYPE, FLAG>
	using BitGetterForFlag = BitGetterAt<sizeof(TYPE), GetBitNumber<TYPE, FLAG>()>;
	
	template<typename TYPE, uint32_t BIT>
		requires ValidBitIndex<TYPE, BIT>
	using BitGetterForIndex = BitGetterAt<sizeof(TYPE), BIT>;

#pragma endregion

	template <typename TYPE, typename STRUCT>
	class BitfieldBase : public std::conditional_t<std::is_integral_v<STRUCT>, BitfieldWrapper<STRUCT>, STRUCT> {
	public:
		constexpr TYPE& GetField() noexcept { return reinterpret_cast<TYPE&>(*this); }

		constexpr const TYPE& GetField() const noexcept { return reinterpret_cast<const TYPE&>(*this); }

		constexpr BitfieldBase() noexcept { Clear(); }
		constexpr BitfieldBase(TYPE data) noexcept { Write(data); }

		constexpr void __fastcall Write(TYPE data) noexcept { GetField() = data; }

		constexpr void __fastcall Clear() noexcept { Write(0); }
		constexpr void __fastcall Clear(TYPE data) noexcept { GetField() &= ~data; }

		constexpr void __fastcall Mask(TYPE data) noexcept { GetField() &= data; }
		constexpr void __fastcall Toggle(TYPE data) noexcept { GetField() ^= data; }

		constexpr void __fastcall Set(TYPE data) noexcept { GetField() |= data; }
		constexpr void __fastcall Set(TYPE data, bool state) noexcept { state ? Set(data) : Clear(data); }
		constexpr void __fastcall Set(TYPE data, TYPE mask, TYPE pos) noexcept { GetField() = (GetField() & ~mask) | (data << pos); }

		constexpr TYPE __fastcall Get() const noexcept { return GetField(); }
		constexpr TYPE __fastcall Get(TYPE data) const noexcept { return GetField() & data; }
		constexpr TYPE __fastcall Get(TYPE mask, TYPE pos) const noexcept { return (GetField() & mask) >> pos; }

		constexpr void __fastcall SetBit(uint32_t bit) noexcept { GetField() |= TYPE(1) << bit; }

		constexpr void __fastcall ClearBit(uint32_t bit) noexcept { GetField() &= ~(TYPE(1) << bit); }

		constexpr void __fastcall SetBit(uint32_t bit, bool state) noexcept { state ? SetBit(bit) : ClearBit(bit); }

		constexpr bool __fastcall GetBit(uint32_t bit) const noexcept {
			if constexpr (HasInstructions_v<TYPE>)
				return _bittest(reinterpret_cast<const long*>(this), bit);
			else
				return (GetField() & (TYPE(1) << bit)) != 0;
		}

		constexpr bool __fastcall GetAndSetBit(uint32_t bit) noexcept {
			if constexpr (HasInstructions_v<TYPE>) {
				return _bittestandset(reinterpret_cast<long*>(this), bit);
			}
			else {
				const TYPE mask = TYPE(1) << bit;
				const bool bVal = (GetField() & mask) != 0;
				GetField() |= mask;
				return bVal;
			}
		}

		constexpr bool __fastcall GetAndClearBit(uint32_t bit) noexcept {
			if constexpr (HasInstructions_v<TYPE>) {
				return _bittestandreset(reinterpret_cast<long*>(this), bit);
			}
			else {
				const TYPE mask = TYPE(1) << bit;
				const bool bVal = (GetField() & mask) != 0;
				GetField() &= ~mask;
				return bVal;
			}
		}

		constexpr bool __fastcall IsSet(TYPE data) const noexcept { return Get(data) != 0u; }
		constexpr bool __fastcall IsClear(TYPE data) const noexcept { return Get(data) == 0u; }

		constexpr TYPE __fastcall RotL(uint32_t amount) noexcept { return std::rotl(GetField(), amount); }

		constexpr TYPE __fastcall RotR(uint32_t amount) noexcept { return std::rotr(GetField(), amount); }

		constexpr uint32_t __fastcall PopCount() const noexcept { return std::popcount(GetField()); }

		constexpr operator TYPE& () noexcept { return GetField(); }
		constexpr operator const TYPE& () const noexcept { return GetField(); }

		constexpr void operator=(TYPE data) noexcept { GetField() = data; }
		constexpr void operator|=(TYPE data) noexcept { Set(data); }
		constexpr void operator&=(TYPE data) noexcept { Mask(data); }
		constexpr void operator^=(TYPE data) noexcept { Toggle(data); }

#pragma region CastTemplates

		template<typename T>
		T& As()
			requires (sizeof(T) <= sizeof(TYPE)) {
			return *reinterpret_cast<T*>(this);
		}

		template<typename T>
		const T& As() const
			requires (sizeof(T) <= sizeof(TYPE)) {
			return *reinterpret_cast<const T*>(this);
		}

#pragma endregion

#pragma region BitTemplates

		template<const uint32_t BIT>
			requires ValidBitIndex<TYPE, BIT>
		constexpr bool GetBit() const noexcept {
			if constexpr (HasInstructions_v<TYPE>)
				return _bittest(reinterpret_cast<const long*>(this), BIT);
			else
				return As<BitGetterForIndex<TYPE, BIT>>().bValue;
		}

		template<const uint32_t BIT>
			requires ValidBitIndex<TYPE, BIT>
		constexpr void SetBit() noexcept {
			As<BitGetterForIndex<TYPE, BIT>>().bValue = true;
		}

		template<const uint32_t BIT>
			requires ValidBitIndex<TYPE, BIT>
		constexpr void SetBit(bool state) noexcept {
			As<BitGetterForIndex<TYPE, BIT>>().bValue = state;
		}

		template<const uint32_t BIT>
			requires ValidBitIndex<TYPE, BIT>
		constexpr void ClearBit() noexcept {
			As<BitGetterForIndex<TYPE, BIT>>().bValue = false;
		}

		template<const uint32_t BIT>
			requires ValidBitIndex<TYPE, BIT>
		constexpr bool GetAndSetBit() noexcept {
			if constexpr (HasInstructions_v<TYPE>())
				return _bittestandset(reinterpret_cast<long*>(this), BIT);
			else {
				const bool bVal = As<BitGetterForIndex<TYPE, BIT>>().bValue;
				As<BitGetterForIndex<TYPE, BIT>>().bValue = true;
				return bVal;
			}
		}

		template <const uint32_t BIT>
			requires ValidBitIndex<TYPE, BIT>
		constexpr bool GetAndClearBit() noexcept {
			if constexpr (HasInstructions_v<TYPE>())
				return _bittestandreset(reinterpret_cast<long*>(this), BIT);
			else {
				const bool bVal = As<BitGetterForIndex<TYPE, BIT>>().bValue;
				As<BitGetterForIndex<TYPE, BIT>>().bValue = false;
				return bVal;
			}
		}

#pragma endregion

#pragma region FlagTemplates

		template<const TYPE FLAG>
			requires ValidFlag<TYPE, FLAG>
		constexpr bool Get() const noexcept {
			return As<BitGetterForFlag<TYPE, FLAG>>().bValue;
		}

		template<const TYPE FLAG>
			requires ValidFlag<TYPE, FLAG>
		constexpr void Set() noexcept {
			As<BitGetterForFlag<TYPE, FLAG>>().bValue = true;
		}

		template<const TYPE FLAG>
			requires ValidFlag<TYPE, FLAG>
		constexpr void Set(bool state) noexcept {
			As<BitGetterForFlag<TYPE, FLAG>>().bValue = state;
		}

		template<const TYPE FLAG>
			requires ValidFlag<TYPE, FLAG>
		constexpr void Clear() noexcept {
			As<BitGetterForFlag<TYPE, FLAG>>().bValue = false;
		}

		template<const TYPE FLAG>
			requires ValidFlag<TYPE, FLAG>
		constexpr bool IsSet() const noexcept {
			return GetBit<GetBitNumber<TYPE, FLAG>()>();
		}

		template<const TYPE FLAG>
			requires ValidFlag<TYPE, FLAG>
		constexpr bool IsClear() const noexcept {
			return !GetBit<GetBitNumber<TYPE, FLAG>()>();
		}

		template<const TYPE FLAG>
			requires ValidFlag<TYPE, FLAG>
		constexpr bool GetAndSet() noexcept {
			return GetAndSetBit<GetBitNumber<TYPE, FLAG>()>();
		}

		template<const TYPE FLAG>
			requires ValidFlag<TYPE, FLAG>
		constexpr bool GetAndClear() noexcept {
			return GetAndClearBit<GetBitNumber<TYPE, FLAG>()>();
		}

#pragma endregion
	};
}

template <typename STRUCT>
using Bitfield = _BitfieldInternal::BitfieldBase<
	std::conditional_t<
	sizeof(STRUCT) == 1, uint8_t,
	std::conditional_t<
	sizeof(STRUCT) == 2, uint16_t,
	std::conditional_t<sizeof(STRUCT) == 4, uint32_t, void>
	>
	>,
	STRUCT
>;

using Bitfield8  = Bitfield<uint8_t>;
using Bitfield16 = Bitfield<uint16_t>;
using Bitfield32 = Bitfield<uint32_t>;