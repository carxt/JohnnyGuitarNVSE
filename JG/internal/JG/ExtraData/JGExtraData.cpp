#include "JGExtraData.hpp"
#include <vector>
#include <stack>
#ifdef GAME
#include "JG/EditorIDRestoration.hpp"
#endif

#define DEBUG_PRINTS 0

#if DEBUG_PRINTS
#include <shared/Utils/DebugLog.hpp>
#define DEBUG_MSG(...) _MESSAGE(__VA_ARGS__)
#else
#define DEBUG_MSG(...) __noop(__VA_ARGS__)
#endif

template<class T, uint32_t uiMaxSize>
class PointerPool {
	std::stack<T*, std::vector<T*>> kStack;
	SRWLOCK							kLock = SRWLOCK_INIT;

public:
	SPEC_NOINLINE T* __fastcall Pop() {
		if (kStack.empty())
			return nullptr;

		AcquireSRWLockExclusive(&kLock);
		T* pData = kStack.top();
		if (pData)
			kStack.pop();
		ReleaseSRWLockExclusive(&kLock);
		return pData;
	}

	SPEC_NOINLINE bool __fastcall Push(T* apData) {
		bool bResult = false;
		if (TryAcquireSRWLockExclusive(&kLock)) {
			if (kStack.size() + 1 < uiMaxSize) {
				kStack.push(apData);
				bResult = true;
			}
			ReleaseSRWLockExclusive(&kLock);
		}
		return bResult;
	}
};

static PointerPool<JGExtraData, 16> kFreeDataPool;

SPEC_NOINLINE JGExtraData::JGExtraData() : pOwner(nullptr) {
}

SPEC_NOINLINE JGExtraData::~JGExtraData() {
	assert(refCount == 0);
	Reset();
}

SPEC_NOINLINE void JGExtraData::Reset() {
#ifdef GAME
	DetachEditorIDs();
	kEditorIDs.RemoveAll();
#endif
	pOwner = nullptr;
}

SPEC_NOINLINE void JGExtraData::DeleteThis() {
	assert(refCount == 0);
	DEBUG_MSG("Deleting JGExtraData for %08X (\"%s\")", pOwner ? pOwner->GetFormID() : 0, GetOwnerEDID());
	Reset();
	const bool bPooled = kFreeDataPool.Push(this);
	if (!bPooled)
		delete this;
}

SPEC_NOINLINE bool JGExtraData::OnRemoval(TESForm* apForm, uint32_t aeRemovalReason) {
	switch (aeRemovalReason) {
		case PluginFormExtraData::RemovalReason::kFormDeletion:
		case PluginFormExtraData::RemovalReason::kTrashedReference:
			DEBUG_MSG("%08X (\"%s\") got deleted!", apForm->GetFormID(), GetOwnerEDID());
			Reset();
			break;
		default:
			break;
	}
	return true;
}

SPEC_NOINLINE JGExtraData* JGExtraData::Create() {
	JGExtraData* pData = kFreeDataPool.Pop();
	if (!pData)
		pData = new JGExtraData();

	assert(pData);
	return pData;
}

bool JGExtraData::OnAdd(TESForm* apForm) {
	pOwner = apForm;
	return true;
}

TESForm* JGExtraData::GetOwner() const {
	return pOwner;
}

const char* JGExtraData::GetOwnerEDID() const {
#ifdef GAME
	const char* pEDID = kEditorIDs.GetItem();
	if (pEDID) 
		return pEDID;
#else
	if (pOwner)
		return pOwner->GetFormEditorID();
#endif
	return "";
}

#ifdef GAME
const NiFixedString& JGExtraData::GetEditorID() const {
	return kEditorIDs.GetItem();
}

SPEC_NOINLINE JGExtraData::EDIDResult __fastcall JGExtraData::SetEditorID(const NiFixedString& arEDID) {
	if (!arEDID.GetLength()) {
		DEBUG_MSG("%08X Tried to set an empty EDID", pOwner->GetFormID());
		return EDIDResult::FAILURE;
	}

	if (!GetEditorID()) {
		DEBUG_MSG("%08X Adding EDID \"%s\"", pOwner->GetFormID(), arEDID);
		kEditorIDs.SetItem(arEDID);
		return EDIDResult::SUCCESS;
	}
	else if (GetEditorID() != arEDID) {
		if (kEditorIDs.IsInList(arEDID)) {
			DEBUG_MSG("%08X EDID alias \"%s\" already exists", pOwner->GetFormID(), arEDID);
			return EDIDResult::ALREADY_EXISTS;
		}

		kEditorIDs.AddHead(arEDID);
		DEBUG_MSG("%08X Adding EDID alias \"%s\"", pOwner->GetFormID(), arEDID);
		return EDIDResult::SUCCESS;
	}
	else {
		DEBUG_MSG("%08X EDID \"%s\" is already set", pOwner->GetFormID(), arEDID);
		return EDIDResult::ALREADY_EXISTS;
	}
}

JGExtraData::EDIDResult __fastcall JGExtraData::RemoveEditorID(const NiFixedString& arEDID) {
	kEditorIDs.Remove(arEDID);
	return EDIDResult::SUCCESS;
}

JGExtraData::EDIDList* JGExtraData::GetEditorIDHead() {
	return &kEditorIDs;
}

SPEC_NOINLINE void JGExtraData::DetachEditorIDs() {
	if (pOwner && !pOwner->GetTemporary() && !kEditorIDs.IsEmpty()) {
		auto pIter = kEditorIDs.GetHead();
		AcquireSRWLockExclusive(&EDIDRestoration::kEDIDMapLock);
		while (pIter) {
			TESForm* pFoundForm = nullptr;
			if (TESForm::pAllFormsByEditorID->GetAt(pIter->GetItem(), pFoundForm) && pFoundForm){
				if (pFoundForm == pOwner) {
					DEBUG_MSG("%08X Removing EDID \"%s\"", pOwner->GetFormID(), pIter->GetItem());
					TESForm::pAllFormsByEditorID->RemoveAt(pIter->GetItem());
				}
				else {
					DEBUG_MSG("%08X Tried to remove EDID \"%s\" belonging to %08X", pOwner->GetFormID(), pIter->GetItem(), pFoundForm->GetFormID());
				}
			}
			pIter = pIter->GetNext();
		}
		ReleaseSRWLockExclusive(&EDIDRestoration::kEDIDMapLock);
	}
}
#endif