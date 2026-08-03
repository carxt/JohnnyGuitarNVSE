#pragma once

#include "LockFreeMap.hpp"
#include "LockFreeQueue.hpp"
#include "BSUtilities.hpp"

#pragma region MarkedPointer

template<typename K, typename T>
template<typename PTR>
inline LockFreeMap<K, T>::MarkedPointer<PTR>::MarkedPointer() {
    pPointer = nullptr;
}

template<typename K, typename T>
template<typename PTR>
inline LockFreeMap<K, T>::MarkedPointer<PTR>::MarkedPointer(bool abMark, PTR* apValue) : pPointer(apValue) { 
    SetMark(abMark); 
}

template<typename K, typename T>
template<typename PTR>
inline bool LockFreeMap<K, T>::MarkedPointer<PTR>::GetMark() const {
    return reinterpret_cast<uint32_t>(pPointer) & POINTER_MARK_FLAG;
}

template<typename K, typename T>
template<typename PTR>
inline void LockFreeMap<K, T>::MarkedPointer<PTR>::SetMark(bool abMark) {
    if (abMark)
        pPointer = reinterpret_cast<PTR*>(reinterpret_cast<size_t>(pPointer) | 1);
    else
        pPointer = reinterpret_cast<PTR*>(reinterpret_cast<size_t>(pPointer) & ~1);
}

template<typename K, typename T>
template<typename PTR>
inline void LockFreeMap<K, T>::MarkedPointer<PTR>::Clear() {
    pPointer = nullptr;
}

template<typename K, typename T>
template<typename PTR>
inline PTR* LockFreeMap<K, T>::MarkedPointer<PTR>::GetPointer() const {
    return reinterpret_cast<PTR*>(reinterpret_cast<uint32_t>(pPointer) & POINTER_MASK);
}

template<typename K, typename T>
template<typename PTR>
inline PTR* LockFreeMap<K, T>::MarkedPointer<PTR>::operator->() const {
    return GetPointer();
}

template<typename K, typename T>
template<typename PTR>
inline LockFreeMap<K, T>::MarkedPointer<PTR>::operator int() {
    return reinterpret_cast<int>(pPointer);
}

#pragma endregion

#pragma region HashListNode

template<typename K, typename T>
inline LockFreeMap<K, T>::HashListNode::HashListNode(K aKey, const T& arData) {
    tKey = aKey;
    tData = arData;
}

template<typename K, typename T>
inline LockFreeMap<K, T>::HashListNode::~HashListNode() {
}

template<typename K, typename T>
inline bool LockFreeMap<K, T>::HashListNode::GetMark() const {
    return pNext.GetMark();
}

template<typename K, typename T>
inline LockFreeMap<K, T>::HashListNode* LockFreeMap<K, T>::HashListNode::GetNextDelete() {
    return *reinterpret_cast<HashListNode**>(reinterpret_cast<char*>(this) + sizeof(K));
}

// GAME - 0x6ECD40
template<typename K, typename T>
inline void LockFreeMap<K, T>::HashListNode::SetNextDelete(HashListNode* apNext) {
    *reinterpret_cast<HashListNode**>(reinterpret_cast<char*>(this) + sizeof(K)) = apNext;
}

#pragma endregion

#pragma region LockFreeMapInterface

template<typename K, typename T>
inline LockFreeMap<K, T>::LockFreeMapInterface::LockFreeMapInterface(class LockFreeMap* apOwner, HashListNode** apNode0, HashListNode** apNode1, HashListNode** apNode2) :
	pOwner(apOwner), pReferencedNodes(apNode0, apNode1, apNode2), pPrev(nullptr), pDeleteHead(nullptr), uiDeleteCount(0)
{
}

template<typename K, typename T>
inline LockFreeMap<K, T>::LockFreeMapInterface::~LockFreeMapInterface() {
    while (uiDeleteCount)
        ScanForDeletedNodes();
}

// GAME - 0x44C8E0
template<typename K, typename T>
inline bool LockFreeMap<K, T>::LockFreeMapInterface::GetAt(K aKey, T& arData) {
    return GetAt(pOwner->GetBucketForKey(aKey), aKey, arData);
}

// GAME - 0x44D510
template<typename K, typename T>
inline bool LockFreeMap<K, T>::LockFreeMapInterface::GetAt(uint32_t auiBucket, K aKey, T& arData) {
    bool bFound = Find(auiBucket, aKey);
    if (bFound) {
        arData = kCurrent->tData;
        if (kCurrent->GetMark())
            bFound = false;
    }
    ClearReferencedNodes();
    return bFound;
}

