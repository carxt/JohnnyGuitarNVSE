#pragma once

#include "Utilities.h"
#include "NiTypes.h"
#include "internal/utility.h"
#include "internal/Game/Bethesda/BSSimpleList.hpp"
#include "internal/Game/Bethesda/BSStringT.hpp"

enum {
	eListInvalid = -1,
	eListEnd = -2,
	eListCount = -3,
};

typedef void* (*_FormHeap_Allocate)(uint32_t size);
extern const _FormHeap_Allocate FormHeap_Allocate;

typedef void (*_FormHeap_Free)(void* ptr);
extern const _FormHeap_Free FormHeap_Free;

typedef TESForm* (*_LookupFormByID)(uint32_t id);
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

template <typename T_Data>
class BSSimpleArray {
public:

	virtual			~BSSimpleArray();
	virtual T_Data* Allocate(uint32_t auiCount);
	virtual void    Deallocate(T_Data* apData);
	virtual T_Data* Reallocate(T_Data* apData, uint32_t auiCount);

	T_Data* pBuffer;
	uint32_t	uiSize;
	uint32_t	uiAllocSize;

	

	uint32_t GetSize() { return uiSize; }
	uint32_t GetAllocSize() { return uiAllocSize; }
	bool IsEmpty() { return uiSize == 0; }
	bool IsFull() { return uiSize == uiAllocSize; }
	T_Data* GetAt(uint32_t idx) { return &pBuffer[idx]; }
	T_Data* GetLast() { return &pBuffer[uiSize - 1]; }

	
};

static_assert(sizeof(BSSimpleArray<uint32_t>)	== 0x10);

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

#define DECL_FLOAT_OP(op) \
	NiPoint3 operator op(const float n) const \
	{ \
		return NiPoint3(x op n, y op n, z op n); \
	} \
	NiPoint3 operator op##=(const float n) \
	{ \
		return *this = NiPoint3(x op n, y op n, z op n); \
	} \

#define DECL_VEC_OP(op) \
	NiPoint3 operator op(const NiPoint3 v) const \
	{ \
		return NiPoint3(x op v.x, y op v.y, z op v.z); \
	} \
	NiPoint3 operator op##=(const NiPoint3 v) \
	{ \
		return *this = NiPoint3(x op v.x, y op v.y, z op v.z); \
	}

struct NiPoint3 {
	float x, y, z;

	void Scale(float scale) {
		x *= scale;
		y *= scale;
		z *= scale;
	};

	void Init(NiPoint3* point) {
		x = point->x;
		y = point->y;
		z = point->z;
	};

	NiPoint3() : x(0.f), y(0.f), z(0.f) {};

	NiPoint3(const float x, const float y, const float z) : x(x), y(y), z(z) {};

	DECL_FLOAT_OP(*);
	DECL_FLOAT_OP(/ );

	DECL_VEC_OP(+);
	DECL_VEC_OP(-);
	DECL_VEC_OP(*);
	DECL_VEC_OP(/ );

	float length() const {
		return sqrtf(x * x + y * y + z * z);
	}

	float length_sqr() const {
		return x * x + y * y + z * z;
	}

	NiPoint3 normal() const {
		const auto len = length();
		return len == 0.F ? NiPoint3() : NiPoint3(x / len, y / len, z / len);
	}

	static float dot(const NiPoint3& v1, const NiPoint3& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
	inline float Distance(const NiPoint3& pt) const {
		return (*this - pt).length();
	}

	static NiPoint3 cross(const NiPoint3& v1, const NiPoint3& v2) {
		return NiPoint3(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x);
	}

	NiPoint3* Add(NiPoint3* toAdd) {
		this->x += toAdd->x;
		this->y += toAdd->y;
		this->z += toAdd->z;
		return this;
	}

	NiPoint3* Subtract(NiPoint3* point) {
		this->x -= point->x;
		this->y -= point->y;
		this->z -= point->z;
		return this;
	}

	float CalculateDistSquared(NiPoint3* to) {
		float deltaX = (x - to->x);
		float deltaY = (y - to->y);
		float deltaZ = (z - to->z);

		return deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;
	}
	static float Sign(NiPoint3 p1, NiPoint3 p2, NiPoint3 p3) {
		return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
	}

	static bool PointInTriangle(NiPoint3 pt, NiPoint3 v1, NiPoint3 v2, NiPoint3 v3) {
		bool b1 = Sign(pt, v1, v2) < 0.0;
		bool b2 = Sign(pt, v2, v3) < 0.0;
		bool b3 = Sign(pt, v3, v1) < 0.0;

		return (b1 == b2) && (b2 == b3);
	}

	static NiPoint3 GetTriangleCenter(NiPoint3 v1, NiPoint3 v2, NiPoint3 v3) {
		return NiPoint3((v1.x + v2.x + v3.x) / 3.0f, (v1.y + v2.y + v3.y) / 3.0f, (v1.z + v2.z + v3.z) / 3.0f);
	}

};