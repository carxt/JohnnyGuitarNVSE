#pragma once

template<class T, uintptr_t address, uint32_t array = 0>
class AddressPtr {
public:
	friend T;
	constexpr AddressPtr() {};

#pragma region "Accessors"
	constexpr inline T& Get() const {
		return *reinterpret_cast<T*>(address);
	}

	template <typename U>
	constexpr inline U& ReadAs() const {
		return *reinterpret_cast<U*>(address);
	}

	// If T has a operator->, pass through
	constexpr inline auto operator->() const
		requires requires(T a) { a.operator->(); } {
		return Get().operator->();
	}

	// If T doesn't have a operator-> and is not a pointer, return T*
	constexpr inline T* operator->() const
		requires (!requires(T a) { a.operator->(); } && !std::is_pointer<T>::value) {
		return reinterpret_cast<T*>(address);
	}

	// If T doesn't have a operator-> and is a pointer, return the dereferenced pointer
	constexpr inline T operator->() const
		requires (!requires(T a) { a.operator->(); } && std::is_pointer<T>::value) {
		return *reinterpret_cast<T*>(address);
	}

	constexpr inline operator T() const 
		requires (std::is_pointer<T>::value || std::is_fundamental<T>::value) {
		return Get();
	}

	constexpr inline operator T& () const
		requires (!std::is_fundamental<T>::value && !std::is_pointer<T>::value) {
		return Get();
	}

	constexpr inline T* operator&() const {
		return reinterpret_cast<T*>(address);
	}

	constexpr inline T operator[](const int32_t index) const
		requires (array > 0 && std::is_pointer<T>::value) {
		return reinterpret_cast<T*>(address)[index];
	}

	constexpr inline T& operator[](const int32_t index) const
		requires (array > 0 && !std::is_pointer<T>::value) {
		return reinterpret_cast<T*>(address)[index];
	}

	// If T has a bool operator, provide it
	constexpr inline operator bool() const
		requires requires(T a) { static_cast<bool>(a); } && (!std::is_fundamental<T>::value)  {
		return static_cast<bool>(Get());
	}
	
	// If T has a U operator, and U is not a fundamental type, provide it, unless U is copy constructible
	template <typename U>
	constexpr inline operator U() const
		requires requires(T a) { static_cast<U>(a); } && (!std::is_fundamental<T>::value && !std::is_pointer<T>::value && (std::is_pointer<U>::value || !std::is_copy_constructible<U>::value)) {
		return static_cast<U>(Get());
	}

#pragma endregion

#pragma region "Modify operators"
	constexpr inline void operator=(const T& other) const
		requires requires(T a, T b) { a = b; } {
		Get() = other;
	}

	template <typename U>
	constexpr inline void operator=(const U other) const
		requires requires(T a, U b) { a = b; } {
		Get() = other;
	}

	template <typename U>
	constexpr inline void operator+=(const U& other) const
		requires requires(T a, U b) { a += b; } {
		Get() += other;
	}

	template <typename U>
	constexpr inline void operator-=(const U& other) const
		requires requires(T a, U b) { a - +b; } {
		Get() -= other;
	}

	template <typename U>
	constexpr inline void operator*=(const U& other) const
		requires requires(T a, U b) { a *= b; } {
		Get() *= other;
	}

	template <typename U>
	constexpr inline void operator/=(const U& other) const
		requires requires(T a, U b) { a /= b; } {
		Get() /= other;
	}

	constexpr inline T operator++(int) const
		requires requires(T a) { a++; } {
		T temp = Get();
		Get()++;
		return temp;
	}

	constexpr inline T& operator++() const
		requires requires(T a) { ++a; } {
		return ++Get();
	}

	constexpr inline T operator--(int) const
		requires requires(T a) { a--; } {
		T temp = Get();
		Get()--;
		return temp;
	}


	constexpr inline T& operator--() const
		requires requires(T a) { --a; } {
		return --Get();
	}
#pragma endregion

#pragma region "Math operators"
#if 0
	template <typename U>
	constexpr inline T operator+(const U& other) const
		requires requires(T a, U b) { a + b; } {
		return Get() + other;
	}

	template <typename U>
	constexpr inline T operator-(const U& other) const
		requires requires(T a, U b) { a - b; } {
		return Get() - other;
	}

	template <typename U>
	constexpr inline T operator*(const U& other) const
		requires requires(T a, U b) { a* b; } {
		return Get() * other;
	}

	template <typename U>
	constexpr inline T operator/(const U& other) const
		requires requires(T a, U b) { a / b; } {
		return Get() / other;
	}
#endif
#pragma endregion

#pragma region "Comparison operators"
	template <typename U>
		requires requires(T a, U b) { a == b; }
	constexpr inline bool operator==(const U& other) const {
		return Get() == other;
	}

	template <typename U>
		requires requires(T a, U b) { a != b; }
	constexpr inline bool operator!=(const U& other) const {
		return Get() != other;
	}

	template <typename U>
		requires requires(T a, U b) { a < b; }
	constexpr inline bool operator<(const U& other) const {
		return Get() < other;
	}

	template <typename U>
		requires requires(T a, U b) { a <= b; }
	constexpr inline bool operator<=(const U& other) const {
		return Get() <= other;
	}

	template <typename U>
		requires requires(T a, U b) { a > b; }
	constexpr inline bool operator>(const U& other) const {
		return Get() > other;
	}

	template <typename U>
		requires requires(T a, U b) { a >= b; }
	constexpr inline bool operator>=(const U& other) const {
		return Get() >= other;
	}
#pragma endregion
};