template<typename K, typename T>
inline bool LockFreeMap<K, T>::LockFreeMapInterface::SetAt(K aKey, const T& arData, bool abReplaceExisting) {
    return SetAt(pOwner->GetBucketForKey(aKey), aKey, arData, abReplaceExisting);
}

template<typename K, typename T>
inline bool LockFreeMap<K, T>::LockFreeMapInterface::SetAt(uint32_t auiBucket, K aKey, const T& arData, bool abReplaceExisting) {
    AUTO_MEM_CONTEXT(MEM_CONTEXT::THREAD_SAFE_STRUCT);

    bool bResult = true;
    HashListNode* pNode = nullptr;
    while (!Find(auiBucket, aKey)) {
        if (!pNode)
            pNode = new HashListNode(pOwner->CopyKey(aKey), arData);

        MarkedPointer<HashListNode> kCurrPtr(false, kCurrent.GetPointer());
        MarkedPointer<HashListNode> kNewPtr(false, pNode);
        pNode->pNext = kCurrPtr;
        if (CompareAndSwapEx(reinterpret_cast<int*>(pPrev), static_cast<int>(kCurrPtr), static_cast<int>(kNewPtr))) {
            pOwner->IncrementCount();
            ClearReferencedNodes();
            return bResult;
        }
    }

    delete pNode;

    if (abReplaceExisting)
        kCurrent.GetPointer()->tData = arData;
    else
        bResult = false;

    ClearReferencedNodes();
    return bResult;
}

template<typename K, typename T>
inline bool LockFreeMap<K, T>::LockFreeMapInterface::RemoveAt(K aKey) {
    return RemoveAt(pOwner->GetBucketForKey(aKey), aKey);
}

template<typename K, typename T>
inline bool LockFreeMap<K, T>::LockFreeMapInterface::RemoveAt(uint32_t auiBucket, K aKey) {
    bool bResult = false;
    while (true) {
        if (!Find(auiBucket, aKey)) {
            bResult = false;
            break;
        }
        else {
            MarkedPointer<HashListNode> kNextPtr(false, kNext.GetPointer());
            if (CompareAndSwapEx(reinterpret_cast<int*>(&kCurrent->pNext), static_cast<int>(MarkedPointer<HashListNode>(true, kNext.GetPointer())), static_cast<int>(kNextPtr))) {
                if (CompareAndSwapEx(reinterpret_cast<int*>(pPrev), static_cast<int>(kNextPtr), static_cast<int>(MarkedPointer<HashListNode>(false, kCurrent.GetPointer()))))
                    DeleteNode(kCurrent.GetPointer());
                else
                    Find(auiBucket, aKey);

                pOwner->DecrementCount();
                bResult = true;
                break;
            }
        }
    };

    ClearReferencedNodes();
    return bResult;
}

template<typename K, typename T>
inline bool LockFreeMap<K, T>::LockFreeMapInterface::Remove(uint32_t auiBucket, T& arData) {
    bool bResult = false;
    while (true) {
        if (!FindValue(auiBucket, arData)) {
            bResult = false;
            break;
        }
        else {
            MarkedPointer<HashListNode> kNextPtr(false, kNext.GetPointer());
            if (CompareAndSwapEx(reinterpret_cast<int*>(&kCurrent->pNext), static_cast<int>(MarkedPointer<HashListNode>(true, kNext.GetPointer())), static_cast<int>(kNextPtr))) {
                if (CompareAndSwapEx(reinterpret_cast<int*>(pPrev), static_cast<int>(kNextPtr), static_cast<int>(MarkedPointer<HashListNode>(false, kCurrent.GetPointer()))))
                    DeleteNode(kCurrent.GetPointer());
                else
                    FindValue(auiBucket, arData);

                pOwner->DecrementCount();
                bResult = true;
                break;
            }
        }
    };

    ClearReferencedNodes();
    return bResult;
}

// GAME - 0xC42380
template<typename K, typename T>
inline bool LockFreeMap<K, T>::LockFreeMapInterface::GetFirst(uint32_t auiBucket, K& arKey, T& arData) {
    bool bFound;
    while (true) {
        do {
            pPrev = pOwner->GetBucket(auiBucket);
			kCurrent.pPointer = pPrev->pPointer;
			*pReferencedNodes[1] = kCurrent.GetPointer();
        } while (static_cast<int>(*pPrev) != static_cast<int>(MarkedPointer<HashListNode>(false, kCurrent.GetPointer())));
        if (!kCurrent.GetPointer())
            break;

		pOwner->CopyKeyDirect(kCurrent.GetPointer()->tKey, arKey);
        arData = kCurrent.GetPointer()->tData;
        bFound = true;
        if (!kCurrent.GetPointer()->GetMark()) {
            ClearReferencedNodes();
            return bFound;
        }
    }
    bFound = false;
    ClearReferencedNodes();
	return bFound;
}

