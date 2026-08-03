#pragma once

#include "BSSpinLock.hpp"
#include "InterfacedClass.hpp"
#include "ThreadSpecificInterfaceManager.hpp"

template<typename K, typename T>
class LockFreeMap : public InterfacedClass {
public:
	LockFreeMap(uint32_t auiMaxThreads, uint32_t auiBucketCount, uint32_t auiDeleteBatchSize);
	~LockFreeMap() override;

	virtual bool		GetAt(K aKey, T& arData);
	virtual bool		SetAt(uint32_t auiBucket, K aKey, const T& arData, bool abReplaceExisting);
	virtual bool		SetAtAlt(K aKey, const T& arData, bool abReplaceExisting);
	virtual bool		RemoveAt(K aKey);
	virtual bool		Remove(uint32_t auiBucket, T aData);
	virtual bool		RemoveAlt(T aData);
	virtual bool		GetAtAlt(K aKey, T& arData); // Same as GetAt, but no lock
	virtual uint32_t	GetBucketForKey(K aKey);
	virtual void		DeleteKey(K aKey);
	virtual K			CopyKey(K aKey);
	virtual void		CopyKeyDirect(K aKey, K& arCopiedKey);
	virtual bool		IsKeyGreaterOrEqual(K aKey1, K aKey2) const;
	virtual bool		IsKeyEqual(K aKey1, K aKey2) const;
	virtual void		IncrementCount();
	virtual void		DecrementCount();
	virtual uint32_t	GetCount() const;

	void* AllocateInterface(uint32_t auiThread) override;

	template<typename PTR>
	struct MarkedPointer {
		static constexpr uint32_t POINTER_MARK_FLAG	= 1u;
		static constexpr uint32_t POINTER_MASK		= ~1u;

		MarkedPointer();
		MarkedPointer(bool abMark, PTR* apValue);

		volatile PTR* pPointer = nullptr;

		bool GetMark() const;
		void SetMark(bool abMark);

		void Clear();
	
		PTR* GetPointer() const;

		PTR* operator->() const;

		operator int();
	};

	struct HashListNode {
		HashListNode(K aKey, const T& arData);
		~HashListNode();

		K							tKey;
		T							tData;
		MarkedPointer<HashListNode>	pNext;

		bool GetMark() const;

		HashListNode* GetNextDelete();
		void SetNextDelete(HashListNode* apNext);
	};

	class LockFreeMapInterface {
	public:
		LockFreeMapInterface(class LockFreeMap* apOwner, HashListNode** apNode0, HashListNode** apNode1, HashListNode** apNode2);
		~LockFreeMapInterface();

		LockFreeMap*							pOwner				= nullptr;
		HashListNode**							pReferencedNodes[3] = {};
		MarkedPointer<HashListNode>*			pPrev				= nullptr;
		MarkedPointer<HashListNode>				kCurrent;
		MarkedPointer<HashListNode>				kNext;
		HashListNode*							pDeleteHead			= nullptr;
		uint32_t								uiDeleteCount		= 0;

		bool GetAt(K aKey, T& arData);
		bool GetAt(uint32_t auiBucket, K aKey, T& arData);

		bool SetAt(K aKey, const T& arData, bool abReplaceExisting);
		bool SetAt(uint32_t auiBucket, K aKey, const T& arData, bool abReplaceExisting);

		bool RemoveAt(K aKey);
		bool RemoveAt(uint32_t auiBucket, K aKey);

		bool Remove(uint32_t auiBucket, T& arData);

		bool GetFirst(uint32_t auiBucket, K& arKey, T& arData);
		bool GetNext(uint32_t auiBucket, K& arKey, T& arData);

		bool Find(uint32_t auiBucket, K aKey);
		bool FindValue(uint32_t auiBucket, T& arData);

		void DeleteNode(HashListNode* apNode);
		void ClearReferencedNodes();

		void ScanForDeletedNodes();
	};
	typedef ThreadSpecificInterfaceManager<LockFreeMapInterface> Manager;

	class LockFreeMapIterator {
	public:
		LockFreeMapIterator();
		virtual ~LockFreeMapIterator();
		virtual void ClearKey();

		struct ALIGN1 _State {
			enum Flags : uint8_t {
				STARTED_BUCKET	= 1 << 0,
				FINISHED		= 1 << 1,
			};

			bool bStartedBucket : 1;
			bool bFinished		: 1;
		};
		using State = _State::Flags;

		alignas(alignof(K)) uint32_t	uiBucket;
		K								tLastKey;
		Bitfield<_State>				ucFlags;

		void SetStartedBucket(bool abVal);
		bool GetStartedBucket() const { return ucFlags.bStartedBucket; };

		void SetFinished(bool abVal);
		bool GetFinished() const;

		void SetBucket(uint32_t auiBucket);

		void Reset();
	};

	HashListNode**					pReferencedNodes;
	uint32_t						uiNumBuckets;
	MarkedPointer<HashListNode>*	pBuckets;
	uint32_t						uiDeleteBatchSize;
	Manager*						pManager;
	uint32_t						uiCount;
	uint32_t						unk01C;
	mutable BSSpinLock				kLock;

	LockFreeMapInterface* GetInterface();

	uint32_t GetMaxThreads() const;

	uint32_t GetNumBuckets() const;

	uint32_t GetDeleteBatchSize() const;

	MarkedPointer<HashListNode>* GetBucket(uint32_t auiBucket);

	bool GetNext(LockFreeMapIterator& arIter, K& arKey, T& arData, bool abSwitchBuckets);
	bool GetNextAndRemove(LockFreeMapIterator& arIter, K& arKey, T& arData, bool abSwitchBuckets);

	void RemoveAll(bool abCalledByDestructor);

	void ScanForDeletedNodes();
	void DeleteNode(HashListNode* apNode);

	void Lock() const { kLock.Lock(); };
	bool TryLock() const { return kLock.TryLock(); };
	void Unlock() const { kLock.Unlock(); };
};

#include "LockFreeMap.inl"