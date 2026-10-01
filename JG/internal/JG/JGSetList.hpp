#pragma once 

#include <unordered_set>

template <class T>
class JGSetList {
public:
	JGSetList(bool abIsWhiteList = false) : bIsWhiteList(abIsWhiteList) {};

	std::unordered_set<T>	kSet;
	bool					bIsWhiteList;

	bool __fastcall Find(const T& obj) const {
		return kSet.contains(obj) == bIsWhiteList;
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