// GAME - 0xC42560
template<typename K, typename T>
inline bool LockFreeMap<K, T>::LockFreeMapInterface::GetNext(uint32_t auiBucket, K& arKey, T& arData) {
    bool bFound;
    while (true) {
        while (Find(auiBucket, arKey)) {
            if (kNext.GetPointer()) {
                if (kNext->GetMark())
                    continue;

                pOwner->CopyKeyDirect(kNext->tKey, arKey);
                arData = kNext->tData;
                bFound = true;
                if (kNext->GetMark()) {
                    arData = 0;
                    continue;
                }
            }
            else {
                bFound = false;
            }
            ClearReferencedNodes();
            return bFound;
        }

		if (!kCurrent.GetPointer())
            break;

        if (kCurrent->GetMark())
            continue;

        pOwner->CopyKeyDirect(kCurrent->tKey, arKey);
        arData = kCurrent->tData;
        bFound = true;
        if (kCurrent->GetMark()) {
            arData = 0;
            continue;
        }
        ClearReferencedNodes();
        return bFound;
    }
    bFound = false;
    ClearReferencedNodes();
	return bFound;
}

// GAME - 0x529030
template<typename K, typename T>
inline bool LockFreeMap<K, T>::LockFreeMapInterface::Find(uint32_t auiBucket, K aKey) {
    auto pBucket = pOwner->GetBucket(auiBucket);
    do {
        do {
            pPrev = pBucket;
            kCurrent.pPointer = pPrev->pPointer;
            *pReferencedNodes[1] = kCurrent.GetPointer();
        } while (static_cast<int>(*pPrev) != static_cast<int>(MarkedPointer<HashListNode>(false, kCurrent.GetPointer())));
    
        while (true) {
            if (!kCurrent.GetPointer())
                return false;

            kNext.pPointer = kCurrent->pNext.pPointer;
            *pReferencedNodes[0] = kNext.GetPointer();
            if (static_cast<int>(kNext) != static_cast<int>(kCurrent->pNext))
                break;

            K tKey = kCurrent.GetPointer()->tKey;
            MarkedPointer<HashListNode> kPtr(false, kCurrent.GetPointer());
            if (static_cast<int>(*pPrev) != static_cast<int>(kPtr))
                break;

            if (kNext.GetMark()) {
                if (!CompareAndSwapEx(reinterpret_cast<int*>(pPrev), static_cast<int>(kNext), static_cast<int>(kPtr)))
                    break;

                DeleteNode(kCurrent.GetPointer());
            }
            else {
                if (pOwner->IsKeyGreaterOrEqual(tKey, aKey))
                    return pOwner->IsKeyEqual(tKey, aKey);

                pPrev = &kCurrent->pNext;
                *pReferencedNodes[2] = kCurrent.GetPointer();
            }
            kCurrent.pPointer = kNext.pPointer;
            *pReferencedNodes[1] = kNext.GetPointer();
        }
    } while (true);
}

template<typename K, typename T>
inline bool LockFreeMap<K, T>::LockFreeMapInterface::FindValue(uint32_t auiBucket, T& arData) {
    bool bResult;
    auto pBucket = pOwner->GetBucket(auiBucket);
    do {
        do {
            pPrev = pBucket;
            kCurrent.pPointer = pPrev->pPointer;
            *pReferencedNodes[1] = kCurrent.GetPointer();
        } while (static_cast<int>(*pPrev) != static_cast<int>(MarkedPointer<HashListNode>(false, kCurrent.GetPointer())));

        while (true) {
            if (!kCurrent.GetPointer())
                return false;

            kNext.pPointer = kCurrent->pNext.pPointer;
            *pReferencedNodes[0] = kNext.GetPointer();
            if (static_cast<int>(kNext) != static_cast<int>(kCurrent->pNext))
                break;

            T kData = kCurrent.GetPointer()->tData;
            MarkedPointer<HashListNode> kPtr(false, kCurrent.GetPointer());
            if (static_cast<int>(*pPrev) != static_cast<int>(kPtr))
                break;

            if (kNext.GetMark()) {
                if (!CompareAndSwapEx(reinterpret_cast<int*>(pPrev), static_cast<int>(kNext), static_cast<int>(kPtr)))
                    break;

                DeleteNode(kCurrent.GetPointer());
            }
            else if (kData != arData) {
                pPrev = &kCurrent->pNext;
                *pReferencedNodes[2] = kCurrent.GetPointer();
            }
            else {
                bResult = true;
                return bResult;
            }
            kCurrent.pPointer = kNext.pPointer;
            *pReferencedNodes[1] = kNext.GetPointer();
        }
    } while (true);
}

