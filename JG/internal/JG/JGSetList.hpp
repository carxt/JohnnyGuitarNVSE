#pragma once 

#include <unordered_set>
template <class T>
struct JGSetList {
	bool isWhiteList = false;
	std::unordered_set<T> set;
	void dFlush() {
		isWhiteList = false;
		set.clear();
	};
	bool Allow(T obj) {
		return bool(set.count(obj)) == isWhiteList;
	}
	void Add(T obj) {
		set.insert(obj);
	}
	void Remove(T obj) {
		set.erase(obj);
	}
};