#pragma once 

#include <unordered_set>

template <class T>
struct JGSetList {

	bool bIsWhiteList = false;
	std::unordered_set<T> kSet;

	bool __fastcall Find(const T& obj) const {
		return bool(kSet.count(obj)) == bIsWhiteList;
	}

	void __fastcall Add(const T& obj) {
		kSet.insert(obj);
	}

	void __fastcall Remove(const T& obj) {
		kSet.erase(obj);
	}

	void __fastcall Flush() {
		bIsWhiteList = false;
		kSet.clear();
	};
};