// GAME - 0x5292A0
template<typename K, typename T>
inline void LockFreeMap<K, T>::LockFreeMapInterface::DeleteNode(HashListNode* apNode) {
    apNode->tData = 0;
    apNode->SetNextDelete(pDeleteHead);
    pDeleteHead = apNode;
    ++uiDeleteCount;
    if (uiDeleteCount == pOwner->GetDeleteBatchSize())
        ScanForDeletedNodes();
}

template<typename K, typename T>
inline void LockFreeMap<K, T>::LockFreeMapInterface::ClearReferencedNodes() {
    *pReferencedNodes[0] = nullptr;
    *pReferencedNodes[1] = nullptr;
    *pReferencedNodes[2] = nullptr;
}

// GAME - 0x44F220
template<typename K, typename T>
inline void LockFreeMap<K, T>::LockFreeMapInterface::ScanForDeletedNodes() {
    AUTO_MEM_CONTEXT(MEM_CONTEXT::THREAD_SAFE_STRUCT);
	uint32_t uiMaxThreads = pOwner->GetMaxThreads();
    const uint32_t uiArraySize = 3 * uiMaxThreads;
	HashListNode** ppTempNodes = new HashListNode*[uiArraySize];
	memcpy(ppTempNodes, pOwner->pReferencedNodes, sizeof(size_t) * uiArraySize);

    HashListNode* pHead = 0;
    uint32_t uiCounter = 0;
    while (pDeleteHead) {
        HashListNode* pItem = pDeleteHead;
        pDeleteHead = pDeleteHead->GetNextDelete();
        bool bFound = false;
        for (uint32_t i = 0; i < uiArraySize; ++i) {
            if (pItem == ppTempNodes[i]) {
                bFound = true;
                break;
            }
        }
        if (bFound) {
            pItem->SetNextDelete(pHead);
            pHead = pItem;
            ++uiCounter;
        }
        else {
            pItem->SetNextDelete(nullptr);
            pOwner->DeleteNode(pItem);
        }
    }
    delete[] ppTempNodes;
    pDeleteHead = pHead;
    uiDeleteCount = uiCounter;
}

#pragma endregion

#pragma region LockFreeMap

template<typename K, typename T>
inline LockFreeMap<K, T>::LockFreeMap(uint32_t auiMaxThreads, uint32_t auiBucketCount, uint32_t auiDeleteBatchSize) {
    AUTO_MEM_CONTEXT(MEM_CONTEXT::THREAD_SAFE_STRUCT);
    uiCount             = 0;
    uiNumBuckets        = auiBucketCount;
    pBuckets            = new MarkedPointer<HashListNode>[auiBucketCount];
    pReferencedNodes    = new HashListNode*[3 * auiMaxThreads];
    uiDeleteBatchSize   = auiDeleteBatchSize;
    pManager            = new Manager(auiMaxThreads);
}

template<typename K, typename T>
inline LockFreeMap<K, T>::~LockFreeMap() {
    RemoveAll(true);
    delete[] pBuckets;
    delete[] pReferencedNodes;
}

template<typename K, typename T>
inline void* LockFreeMap<K, T>::AllocateInterface(uint32_t auiThread) {
    AUTO_MEM_CONTEXT(MEM_CONTEXT::THREAD_SAFE_STRUCT);
    const uint32_t uiIndex = 3 * auiThread;
    return new LockFreeMapInterface(this, &pReferencedNodes[uiIndex], &pReferencedNodes[uiIndex + 1], &pReferencedNodes[uiIndex + 2]);
}

template<typename K, typename T>
inline bool LockFreeMap<K, T>::GetAt(K aKey, T& arData) {
	std::lock_guard kGuard(kLock);
    return GetInterface()->GetAt(aKey, arData);
}

