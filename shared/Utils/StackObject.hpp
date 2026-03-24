#pragma once

template <class T, uint32_t auiConstructAddr = 0, uint32_t auiDestructAddr = 0>
class StackObject {
private:
	uint8_t data[sizeof(T)];

public:
	template <typename ...Args>
	StackObject(Args ...args) {
		if constexpr (auiConstructAddr)
			((T * (__thiscall*)(const void*, Args...))auiConstructAddr)(GetPtr(), std::forward<Args>(args)...);
		else
			memset(data, 0, sizeof(T));
	}

	~StackObject() {
		if constexpr (auiDestructAddr)
			ThisCall(auiDestructAddr, GetPtr());
		else
			reinterpret_cast<T*>(data)->~T();
	}

	T* operator->() {
		return reinterpret_cast<T*>(data);
	}
	T& operator*() {
		return *reinterpret_cast<T*>(data);
	};

	T& Get() {
		return *reinterpret_cast<T*>(data);
	}

	T* GetPtr() {
		return reinterpret_cast<T*>(data);
	}

	template <typename ...Args>
	T* Create(uint32_t _addr, Args ...args)
	{
		return ((T * (__thiscall*)(const void*, Args...))_addr)(GetPtr(), std::forward<Args>(args)...);
	}
};