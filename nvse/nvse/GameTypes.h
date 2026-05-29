#pragma once

#include "Utilities.h"
#include "NiTypes.h"
#include "internal/utility.h"
#include "internal/Game/Bethesda/BSSimpleList.hpp"
#include "internal/Game/Bethesda/BSSimpleArray.hpp"
#include "internal/Game/Bethesda/BSStringT.hpp"

enum {
	eListInvalid = -1,
	eListEnd = -2,
	eListCount = -3,
};

template <typename T_Data> struct ListNode {
	T_Data* data;
	ListNode* next;

	ListNode() : data(NULL), next(NULL) {}
	ListNode(T_Data* _data) : data(_data), next(NULL) {}

	T_Data* Data() const { return data; }
	ListNode* Next() const { return next; }

	ListNode* RemoveMe() {
		if (next) {
			ListNode* pNext = next;
			data = next->data;
			next = next->next;
			BSMemory::free(pNext);
			return this;
		}
		data = NULL;
		return NULL;
	}

	ListNode* RemoveNext() {
		ListNode* pNext = next;
		next = next->next;
		BSMemory::free(pNext);
		return next;
	}

	ListNode* Append(T_Data* _data) {
		ListNode* newNode = BSMemory::malloc<ListNode>();
		newNode->data = _data;
		newNode->next = next;
		next = newNode;
		return newNode;
	}

	ListNode* Insert(T_Data* _data) {
		ListNode* newNode = BSMemory::malloc<ListNode>();
		newNode->data = data;
		data = _data;
		newNode->next = next;
		next = newNode;
		return newNode;
	}
};