template<typename K, typename T>
inline bool LockFreeMap<K, T>::SetAt(uint32_t auiBucket, K aKey, const T& arData, bool abReplaceExisting) {
    std::lock_guard kGuard(kLock);
    return GetInterface()->SetAt(auiBucket, aKey, arData, abReplaceExisting);
}

template<typename K, typename T>
inline bool LockFreeMap<K, T>::SetAtAlt(K aKey, const T& arData, bool abReplaceExisting) {
    std::lock_guard kGuard(kLock);
    return GetInterface()->SetAt(aKey, arData, abReplaceExisting);
}

template<typename K, typename T>
inline bool LockFreeMap<K, T>::RemoveAt(K aKey) {
    std::lock_guard kGuard(kLock);
    return GetInterface()->RemoveAt(aKey);
}

template<typename K, typename T>
inline bool LockFreeMap<K, T>::Remove(uint32_t auiBucket, T aData) {
    std::lock_guard kGuard(kLock);
    return GetInterface()->Remove(auiBucket, aData);
}

template<typename K, typename T>
inline bool LockFreeMap<K, T>::RemoveAlt(T aData) {
    std::lock_guard kGuard(kLock);
    bool bRemoved = false;
    for (uint32_t i = 0; i < uiNumBuckets && !bRemoved; ++i) {
        bRemoved = Remove(i, aData);
    }
    return bRemoved;
}

template<typename K, typename T>
inline bool LockFreeMap<K, T>::GetAtAlt(K aKey, T& arData) {
    return GetInterface()->GetAt(aKey, arData);
}

template<typename K, typename T>
inline uint32_t LockFreeMap<K, T>::GetBucketForKey(K aKey) {
    return reinterpret_cast<uint32_t&>(aKey) % uiNumBuckets;
}

template<typename K, typename T>
inline void LockFreeMap<K, T>::DeleteKey(K aKey) {
}

template<typename K, typename T>
inline K LockFreeMap<K, T>::CopyKey(K aKey) {
    return aKey;
}

template<typename K, typename T>
inline void LockFreeMap<K, T>::CopyKeyDirect(K aKey, K& arCopiedKey) {
    arCopiedKey = aKey;
}

template<typename K, typename T>
inline bool LockFreeMap<K, T>::IsKeyGreaterOrEqual(K aKey1, K aKey2) const {
    return aKey1 >= aKey2;
}

template<typename K, typename T>
inline bool LockFreeMap<K, T>::IsKeyEqual(K aKey1, K aKey2) const {
    return aKey1 == aKey2;
}

template<typename K, typename T>
inline void LockFreeMap<K, T>::IncrementCount() {
    InterlockedIncrement(&uiCount);
}

template<typename K, typename T>
inline void LockFreeMap<K, T>::DecrementCount() {
    InterlockedDecrement(&uiCount);
}

template<typename K, typename T>
inline uint32_t LockFreeMap<K, T>::GetCount() const {
    return uiCount;
}

template<typename K, typename T>
inline LockFreeMap<K, T>::LockFreeMapInterface* LockFreeMap<K, T>::GetInterface() {
    return pManager->GetInterface(this);
}

template<typename K, typename T>
uint32_t LockFreeMap<K, T>::GetMaxThreads() const {
	return pManager->uiMaxThreads;
}

template<typename K, typename T>
inline uint32_t LockFreeMap<K, T>::GetNumBuckets() const {
    return uiNumBuckets;
}

// GAME - 0x44EDB0
template<typename K, typename T>
inline uint32_t LockFreeMap<K, T>::GetDeleteBatchSize() const {
    return uiDeleteBatchSize;
}

// GAME - 0x44EE20
template<typename K, typename T>
inline LockFreeMap<K, T>::MarkedPointer<typename LockFreeMap<K, T>::HashListNode>* LockFreeMap<K, T>::GetBucket(uint32_t auiBucket) {
    return &pBuckets[auiBucket];
}

template<typename K, typename T>
inline bool LockFreeMap<K, T>::GetNext(LockFreeMapIterator& arIter, K& arKey, T& arData, bool abSwitchBuckets) {
    std::lock_guard kGuard(kLock);
    bool bResult;
    if (arIter.GetFinished()) {
        bResult = false;
    }
    else {
        while (true) {
            if (arIter.GetStartedBucket()) {
                const uint32_t uiBucket = arIter.uiBucket;
                bResult = GetInterface()->GetNext(uiBucket, arIter.tLastKey, arData);
            }
            else {
                const uint32_t uiBucket = arIter.uiBucket;
                bResult = GetInterface()->GetFirst(uiBucket, arIter.tLastKey, arData);
                arIter.SetStartedBucket(true);
            }

            if (!bResult) {
                ++arIter.uiBucket;

                if (arIter.uiBucket >= GetNumBuckets()) {
                    arIter.SetFinished(true);
                    break;
                }

                if (!abSwitchBuckets)
                    break;

                arIter.SetStartedBucket(false);
                continue;
            }

            arKey = arIter.tLastKey;
            break;
        }
    }

    return bResult;
}

