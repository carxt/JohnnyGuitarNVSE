#pragma once

#include "Utilities.h"
#include "NiTypes.h"
#include "internal/utility.h"

// 8
class BSString {
public:
	BSString();
	~BSString();

	char*	m_data;
	UInt16	m_dataLen;
	UInt16	m_bufLen;

	void Init(UInt32 bufSize);
	bool Set(const char* src);
	bool Append(const char* toAppend);
	void AppendChar(char toAppend);
	void InsertChar(char toInsert, UInt32 index);
	void EraseAt(UInt32 index);
	const char* CStr();
};

enum {
	eListInvalid = -1,
	eListEnd = -2,
	eListCount = -3,
};

typedef void* (*_FormHeap_Allocate)(UInt32 size);
extern const _FormHeap_Allocate FormHeap_Allocate;

typedef void (*_FormHeap_Free)(void* ptr);
extern const _FormHeap_Free FormHeap_Free;

typedef TESForm* (*_LookupFormByID)(UInt32 id);
extern const _LookupFormByID LookupFormByID;

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
			GameHeapFree(pNext);
			return this;
		}
		data = NULL;
		return NULL;
	}

	ListNode* RemoveNext() {
		ListNode* pNext = next;
		next = next->next;
		GameHeapFree(pNext);
		return next;
	}

	ListNode* Append(T_Data* _data) {
		ListNode* newNode = (ListNode*)GameHeapAlloc(sizeof(ListNode));
		newNode->data = _data;
		newNode->next = next;
		next = newNode;
		return newNode;
	}

	ListNode* Insert(T_Data* _data) {
		ListNode* newNode = (ListNode*)GameHeapAlloc(sizeof(ListNode));
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
	UInt32 FreeNodes(Node* node, Op& compareOp) const {
		static UInt32 nodeCount = 0, numFreed = 0, lastNumFreed = 0;
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

	Node* GetLastNode(SInt32* outIdx = NULL) const {
		SInt32 index = 0;
		Node* node = Head();
		while (node->next) {
			node = node->next;
			index++;
		}
		if (outIdx) *outIdx = index;
		return node;
	}

	Node* GetNthNode(SInt32 index) const {
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

	UInt32 Count() const {
		if (!m_listHead.data) return 0;
		Node* node = Head();
		UInt32 count = 1;
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

	Item* GetNthItem(SInt32 index) const {
		if (eListEnd == index)
			return GetLastNode()->data;
		Node* node = GetNthNode(index);
		return node ? node->data : NULL;
	}

	SInt32 AddAt(Item* item, SInt32 index) {
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

	SInt32 Append(Item* item) {
		SInt32 index = eListInvalid;
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
	void Visit(Op& op, Node* prev = NULL) const {
		Node* curr = prev ? prev->next : Head();
		while (curr) {
			if (!curr->data || !op.Accept(curr->data)) break;
			curr = curr->next;
		}
	}

	template <class Op>
	Item* Find(Op& op) const {
		Node* curr = Head();
		Item* pItem;
		do {
			pItem = curr->data;
			if (pItem && op.Accept(pItem)) return pItem;
			curr = curr->next;
		} while (curr);
		return NULL;
	}

	template <class Op>
	Iterator Find(Op& op, Iterator& prev) const {
		Iterator curIt = prev.End() ? Begin() : ++prev;
		while (!curIt.End()) {
			if (*curIt && op.Accept(*curIt)) break;
			++curIt;
		}
		return curIt;
	}

	const Node* FindString(char* str, Iterator prev) const {
		return Find(StringFinder_CI(str), prev);
	}

	template <class Op>
	UInt32 CountIf(Op& op) const {
		UInt32 count = 0;
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
			GameHeapFree(currNode);
			currNode = nextNode;
		}
	}

	void DeleteAll() const {
		Node* nextNode = Head(), * currNode = nextNode->next;
		GameHeapFree(nextNode->data);
		nextNode->data = NULL;
		nextNode->next = NULL;
		while (currNode) {
			nextNode = currNode->next;
			GameHeapFree(currNode->data);
			GameHeapFree(currNode);
			currNode = nextNode;
		}
	}

	Item* RemoveNth(SInt32 idx) {
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

	UInt32 Remove(Item* item) {
		UInt32 removed = 0;
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

	Item* ReplaceNth(SInt32 index, Item* item) {
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

	UInt32 Replace(Item* item, Item* replace) {
		UInt32 replaced = 0;
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
	UInt32 RemoveIf(Op& op) {
		return FreeNodes(Head(), op);
	}

	SInt32 GetIndexOf(Item* item) {
		SInt32 idx = 0;
		Node* curr = Head();
		do {
			if (curr->data == item) return idx;
			idx++;
			curr = curr->next;
		} while (curr);
		return -1;
	}

	template <class Op>
	SInt32 GetIndexOf(Op& op) {
		SInt32 idx = 0;
		Node* curr = Head();
		do {
			if (curr->data && op.Accept(curr->data)) return idx;
			idx++;
			curr = curr->next;
		} while (curr);
		return -1;
	}
};
STATIC_ASSERT(sizeof(tList<void*>) == 0x8);

template <typename T_Data> struct DListNode {
	DListNode* next;
	DListNode* prev;
	T_Data* data;

	DListNode* Advance(UInt32 times) {
		DListNode* result = this;
		while (result && times) {
			times--;
			result = result->next;
		}
		return result;
	}

	DListNode* Regress(UInt32 times) {
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
	UInt32		count;

public:
	bool Empty() const { return !first; }
	Node* Head() { return first; }
	Node* Tail() { return last; }
	UInt32 Size() const { return count; }
};
class Tile;
// 010
template <class T> class BSSimpleList {
public:
	BSSimpleList<T>();
	~BSSimpleList<T>();

	virtual bool	SetSelectedTile(Tile* tile) { return false; };
	virtual Tile* GetSelectedTile(void) { return nullptr; };
	virtual Tile* HandleKeyboardInput(int code) { return nullptr; };
	virtual bool	IsMenuEqual(void* that) { return false; };
	virtual void	ScrollToHighlight(void) {};
	virtual Tile* GetTileByIndex(int index, char isNotTileListIndex) { return nullptr; };
	virtual void	Destructor(bool doFree) {};
	virtual void	FreeAllTiles(void) {};
	virtual void	Sort(signed int(__cdecl*)(T*, T*)) {};

	tList<T>	list;
};
STATIC_ASSERT(sizeof(BSSimpleList<void*>) == 0xC);

template <typename T_Data>
class BSSimpleArray {
public:

	virtual			~BSSimpleArray();
	virtual T_Data* Allocate(UInt32 auiCount);
	virtual void    Deallocate(T_Data* apData);
	virtual T_Data* Reallocate(T_Data* apData, UInt32 auiCount);

	T_Data* pBuffer;
	UInt32	uiSize;
	UInt32	uiAllocSize;

	

	UInt32 GetSize() { return uiSize; }
	UInt32 GetAllocSize() { return uiAllocSize; }
	bool IsEmpty() { return uiSize == 0; }
	bool IsFull() { return uiSize == uiAllocSize; }
	T_Data* GetAt(UInt32 idx) { return &pBuffer[idx]; }
	T_Data* GetLast() { return &pBuffer[uiSize - 1]; }

	
};

STATIC_ASSERT(sizeof(BSSimpleArray<UInt32>)	== 0x10);

template <class Node, class Info>
class Visitor {
	const Node* m_pHead;

	template <class Op>
	UInt32 FreeNodes(Node* node, Op& compareOp) const {
		static UInt32 nodeCount = 0;
		static UInt32 numFreed = 0;
		static Node* lastNode = NULL;
		static bool bRemovedNext = false;

		UInt32 returnCount;

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
		bool Accept(Info* info) {
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

	UInt32 Count() const {
		UInt32 count = 0;
		const Node* pCur = m_pHead;
		while (pCur && pCur->Info() != NULL) {
			++count;
			pCur = pCur->Next();
		}
		return count;
	}

	Info* GetNthInfo(UInt32 n) const {
		UInt32 count = 0;
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

	const Node* FindString(char* str, const Node* prev = NULL) const {
		return Find(StringFinder_CI(str), prev);
	}

	template <class Op>
	UInt32 CountIf(Op& op) const {
		UInt32 count = 0;
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
	UInt32 RemoveIf(Op& op) {
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
	UInt32 GetIndexOf(Op& op) {
		UInt32 idx = 0;
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

struct CoordXY {
	float	x;
	float	y;

	CoordXY() {}
	CoordXY(float _x, float _y) : x(_x), y(_y) {}

	inline CoordXY& operator =(const CoordXY& rhs) {
		*(double*)this = *(double*)&rhs;
		return *this;
	}
};