template <class Item> class tList {
public:
	typedef ListNode<Item> Node;

private:
	Node	m_listHead;

	template <class Op>
	uint32_t FreeNodes(Node* node, Op& compareOp) const {
		static uint32_t nodeCount = 0, numFreed = 0, lastNumFreed = 0;
		if (node->next) {
			nodeCount++;
			FreeNodes(node->next, compareOp);
			nodeCount--;
		}
		if (compareOp.Accept(node->data)) {
			node->RemoveMe();
			numFreed++;
		}
		if (!nodeCount) {
			lastNumFreed = numFreed;
			numFreed = 0;
		}
		return lastNumFreed;
	}

	Node* GetLastNode(int32_t* outIdx = NULL) const {
		int32_t index = 0;
		Node* node = Head();
		while (node->next) {
			node = node->next;
			index++;
		}
		if (outIdx) *outIdx = index;
		return node;
	}

	Node* GetNthNode(int32_t index) const {
		if (index >= 0) {
			Node* node = Head();
			do {
				if (!index) return node;
				index--;
			} while (node = node->next);
		}
		return NULL;
	}

public:
	void Init(Item* item = NULL) {
		m_listHead.data = item;
		m_listHead.next = NULL;
	}

	Node* Head() const { return const_cast<Node*>(&m_listHead); }

	bool Empty() const { return !m_listHead.data; }

	class Iterator {
		Node* m_curr;

	public:
		Iterator operator++() {
			if (m_curr) m_curr = m_curr->next;
			return *this;
		}
		bool End() const { return !m_curr || (!m_curr->data && !m_curr->next); }
		Item* operator->() const { return m_curr->data; }
		Item*& operator*() const { return m_curr->data; }
		const Iterator& operator=(const Iterator& rhs) {
			m_curr = rhs.m_curr;
			return *this;
		}
		Item* Get() const { return m_curr->data; }
		void Next() { if (m_curr) m_curr = m_curr->next; }
		void Find(Item* _item) {
			while (m_curr) {
				if (m_curr->data == _item) break;
				m_curr = m_curr->next;
			}
		}

		Iterator(Node* node = NULL) : m_curr(node) {}
		Iterator(tList& _list) : m_curr(&_list.m_listHead) {}
		Iterator(tList* _list) : m_curr(&_list->m_listHead) {}
		Iterator(tList& _list, Item* _item) : m_curr(&_list.m_listHead) { Find(_item); }
		Iterator(tList* _list, Item* _item) : m_curr(&_list->m_listHead) { Find(_item); }
	};

	const Iterator Begin() const { return Iterator(Head()); }

	uint32_t Count() const {
		if (!m_listHead.data) return 0;
		Node* node = Head();
		uint32_t count = 1;
		while (node = node->next) count++;
		return count;
	};

	bool IsInList(Item* item) const {
		Node* node = Head();
		do {
			if (node->data == item) return true;
			node = node->next;
		} while (node);
		return false;
	}

	Item* GetFirstItem() const {
		return m_listHead.data;
	}

	Item* GetLastItem() const {
		return GetLastNode()->data;
	}

	Item* GetNthItem(int32_t index) const {
		if (eListEnd == index)
			return GetLastNode()->data;
		Node* node = GetNthNode(index);
		return node ? node->data : NULL;
	}

	int32_t AddAt(Item* item, int32_t index) {
		if (!item) return eListInvalid;
		Node* node;
		if (!index) {
			if (m_listHead.data) m_listHead.Insert(item);
			else m_listHead.data = item;
		}
		else if (eListEnd == index) {
			node = GetLastNode(&index);
			if (node->data) node->Append(item);
			else node->data = item;
		}
		else {
			node = GetNthNode(index);
			if (!node) return eListInvalid;
			node->Insert(item);
		}
		return index;
	}

	int32_t Append(Item* item) {
		int32_t index = eListInvalid;
		if (item) {
			Node* node = GetLastNode(&index);
			if (node->data) node->Append(item);
			else node->data = item;
		}
		return index;
	}

	void Insert(Item* item) {
		if (item) {
			if (m_listHead.data) m_listHead.Insert(item);
			else m_listHead.data = item;
		}
	}

	void CopyFrom(tList& sourceList) {
		Node* target = Head(), * source = sourceList.Head();
		RemoveAll();
		if (!source->data) return;
		target->data = source->data;
		while (source = source->next)
			target = target->Append(source->data);
	}

	template <class Op>
	void Visit(const Op& op, Node* prev = NULL) const {
		Node* curr = prev ? prev->next : Head();
		while (curr) {
			if (!curr->data || !const_cast<Op&>(op).Accept(curr->data)) break;
			curr = curr->next;
		}
	}

	template <class Op>
	Item* Find(const Op& op) const {
		Node* curr = Head();
		Item* pItem;
		do {
			pItem = curr->data;
			if (pItem && const_cast<Op&>(op).Accept(pItem)) return pItem;
			curr = curr->next;
		} while (curr);
		return NULL;
	}

	template <class Op>
	Iterator Find(const Op& op, Iterator& prev) const {
		Iterator curIt = prev.End() ? Begin() : ++prev;
		while (!curIt.End()) {
			if (*curIt && const_cast<Op&>(op).Accept(*curIt)) break;
			++curIt;
		}
		return curIt;
	}

	template <class Op>
	uint32_t CountIf(Op& op) const {
		uint32_t count = 0;
		Node* curr = Head();
		do {
			if (curr->data && op.Accept(curr->data)) count++;
			curr = curr->next;
		} while (curr);
		return count;
	}

	class AcceptAll {
	public:
		bool Accept(Item* item) { return true; }
	};

	void RemoveAll() const {
		Node* nextNode = Head(), * currNode = nextNode->next;
		nextNode->data = NULL;
		nextNode->next = NULL;
		while (currNode) {
			nextNode = currNode->next;
			BSMemory::free(currNode);
			currNode = nextNode;
		}
	}

	void DeleteAll() const {
		Node* nextNode = Head(), * currNode = nextNode->next;
		BSMemory::free(nextNode->data);
		nextNode->data = NULL;
		nextNode->next = NULL;
		while (currNode) {
			nextNode = currNode->next;
			BSMemory::free(currNode->data);
			BSMemory::free(currNode);
			currNode = nextNode;
		}
	}

	Item* RemoveNth(int32_t idx) {
		Item* removed = NULL;
		if (idx <= 0) {
			removed = m_listHead.data;
			m_listHead.RemoveMe();
		}
		else {
			Node* node = Head();
			while (node->next && --idx)
				node = node->next;
			if (!idx) {
				removed = node->next->data;
				node->RemoveNext();
			}
		}
		return removed;
	};

	uint32_t Remove(Item* item) {
		uint32_t removed = 0;
		Node* curr = Head(), * prev = NULL;
		do {
			if (curr->data == item) {
				curr = prev ? prev->RemoveNext() : curr->RemoveMe();
				removed++;
			}
			else {
				prev = curr;
				curr = curr->next;
			}
		} while (curr);
		return removed;
	}

	Item* ReplaceNth(int32_t index, Item* item) {
		Item* replaced = NULL;
		if (item) {
			Node* node;
			if (eListEnd == index)
				node = GetLastNode();
			else {
				node = GetNthNode(index);
				if (!node) return NULL;
			}
			replaced = node->data;
			node->data = item;
		}
		return replaced;
	}

	uint32_t Replace(Item* item, Item* replace) {
		uint32_t replaced = 0;
		Node* curr = Head();
		do {
			if (curr->data == item) {
				curr->data = replace;
				replaced++;
			}
			curr = curr->next;
		} while (curr);
		return replaced;
	}

	template <class Op>
	uint32_t RemoveIf(Op& op) {
		return FreeNodes(Head(), op);
	}

	int32_t GetIndexOf(Item* item) {
		int32_t idx = 0;
		Node* curr = Head();
		do {
			if (curr->data == item) return idx;
			idx++;
			curr = curr->next;
		} while (curr);
		return -1;
	}

	template <class Op>
	int32_t GetIndexOf(const Op& op) {
		int32_t idx = 0;
		Node* curr = Head();
		do {
			if (curr->data && const_cast<Op&>(op).Accept(curr->data)) return idx;
			idx++;
			curr = curr->next;
		} while (curr);
		return -1;
	}
};
static_assert(sizeof(tList<void*>) == 0x8);