template<typename K, typename T>
inline bool LockFreeMap<K, T>::GetNextAndRemove(LockFreeMapIterator& arIter, K& arKey, T& arData, bool abSwitchBuckets) {
    std::lock_guard kGuard(kLock);
    bool bResult;
    if (arIter.GetFinished()) {
        bResult = false;
    }
    else {
        while (true) {
            if (arIter.GetStartedBucket()) {
                const uint32_t uiBucket = arIter.uiBucket;
                bResult = GetInterface()->GetNext(uiBucket, arIter.tLastKey, arData);
            }
            else {
                const uint32_t uiBucket = arIter.uiBucket;
                bResult = GetInterface()->GetFirst(uiBucket, arIter.tLastKey, arData);
                arIter.SetStartedBucket(true);
            }

            if (!bResult) {
                ++arIter.uiBucket;

                if (arIter.uiBucket >= GetNumBuckets()) {
                    arIter.SetFinished(true);
                    break;
                }

                if (!abSwitchBuckets)
                    break;

                arIter.SetStartedBucket(false);
                continue;
            }
            
            arKey = arIter.tLastKey;
            break;
        }
    }

    if (bResult)
        bResult = GetInterface()->RemoveAt(arKey);

    return bResult;
}

template<typename K, typename T>
inline void LockFreeMap<K, T>::RemoveAll(bool abCalledByDestructor) {
    AUTO_MEM_CONTEXT(MEM_CONTEXT::THREAD_SAFE_STRUCT);
    if (pManager) {
		std::lock_guard kGuard(kLock);
        const uint32_t uiMaxThreads = pManager->GetMaxThreads();
        delete pManager;
        pManager = nullptr;
        uiCount = 0;

        for (uint32_t i = 0; i < uiNumBuckets; ++i) {
            auto pIter = pBuckets[i].GetPointer();
            pBuckets[i].Clear();
            while (pIter) {
                auto pNextPtr = pIter->pNext.GetPointer();
                pIter->pNext.Clear();
                pIter->tData = 0;
                DeleteNode(pIter);
                pIter = pNextPtr;
            }
        }

        if (!abCalledByDestructor)
            pManager = new Manager(uiMaxThreads);
    }
}

// GAME - 0x44DDE0
template<typename K, typename T>
inline void LockFreeMap<K, T>::DeleteNode(HashListNode* apNode) {
	DeleteKey(apNode->tKey);
	delete apNode;
}

#pragma endregion

#pragma region LockFreeMapIterator

template<typename K, typename T>
inline LockFreeMap<K, T>::LockFreeMapIterator::LockFreeMapIterator() : uiBucket(0), tLastKey(0) {
}

template<typename K, typename T>
inline LockFreeMap<K, T>::LockFreeMapIterator::~LockFreeMapIterator() {
}

template<typename K, typename T>
inline void LockFreeMap<K, T>::LockFreeMapIterator::ClearKey() { 
    tLastKey = K(0); 
}

template<typename K, typename T>
inline void LockFreeMap<K, T>::LockFreeMapIterator::SetStartedBucket(bool abVal) { 
    ucFlags.Set<State::STARTED_BUCKET>(abVal);
}

template<typename K, typename T>
inline void LockFreeMap<K, T>::LockFreeMapIterator::SetFinished(bool abVal) { 
    ucFlags.Set<State::FINISHED>(abVal);
}

template<typename K, typename T>
inline bool LockFreeMap<K, T>::LockFreeMapIterator::GetFinished() const { 
    return ucFlags.Get<State::FINISHED>(); 
}

template<typename K, typename T>
inline void LockFreeMap<K, T>::LockFreeMapIterator::SetBucket(uint32_t auiBucket) {
    ClearKey();
    uiBucket = auiBucket;
    SetStartedBucket(false);
    SetFinished(false);
}

template<typename K, typename T>
inline void LockFreeMap<K, T>::LockFreeMapIterator::Reset() { 
    SetBucket(0);
}

#pragma endregion