template <typename T_Data> struct DListNode {
	DListNode* next;
	DListNode* prev;
	T_Data* data;

	DListNode* Advance(uint32_t times) {
		DListNode* result = this;
		while (result && times) {
			times--;
			result = result->next;
		}
		return result;
	}

	DListNode* Regress(uint32_t times) {
		DListNode* result = this;
		while (result && times) {
			times--;
			result = result->prev;
		}
		return result;
	}
};

template <class Item> class DList {
public:
	typedef DListNode<Item> Node;

private:
	Node* first;
	Node* last;
	uint32_t		count;

public:
	bool Empty() const { return !first; }
	Node* Head() { return first; }
	Node* Tail() { return last; }
	uint32_t Size() const { return count; }
};
class Tile;

template <class Node, class Info>
class Visitor {
	const Node* m_pHead;

	template <class Op>
	uint32_t FreeNodes(Node* node, Op& compareOp) const {
		static uint32_t nodeCount = 0;
		static uint32_t numFreed = 0;
		static Node* lastNode = NULL;
		static bool bRemovedNext = false;

		uint32_t returnCount;

		if (node->Next()) {
			nodeCount++;
			FreeNodes(node->Next(), compareOp);
			nodeCount--;
		}

		if (compareOp.Accept(node->Info())) {
			if (nodeCount)
				node->Delete();
			else
				node->DeleteHead(lastNode);
			numFreed++;
			bRemovedNext = true;
		}
		else {
			if (bRemovedNext)
				node->SetNext(lastNode);
			bRemovedNext = false;
			lastNode = node;
		}

		returnCount = numFreed;

		if (!nodeCount)	//reset vars after recursing back to head
		{
			numFreed = 0;
			lastNode = NULL;
			bRemovedNext = false;
		}

		return returnCount;
	}

	class AcceptAll {
	public:
		bool Accept(const Info* info) {
			return true;
		}
	};

	class AcceptEqual {
		const Info* m_toMatch;
	public:
		AcceptEqual(const Info* info) : m_toMatch(info) {}
		bool Accept(const Info* info) {
			return info == m_toMatch;
		}
	};

	class AcceptStriCmp {
		const char* m_toMatch;
	public:
		AcceptStriCmp(const char* info) : m_toMatch(info) {}
		bool Accept(const char* info) {
			if (m_toMatch && info)
				return _stricmp(info, m_toMatch) ? false : true;
			return false;
		}
	};
public:
	Visitor(const Node* pHead) : m_pHead(pHead) {}

	uint32_t Count() const {
		uint32_t count = 0;
		const Node* pCur = m_pHead;
		while (pCur && pCur->Info() != NULL) {
			++count;
			pCur = pCur->Next();
		}
		return count;
	}

	Info* GetNthInfo(uint32_t n) const {
		uint32_t count = 0;
		const Node* pCur = m_pHead;
		while (pCur && count < n && pCur->Info() != NULL) {
			++count;
			pCur = pCur->Next();
		}
		return (count == n && pCur) ? pCur->Info() : NULL;
	}

	template <class Op>
	void Visit(Op& op) const {
		const Node* pCur = m_pHead;
		bool bContinue = true;
		while (pCur && pCur->Info() && bContinue) {
			bContinue = op.Accept(pCur->Info());
			if (bContinue) {
				pCur = pCur->Next();
			}
		}
	}

	template <class Op>
	const Node* Find(Op& op, const Node* prev = NULL) const {
		const Node* pCur;
		if (!prev)
			pCur = m_pHead;
		else
			pCur = prev->next;
		bool bFound = false;
		while (pCur && !bFound) {
			if (!pCur->Info())
				pCur = pCur->Next();
			else {
				bFound = op.Accept(pCur->Info());
				if (!bFound)
					pCur = pCur->Next();
			}
		}

		return pCur;
	}

	Node* FindInfo(const Info* toMatch) {
		return Find(AcceptEqual(toMatch));
	}

	template <class Op>
	uint32_t CountIf(Op& op) const {
		uint32_t count = 0;
		const Node* pCur = m_pHead;
		while (pCur) {
			if (pCur->Info() && op.Accept(pCur->Info()))
				count++;
			pCur = pCur->Next();
		}
		return count;
	}

	const Node* GetLastNode() const {
		const Node* pCur = m_pHead;
		while (pCur && pCur->Next())
			pCur = pCur->Next();
		return pCur;
	}

	void RemoveAll() const {
		FreeNodes(const_cast<Node*>(m_pHead), AcceptAll());
	}

	template <class Op>
	uint32_t RemoveIf(Op& op) {
		return FreeNodes(const_cast<Node*>(m_pHead), op);
	}

	bool Remove(const Info* toRemove) {
		return RemoveIf(AcceptEqual(toRemove)) ? true : false;
	}

	bool RemoveString(const char* toRemove) {
		return RemoveIf(AcceptStriCmp(toRemove)) ? true : false;
	}

	void Append(Node* newNode) {
		Node* lastNode = const_cast<Node*>(GetLastNode());
		if (lastNode == m_pHead && !m_pHead->Info())
			lastNode->DeleteHead(newNode);
		else
			lastNode->SetNext(newNode);
	}

	template <class Op>
	uint32_t GetIndexOf(Op& op) {
		uint32_t idx = 0;
		const Node* pCur = m_pHead;
		while (pCur && pCur->Info() && !op.Accept(pCur->Info())) {
			idx++;
			pCur = pCur->Next();
		}

		if (pCur && pCur->Info())
			return idx;
		else
			return -1;
	}
};